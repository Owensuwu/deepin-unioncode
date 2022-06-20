/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     huangyu<huangyub@uniontech.com>
 *
 * Maintainer: huangyu<huangyub@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "generator.h"

#include <QStandardItem>

Generator::Generator(QObject *parent)
    : QObject(parent)
{

}

QString Generator::errorString()
{
    return property("errorString").toString();
}

bool Generator::setErrorString(const QString &error)
{
    return setProperty("errorString", error);
}

bool Generator::setProperty(const QString &name, const QVariant &value)
{
    return QObject::setProperty(name.toLatin1(), value);
}

QVariant Generator::property(const QString &name) const
{
    return QObject::property(name.toLatin1());
}

void Generator::recursionRemoveItem(QStandardItem *item)
{
    if (!item)
        return;


    for (int row = 0; row < item->rowCount(); row ++) {
        auto child = item->takeChild(row);
        if (!child->hasChildren()) {
            delete child;
        } else {
            recursionRemoveItem(child);
        }
    }

    delete item;
    return;
}