/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     zhouyi<zhouyi1@uniontech.com>
 *
 * Maintainer: zhouyi<zhouyi1@uniontech.com>
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
#include "optionpythongenerator.h"
#include "pythonoptionwidget.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QTabWidget>

class OptionPythonGeneratorPrivate
{
    friend class OptionPythonGenerator;

    PythonOptionWidget *widget = nullptr;
};

OptionPythonGenerator::OptionPythonGenerator()
    : d(new OptionPythonGeneratorPrivate())
{
    d->widget = new PythonOptionWidget();
}

QWidget *OptionPythonGenerator::optionWidget()
{
    return d->widget;
}
