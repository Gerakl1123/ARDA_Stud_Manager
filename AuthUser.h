/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef AUTHUSER_H
#define AUTHUSER_H
#include"Logger.h"
#include<QString>
#include<QDateTime>
#include<QByteArray>
#include<QCryptographicHash>
#include"Validator.h"

class StudentLoader;

struct UserAuthenticator
{
    friend class StudentLoader;



   explicit UserAuthenticator(const QString& logFile)
        : logger(Log::create(logFile.toStdString()))
    {}
   UserAuthenticator() = delete;
   UserAuthenticator(const UserAuthenticator&) = delete;
   UserAuthenticator& operator=(const UserAuthenticator&) = delete;
   UserAuthenticator& operator=(UserAuthenticator&&) noexcept = delete;
   UserAuthenticator(UserAuthenticator&&)noexcept = delete;

    bool registerStudent(const QString& login, const QString& password);
    bool loginStudent(const QString& login, const QString& password);
private:
    bool isFileWritable(const QString& fileName);
    bool isFileReadtable(const QString& fileName);

    std::shared_ptr<Log> logger;
   static QString hashPass(const QString&);
};

#endif // AUTHUSER_H
