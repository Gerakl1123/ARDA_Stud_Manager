/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include"Loader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <memory>
#include<QtCore>
#include"Validator.h"


std::shared_ptr<Log> StudentLoader::logger = Log::create("LoaderLog.txt");

std::vector<std::shared_ptr<Student>> StudentLoader::fromFile(const QString &fileName) // filename'и храняться студенты
{
    std::vector<std::shared_ptr<Student>> vecStudentTemp;

    QFile file(fileName);

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(std::logic_error& e)
    {
        qWarning("Error open this file: %s", qUtf8Printable(fileName));
        StudentLoader::logger->write(e.what());
        return vecStudentTemp;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty())
            continue;

        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        if (parts.size() != 2)
            continue;

        bool ok = false;
        double ball = parts[1].toDouble(&ok);

        if (!ok)
            continue;

        QString name = parts[0];
        vecStudentTemp.push_back(std::make_shared<Student>(name, ball));

    }

    file.close();

    return vecStudentTemp;
}


std::vector<Student> StudentLoader::loadStudentsFromFile(const QString &file)
{

    std::vector<Student> vecStudentTemp = std::vector<Student>();

    QFile ifile(file);


    try
    {
        Validator::isFileValid(ifile,ModeValidator::ReadFile);
    }
    catch(std::logic_error& e)
    {
        StudentLoader::logger->write(e.what());
        return vecStudentTemp;
    }

    QTextStream in(&ifile);

    while(!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if(line.isEmpty())
            continue;

        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        if (parts.size() != 2)
            continue;

        bool ok = false;
        double ball = parts[1].toDouble(&ok);
        if (!ok)
            continue;

        QString name = parts[0];
        vecStudentTemp.emplace_back(name,ball);
    }

    return vecStudentTemp;

}
//UserAuth
bool StudentLoader::saveLoginPassword(const QString& login, const QString& hashedPassword, const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out << login << " " << hashedPassword <<  " [" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "] ""\n";

    file.close();

    return true;
}
bool StudentLoader::ReadLoginPassword(const QString &login, const QString &password)
{
    const QString fileName = "DATALP.txt";
    QFile file(fileName);

    try{
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(std::invalid_argument& e)
    {
        qWarning() << "Ошибка при открытии файла:" << e.what();
        return false;
    }

    QTextStream in(&file);

    in.setEncoding(QStringConverter::Utf8);

    QString hashedInput = UserAuthenticator::hashPass(password);

    while(!in.atEnd())
    {
        QString line = in.readLine().trimmed().remove(QChar::ByteOrderMark);

        if (line.isEmpty())
            continue;

        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (parts.size() < 2)
            continue;

        QString loginFile = parts[0].trimmed();
        QString passwordFile = parts[1].trimmed();

        if(login.compare(login,Qt::CaseInsensitive) == 0 && passwordFile == hashedInput)
        {
            return true;
        }
    }

    return false;
}

bool StudentLoader::isLoginExists(const QString &login, const QString &file)
{
    QFile ifile(file);

    try {
        Validator::isFileValid(ifile, ModeValidator::ReadFile);
    } catch (const std::invalid_argument& e) {
        qWarning() << "Ошибка при открытии файла:" << e.what();
        return false;
    }

    QTextStream in(&ifile);
    in.setEncoding(QStringConverter::Utf8);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.isEmpty())
            continue;

        qDebug() << "line:" << line.toUtf8();

        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        if (parts.size() < 2) {
            continue;
        }

        QString fileLogin = parts[0].trimmed().remove(QChar::ByteOrderMark).toLower();
        QString inputLogin = login.trimmed().remove(QChar::ByteOrderMark).toLower();


        if (fileLogin == inputLogin)
        {
            return true;
        }
    }

    return false;
}
