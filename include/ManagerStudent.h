#ifndef MANAGERSTUDENT_H
#define MANAGERSTUDENT_H

#include"Libs.h"
#include"Logger.h"
#include"Student.h"
#include"Contest.h"
#include<optional>
#include<QString>
#include<QCryptographicHash>
#include<QByteArray>

class StudFileMngr;
class Lessons;
class Log;

class Stud {
    friend class StudFileMngr;
    friend class Lessons;

    friend void swap(Stud& lhs, Stud& rhs);

public:

    explicit Stud(const std::string& file)
        : Logger(Log::create(file))
    {
    };

    Stud() = delete;

public:
    void SortStudent(const QString& ofile,const QString& Ifile);
    bool uploadDataToFile(const std::string& file, const std::string& data);
    QString PrintSortStud(const std::string& file);
    bool DeleteStudentFromFile(const std::string&, const std::string&, std::optional<double> );
    bool findStudent(const std::string&, const std::string&, std::optional<double>);
    bool registerStudent(std::string& login, std::string password);
    bool loginStudent(std::string& login, std::string password);

    //=====
    bool DeleteStudent(size_t index);
    void SwapStudents(size_t index, size_t index2);
    void RezervSort();

private:
    void uploadInfoStud(const std::string& file);
    void cast();
    void uploadReadyFile(const std::string& file);
    QString hashPass(const std::string&);
    // QString DeHashPass(std::string&);  не нужен
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
