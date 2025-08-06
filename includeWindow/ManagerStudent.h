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

#include"Libs.h"
#include"Logger.h"
#include"Student.h"
#include<optional>
#include<QString>


class StudFileMngr;
class Lessons;

class Stud {
    friend class StudFileMngr;
    friend class Lessons;

    friend void swap(Stud& lhs, Stud& rhs);

public:

    explicit Stud(std::shared_ptr<Log> logger)
        :Logger(logger)
    {
    };

    Stud() = delete;

public:
    bool SortStudent(const QString& ofile,const QString& Ifile);
    bool uploadDataToFile(const std::string& file, const std::string& data);
    QString PrintSortStud(const std::string& file);
    bool DeleteStudentFromFile(const std::string&, const std::string&, std::optional<double> );
    bool findStudent(const std::string&, const std::string&, std::optional<double>);

    //=====
    bool DeleteStudent(size_t index);
    void RezervSort();

private:
    void uploadInfoStud(const std::string& file);
    void cast();
    void uploadReadyFile(const std::string& file);
private:

    std::vector<Student> Students;

    std::unordered_multimap<std::string, double> rezerv_info_stud;
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
