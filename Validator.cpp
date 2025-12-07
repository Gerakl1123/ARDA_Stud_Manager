/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include"Validator.h"
#include<QRegularExpression>
#include"LogicOperation.h"

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
    if (file.isOpen()) {
        file.close();
    }


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
    }else if(modeIO == ModeValidator::DeleteWrite)
    {
        if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
            qWarning() << "Не удалось открыть файл для удаления и перезаписи:" << file.fileName();
            Logger->write("Не удалось открыть файл для удаления и перезаписи");
            throw std::invalid_argument("Ошибка: не удалось открыть файл для удаления и перезаписи.");
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

QString Validator::SwitchAppContest(const ModeSerelization& mode)
{
    static const QMap<ModeSerelization, QString> mapApp
    {
        { ModeSerelization::Attestat, "AttestatContest" },
        { ModeSerelization::MaxScore, "MaxScoreContest" },
        { ModeSerelization::ManagerStudent, "ManagerStudent" }
    };

    return mapApp.value(mode, {});
}



bool Validator::IsObjectForMode(const QString &objectName,const ModeSerelization &mode)
{
    switch (mode) {
    case ModeSerelization::Attestat:
        return objectName.contains("_Attestat_");
    case ModeSerelization::MaxScore:
        return objectName.contains("_MaxScore_");
    case ModeSerelization::ManagerStudent:
        return objectName.contains("_ManagerStudent_");
    default:
        return false;
    }
}

QString Validator::SwitchAppGradesMenu(const ModeSerelization& mode)
{
    static const QMap<ModeSerelization,QString> myApp
    {
        { ModeSerelization::Lessons, "Lessons" },
        { ModeSerelization::Projects, "Projects" },
        { ModeSerelization::Records, "Records" }
    };

    return myApp.value(mode,{});
}

bool Validator::ValidWorkData(const QString &name,const QDate &date, const QTime &time, const QString &priority)
{
    if (name.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Введите название работы");
        return false;
    }

    if (!date.isValid()) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверная дата");
        return false;
    }

    if (!time.isValid()) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверное время");
        return false;
    }

    if (priority.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Выберите приоритет");
        return false;
    }

    if (date < QDate::currentDate()) {
        QMessageBox::warning(nullptr, "Ошибка", "Дата не может быть в прошлом");
        return false;
    }

    return true;
}

bool Validator::validIDJson(const QString &fileName,const QString& TargetID)
{

    QFile file(fileName);

    if(file.size() == 0)
    {
        file.close();
        return true;
    }

    try
    {
        isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::invalid_argument& err)
    {
        qDebug() << err.what();
        return false;
    }


    QByteArray bArr = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(bArr);
    QJsonArray arr = doc.array();

    for(const auto a : arr)
    {
        if (!a.isObject()) continue;
        QJsonObject obj = a.toObject();

        QString ID = obj["ID"].toString();

        if(!ID.isEmpty() && ID == TargetID)
        {
            return false;
        }
    }
    file.close();

    return true;
}


