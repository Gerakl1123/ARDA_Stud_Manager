/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include"../include/Validator.h"
#include<QRegularExpression>

std::shared_ptr<Log> Validator::Logger = Log::create("ValidatorLog.txt");

void Validator::verifyLoginAndPassword(const QString &login, const QString &password,ModeValidator mode)
{
    if(login.isEmpty() || password.isEmpty()){
        Logger->write("Fail register account");
        throw std::invalid_argument("Login or password don't is empty.");

    }

    if(mode == ModeValidator::Register){

            if(login.length() <= 4){
                Logger->write("shory login");
                throw std::invalid_argument("Login to short this > 4 symbols");
            }

            QRegularExpression DifficultPassword("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$");

            if (!DifficultPassword.match(password).hasMatch()) {
                Logger->write("weak password");
                throw std::invalid_argument("The password must be at least 8 characters long, including at least one uppercase letter, one lowercase letter and one number.");
            }
    }
    else if(mode == ModeValidator::Login)
    {
        // А тут пусто 😁
    }
}


void Validator::isFileValid(QFile &file, ModeValidator modeIO)
{
    if (modeIO == ModeValidator::WriteFile) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qWarning() << "Не удалось открыть файл для записи:" << file.fileName();
            Logger->write("Не удалось открыть файл для записи");
            throw std::invalid_argument("Ошибка: не удалось открыть файл для записи.");
        }
    }
    else if (modeIO == ModeValidator::ReadFile) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Не удалось открыть файл для чтения:" << file.fileName();
            Logger->write("Не удалось открыть файл для чтения");
            throw std::invalid_argument("Ошибка: не удалось открыть файл для чтения.");
        }
    }
    else if (modeIO == ModeValidator::Delete) {
        if (!file.open(QIODevice::Truncate | QIODevice::Text)) {
            qWarning() << "Не удалось открыть файл для удаления:" << file.fileName();
            Logger->write("Не удалось открыть файл для удаления");
            throw std::invalid_argument("Ошибка: не удалось открыть файл для удаления.");
        }
    }
}

std::optional<double> Validator::ValidOptional(const QString& scoreStr)
{

    if (scoreStr.trimmed().isEmpty()) {
        return std::nullopt;
    }

    bool ok = false;
    double val = scoreStr.toDouble(&ok);

    if (!ok) {
        throw std::invalid_argument("NON Correct score");
        return std::nullopt;
    }

    return val;
}


