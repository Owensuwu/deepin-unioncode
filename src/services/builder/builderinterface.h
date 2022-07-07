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
#ifndef BUILDERINTERFACE_H
#define BUILDERINTERFACE_H

#include "builderglobals.h"
#include "task.h"
#include "services/project/projectinfo.h"
#include <framework/framework.h>

class BuilderInterface
{
public:
    /*!
     * \brief builderCommand
     * \param program
     * \param arguments
     * \param workingDir
     */
    DPF_INTERFACE(void, builderCommand, const QString &program, const QStringList &arguments, const QString &workingDir);

    /*!
     * \brief compileOutput
     * \param content
     * \param format
     */
    DPF_INTERFACE(void, compileOutput, const QString &content, OutputFormat format);

    /*!
     * \brief problemOutput
     * \param task
     * \param linkedOutputLines
     * \param skipLines
     */
    DPF_INTERFACE(void, problemOutput, const Task &task, int linkedOutputLines, int skipLines);

    /*!
     * \brief buildStateChanged
     * \param state
     * \param originCmds
     */
    DPF_INTERFACE(void, buildStateChanged, BuildState state, QString originCmds);

    /*!
     * \brief buildStart
     */
    DPF_INTERFACE(void, buildStart);
};

#endif // BUILDERINTERFACE_H
