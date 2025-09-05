/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef VALIDATOR_H
#define VALIDATOR_H
#include<QString>
#include<stdexcept>
#include"../include/Logger.h"
#include<QFile>
#include<optional>

enum class ModeValidator
{
    Login,
    Register,
    WriteFile,
    ReadFile,
    Delete
};

struct Validator
{
    Validator() = delete;

    static void verifyLoginAndPassword(const QString& login,const QString& password,ModeValidator modeRL);
    static void isFileValid(QFile& File,ModeValidator modeIO);
    static std::optional<double> ValidOptional(const QString& scoreStr);

    //static bool isPasswordStrong(const std::string& password);
    //static bool isEmailValid(const std::string& email);
private:
    static std::shared_ptr<Log> Logger;
};

#endif // VALIDATOR_H
