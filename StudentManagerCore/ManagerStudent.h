/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef MANAGERSTUDENT_H
#define MANAGERSTUDENT_H

#include"../Libs.h"
#include"../Logger.h"
#include"Student.h"
#include<optional>
#include<QString>
#include<QHash>


class StudFileMngr;
class Lessons;

class Stud {
    friend class StudFileMngr;
    friend class Lessons;

    friend void swap(Stud& lhs, Stud& rhs);

public:

    explicit Stud(std::shared_ptr<Log> logger)
        : Logger(logger)
    {
    }

    Stud() = delete;

public:
    bool SortStudent(const QString& ofile,const QString& Ifile);
    bool uploadDataToFile(const QString& file, const QString& data);
    QString PrintSortStud(const QString& file);
    bool DeleteStudentFromFile(const QString&, const QString&, std::optional<double> );
    bool findStudent(const QString&, const QString &, std::optional<double>);

    //=====
   // bool DeleteStudent(size_t index);
   // void RezervSort();

private:
    void uploadInfoStud(const QString& file);
    void cast();
    void uploadReadyFile(const QString& file);
private:

    std::vector<Student> Students;

    QHash<QString, double> rezerv_info_stud;
    std::vector<Student> BackUpStud;
    std::map<size_t, Student> Key;
    std::shared_ptr<Log> Logger;
    static inline size_t id = 1;
};


inline void swap(Stud& lhs, Stud& rhs)
{

    using std::swap;
    swap(lhs.rezerv_info_stud, rhs.rezerv_info_stud);
    swap(lhs.Students, rhs.Students);
    swap(lhs.BackUpStud, rhs.BackUpStud);
    swap(lhs.Key, rhs.Key);
}
#endif // MANAGERSTUDENT_H
