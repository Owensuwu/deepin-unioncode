#include "setting.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <iostream>

#define CONFIG_FILE_NAME "languageAdapter.conf"
#define CONFIG_PATH QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)
#define CONFIG_FILE_PATH CONFIG_PATH + QDir::separator() + CONFIG_FILE_NAME

namespace {
QJsonDocument configDoc;
QString configTemplate{
    "{\n"
    "    \"C/C++\" : {\n"
    "           \"mode\": \"process\",\n"
    "           \"program\": \"/usr/bin/xxx\",\n"
    "           \"arguments\": []\n"
    "    },\n"
    "    \"Java\" : {\n"
    "           \"mode\": \"socket\",\n"
    "           \"port\": \"3308\",\n"
    "           \"program\" : \"/usr/bin/xxx\",\n"
    "           \"arguments\" : []\n"
    "    },\n"
    "    \"Python\" : {\n"
    "           \"mode\": \"socket\",\n"
    "           \"port\": \"3308\",\n"
    "           \"program\" : \"/usr/bin/xxx\",\n"
    "           \"arguments\" : []\n"
    "    }\n"
    "}\n"
};

QString configCache{
    "{\n"
    "    \"C/C++\" : {\n"
    "           \"mode\": \"process\",\n"
    "           \"program\": \"/usr/bin/clangd\",\n"
    "           \"arguments\": []\n"
    "    },\n"
    "    \"Java\" : {\n"
    "           \"mode\": \"process\",\n"
    "           \"program\" : \"\",\n"
    "           \"arguments\" : []\n"
    "    },\n"
    "    \"Python\" : {\n"
    "           \"mode\": \"process\",\n"
    "           \"program\" : \"\",\n"
    "           \"arguments\" : []\n"
    "    }\n"
    "}\n"
};
}

bool checkConfigFile()
{
    QDir dir(CONFIG_PATH);
    if (!dir.exists()) {
        QDir().mkdir(CONFIG_PATH);
    }

    QFile file(CONFIG_FILE_PATH);
    if (!file.exists()) {
        if (file.open(QFile::Truncate | QFile::ReadWrite)) {
            file.write(configCache.toLatin1());
            file.close();
        }
    }

    if (file.open(QFile::ReadOnly)) {
        ::configDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
    }

    if (!::configDoc.isObject()) {
        std::cerr << "Failed, can't load configure file" << std::endl;
        abort();
    }

    return true;
}

SettingInfo Setting::getInfo(const QString &language)
{
    checkConfigFile();
    QJsonObject docObj = configDoc.object();
    QJsonObject secObj = docObj.value(language).toObject();
    QString mode = secObj.value("mode").toString();
    QString program = secObj.value("program").toString();
    QJsonArray array = secObj.value("arguments").toArray();
    QStringList result;
    for (auto val : array) {
        result << val.toString();
    }
    return {language, mode, program, result };
}

bool Setting::genConfigFile(const QString &configPath)
{
    if (!QDir(configPath).exists()) {
        std::cerr <<  "Failed, file path not exists!" << std::endl;
        return false;
    }

    bool enquire = true;
    bool exists = false;
    QFile configFile(configPath + QDir::separator() + CONFIG_FILE_NAME);
    if (configFile.exists()) {
        exists = true;
        std::cout << "config file exists, need overwrite? [Y/N]:";
        char req;
        std::cin >> req;
        if ('Y' == req)
            enquire = true;
        else {
            enquire = false;
            return false;
        }
    } else {
        exists = false;
    }

    if ((exists && enquire) || !exists){
        std::cout << "Start generating files" << std::endl;

        if (!configFile.open(QFile::Truncate |QFile::WriteOnly)) {
            std::cerr << configFile.errorString().toUtf8().toStdString() << std::endl;
        }

        configFile.write(::configTemplate.toLatin1());
        configFile.close();

        std::cout << std::string("Successful file path: ") +
                     (configPath + QDir::separator() + CONFIG_FILE_NAME).toStdString()
                  << std::endl;
        return true;
    }

    std::cerr << "Failed, Unknown error!" << std::endl;
    return false;
}
