/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef LOADER_H
#define LOADER_H
#include"Libs.h"
#include"StudentManagerCore/Student.h"
#include<QFile>
#include <QRegularExpression>
#include"AuthUser.h"
#include<QPushButton>
#include<QLineEdit>
#include"FileChooicer.h"
#include<QFormLayout>

//DynamicFormDialog


class StudentLoader
{
private:
    static std::shared_ptr<Log> logger;
public:

   static std::vector<std::shared_ptr<Student>> fromFile(const QString& file);
    static std::vector<Student> loadStudentsFromFile(const QString& file);
   //UserAuth
    static bool saveLoginPassword(const QString& login, const QString& hashedPassword, const QString& fileName);
    static bool ReadLoginPassword(const QString& login, const QString& hashedPassword);
    static bool isLoginExists(const QString& login, const QString& file);

};

#endif // LOADER_H
