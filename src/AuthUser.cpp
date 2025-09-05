/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "../include/AuthUser.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QIODevice>
#include"../include/Loader.h"

QString UserAuthenticator::hashPass(const QString& password) {
    QByteArray ba = password.toUtf8();
    QByteArray hashed = QCryptographicHash::hash(ba, QCryptographicHash::Sha256);
    return QString(hashed.toHex());
}

bool UserAuthenticator::registerStudent(const QString& login, const QString& password) {

    //Проверка логина и пароля
    try {
        Validator::verifyLoginAndPassword(login, password, ModeValidator::Register);
    } catch (const std::invalid_argument& e) {
        QMessageBox::warning(nullptr, "Ошибка валидации", e.what());
        return false;
    }

    QString fileName = "DATALP.txt";

    //Проверка доступности файла на запись
    if (!isFileWritable(fileName)) {
        QMessageBox::warning(nullptr, "Ошибка файла", "Не удалось открыть файл для записи ");
        return false;
    }

    //Проверка что логин не существует
    if (StudentLoader::isLoginExists(login, fileName)) {
        logger->write("Попытка регистрации существующего логина: " + login.toStdString());
        QMessageBox::warning(nullptr, "Ошибка", "Такой логин уже существует");
        return false;
    }

    //Хешируем пароль
    QString hashedPassword = hashPass(password);

    //Сохраненяем данные
    if (!StudentLoader::saveLoginPassword(login, hashedPassword, fileName)) {
        logger->write("Ошибка при записи логина: " + login.toStdString());
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось сохранить пользователя");
        return false;
    }

    logger->write("Зарегистрирован новый пользователь: " + login.toStdString());
    return true;
}

bool UserAuthenticator::loginStudent(const QString& login, const QString& password) {


    QString fileName = "DATALP.txt";

    if (!isFileReadtable(fileName)) {
        QMessageBox::warning(nullptr, "Ошибка файла", "Не удалось открыть файл для чтения.");
        return false;
    }

    if(StudentLoader::ReadLoginPassword(login,password))
    {
         logger->write("Success login to account " + login.toStdString());
        return true;
    }



    return false;
}

bool UserAuthenticator::isFileWritable(const QString& fileName) {
    QFile file(fileName);
    try {
        Validator::isFileValid(file, ModeValidator::WriteFile);
        file.close();
    } catch (const std::invalid_argument& e) {
        logger->write(QString("Ошибка открытия файла для записи: %1").arg(e.what()).toStdString());
        return false;
    }
    return true;
}

bool UserAuthenticator::isFileReadtable(const QString& fileName)
{
    QFile file(fileName);
    try {
        Validator::isFileValid(file, ModeValidator::ReadFile);
        file.close();
    } catch (const std::invalid_argument& e) {
        logger->write(QString("Ошибка открытия файла для чтения: %1").arg(e.what()).toStdString());
        return false;
    }
    return true;
}
