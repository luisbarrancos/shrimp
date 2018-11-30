
/*
    Copyright 2010-2012, Romain Behar <romainbehar@users.sourceforge.net>

    This file is part of Shrimp 2.

    Shrimp 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Shrimp 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Shrimp 2.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "system_functions.h"

#include "../miscellaneous/logging.h"

#include <QDir>
#include <QFileInfo>
#include <QTextStream>

system_functions::system_functions()
    : runningProcess(nullptr)
{
}

std::string system_functions::get_user_directory()
{
    log() << aspect << "system_functions::get_user_directory()" << std::endl;

    // get user's home
    QString home = QDir().homePath();

    // check for .shrimp directory, create it if not there
    QString shrimp = home + QDir().separator() + ".shrimp";
    if (!QDir().exists(shrimp))
    {
        QDir().mkdir(shrimp);
    }

    return shrimp.toStdString();
}

std::string system_functions::get_temp_directory()
{
    // get .shrimp directory
    std::string shrimp = get_user_directory();

    // check for temp directory
    QString temp = QString::fromStdString(shrimp) + QDir().separator() + QString::fromStdString("temp");
    if (!QDir().exists(temp))
    {
        QDir().mkdir(temp);
    }
    return temp.toStdString();
}

std::string system_functions::get_absolute_path(const std::string& path)
{
    QDir absolute = QString::fromStdString(path);
    if (absolute.isAbsolute())
    {
        if (!absolute.makeAbsolute())
        {
            log() << error << "Error while converting path to absolute: " << path
                  << std::endl;
        }
    }

    QString newPath = absolute.absolutePath();

    return newPath.toStdString();
}

std::vector<std::string> system_functions::list_directory(const std::string& directory)
{
    std::vector<std::string> list;

    QString qdirectory = QString::fromStdString(directory);
    QDir dir_info(qdirectory);
    QStringList directory_items = dir_info.entryList();

    if (directory_items.count() <= 0)
    {
        log() << error << "Couldn't list the content of directory '" << directory << "'"
              << std::endl;
    }
    else
    {
        for (QStringList::const_iterator i = directory_items.constBegin();
             i != directory_items.constEnd();
             ++i)
        {
            list.push_back(i->toStdString());
        }
    }

    return list;
}

bool system_functions::is_directory(const std::string& path)
{
    const QString qpath = QString::fromStdString(path);
    QDir dir            = QDir(qpath);

    return dir.exists();
}

std::string system_functions::combine_paths(
    const std::string& path1,
    const std::string& path2)
{
    QString new_path = QString::fromStdString(path1) + QDir().separator() + QString::fromStdString(path2);
    return new_path.toStdString();
}

std::string system_functions::get_file_extension(const std::string& file)
{
    QString q_file = QString::fromStdString(file);
    QFileInfo info = QFileInfo(q_file);

    return info.suffix().toStdString();
}

void system_functions::save_file(
    const std::string& destination,
    const std::string& content)
{
    QFile file(QString::fromStdString(destination));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << QString::fromStdString(content);
        file.close();
    }
    else
    {
        log() << error << "Couldn't save file '" << destination << "'" << std::endl;
    }
}

void system_functions::execute_synchronous_command(const std::string& command)
{
    log() << aspect << "Executing synchronous command: " << command << std::endl;

    runningProcess = new QProcess();
    QObject::connect(
        runningProcess,
        SIGNAL(error(QProcess::ProcessError)),
        this,
        SLOT(processError(QProcess::ProcessError)));
    QObject::connect(
        runningProcess,
        SIGNAL(finished(int, QProcess::ExitStatus)),
        this,
        SLOT(processFinished(int, QProcess::ExitStatus)));

    runningProcess->start(QString::fromStdString(command));
    runningProcess->waitForStarted();

    // always wait for the process to finish before starting a new one (all shaders must be compiled before rendering)
    if (!runningProcess->waitForFinished())
    {
        log() << error << "Synchronous process failed" << std::endl;
    }
    else
    {
        QByteArray output = runningProcess->readAll();
        log() << error << "OUTPUT = " << QString(output).toStdString() << std::endl;
    }

    delete runningProcess;
    runningProcess = nullptr;
}

void system_functions::execute_asynchronous_command(const std::string& command)
{
    log() << aspect << "Executing and detaching command: " << command << std::endl;

    QProcess detachedCommand;
    if (!detachedCommand.startDetached(QString::fromStdString(command)))
    {
        log() << error << "Command launch failed" << std::endl;
    }
}

void system_functions::processError(QProcess::ProcessError error)
{
    log() << error << "Process error = " << error << std::endl;
}

void system_functions::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    log() << aspect << "Process finished with code " << exitCode << std::endl;
}
