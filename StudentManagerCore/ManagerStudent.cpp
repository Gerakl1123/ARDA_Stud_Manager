/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include"ManagerStudent.h"
#include "../Loader.h"
#include"../LogicOperation.h"
#include<QFile>

bool Stud::findStudent(const QString &nameF, const QString &name, std::optional<double> value = std::nullopt)
{

    Students.clear();

    Students = StudentLoader::loadStudentsFromFile(nameF);

    auto result = std::find_if(Students.cbegin(),Students.cend(),[&](const Student& s)
     {
         if (value.has_value())
             return s.name == name && s.ball == value.value();
         else
             return s.name == name;
     });

    if (result != Students.cend()) {
        *Logger << "Студент найден: " + result->name + " " + QString::number(result->ball);
        return true;
    } else {
        *Logger << "Студент не найден: " + name + (value ? " " + QString::number(value.value()) : "");
        return false;
    }




}

//Fix
//=====================================

bool Stud::uploadDataToFile(const QString &file, const QString &data)
{

    QFile ofile(file);
    LogicOperation::ValidFile(ofile,ModeValidator::WriteFile);


    QTextStream iss(const_cast<QString*>(&data));
    QString line = iss.readAll().trimmed();
    iss.seek(0);

    QTextStream out(&ofile);

    QString name = "";
    double ball = 0.0;
    iss >> name >> ball;

    QStringList datas = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    if(datas.size() == 2){
        out << name << " " << ball << "\n";
        *Logger << "Успешно добавлен " << name << " " << std::to_string(ball);

    }
    else
    {
        QMessageBox::information(nullptr,"Ошибка","Неверный формат входных данных");
        return false;
    }



    return true;
}

bool Stud::SortStudent(const QString& Ofile,const QString& Ifile)
{

    uploadInfoStud(Ifile); // rezerv upload data stud

    cast(); // input rezerv data to vector students

    if(Students.empty())
    {
        return false;
    }
    std::sort(this->Students.begin(), this->Students.end(), [](const Student& a, const Student& b) {
        return a.ball > b.ball;
    });

    rezerv_info_stud.clear();

    for (const auto& st : Students)
    {
        rezerv_info_stud.emplace(st.name, st.ball);
    }

    Logger->write("Sorsted Seccuful!");


    uploadReadyFile(Ofile);

    return true;

}
//PRIVATE METHODS

void Stud::uploadInfoStud(const QString& file)
{
    QString line;

    QFile ifile(file);
    LogicOperation::ValidFile(ifile,ModeValidator::ReadFile);
    QTextStream in(&ifile);

    while (!in.atEnd())
    {
        line = in.readLine();

        if (line.isEmpty()) continue;

        QTextStream iss(&line);
        QString name;
        double ball;

        iss >> name >> ball;

        if (!(iss.status() == QTextStream::Ok)) {
            *Logger << "Неверный формат игнорирование " + line;
            continue;
        }

        if (!std::isfinite(ball)) {
            *Logger << "Неверный балл игнор " + name + ": " + QString::number(ball);
            continue;
        }

       rezerv_info_stud.emplace(name, ball);
    }

    Logger->write("Successful Backup!");
    ifile.close();
}

void Stud::cast()
{
    Students.clear();

    for(auto it = rezerv_info_stud.begin(); it!= rezerv_info_stud.end(); ++it){

        const QString& name = it.key();
        double ball = it.value();

        if (std::isfinite(ball))
        {
            Students.emplace_back(name, ball);
        }
        else
        {
            *Logger << "Балл не верный " + name + ": " + QString::number(ball);
        }
    }

    Logger->write("Каст прошел успешно");


}

void Stud::uploadReadyFile(const QString &file)
{
    QFile ofile(file);
    LogicOperation::ValidFile(ofile,ModeValidator::DeleteWrite);

    QTextStream out(&ofile);
    for (const auto& st : Students)
       out << st.name << " " << st.ball << "\n";

    Logger->write("Загружены сортированные данные в файл ");


    rezerv_info_stud.clear();
    Students.clear();
}
//==============END PRIVATE METHODS=====================

QString Stud::PrintSortStud(const QString &file)
{
    QFile ifile(file);
    LogicOperation::ValidFile(ifile,ModeValidator::ReadFile);

    QTextStream in(&ifile);
    QString line {};
    Stud::id = 0;
    Key.clear();

    while (!in.atEnd())
    {
        line = in.readLine();
        QTextStream iss(&line);

        Student s;

        iss >> s.name >> s.ball;

        if (iss.status() == QTextStream::Ok) {
            Key[++id] = s;

        }
    }


    ifile.close();

    QString result;
    QTextStream oss(&result);

    for (const auto& [k, stud] : Key) // c++ 17
    {
        oss << k << ") " << stud.name << " - "
            << qSetRealNumberPrecision(2) << stud.ball << "\n";

    }

    Logger->write("Output data to Student!");

    return result;
}



bool Stud::DeleteStudentFromFile(const QString &filename, const QString &targetName, std::optional<double> targetBall = std::nullopt)
{

    QFile ifile(filename);
    LogicOperation::ValidFile(ifile,ModeValidator::ReadFile);

    bool targetDelete = false;
    QString line;
    QTextStream in(&ifile);

    std::vector<QString> filter;

    while (!in.atEnd())
    {
        line = in.readLine();

        QTextStream iss(&line);

        QString name;
        double ball;

        iss >> name >> ball;
        if(iss.status() == QTextStream::Ok)
        {

            targetDelete = (name == targetName) && (!targetBall || std::abs(ball - *targetBall) < 1e-6);
            // если имена схожи и нету балла (true) или он есть и его абсолютная цира меньше 0.000001 тк это double тут нет 0 если нет то false


            if (targetDelete)
            {
                *Logger << "Удален студент: " + name + (targetBall.has_value() ? " " + QString::number(targetBall.value()) : QString());


            }else
            {
                filter.emplace_back(line);
            }

        }else
        {
            continue;
        }


    }

    ifile.close();

    QFile ofile(filename);
    LogicOperation::ValidFile(ofile,ModeValidator::DeleteWrite);
    QTextStream out(&ofile);

    for (const auto& s : filter)
    {
        out << s << "\n";
    }
    ofile.close();


    return targetDelete;
}

