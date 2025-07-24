#ifndef CONTEST_H
#define CONTEST_H

#include <vector>
#include <QString>
#include <memory>
#include <fstream>
#include <chrono>
#include "../include/Libs.h"
#include "../include/Logger.h"
#include "../include/Student.h"



class ContestBase
{

protected:
    QString description;
    QString contestNames;
    float strength;
    QString Faculty;  // исправлено
    std::vector<Student> Students;
    std::shared_ptr<Log> logger;
    std::shared_ptr<std::ofstream> ofile;
   // ContestType contestType;

public:
    ContestBase() = delete;

    ContestBase(const std::string& logFile)
        : logger(Log::create(logFile)) {
    }

    virtual ~ContestBase() = default;



public:
    virtual std::shared_ptr<std::ofstream>& readWinStudent(std::shared_ptr<std::ofstream>& ofile, Student& res) final;
    static std::vector<Student> loadStudentsFromFile(const QString& fileName);

    virtual qint16 findWinner(double score, const QString& file,  const QString& saveFile, QString& faculty) = 0;

};

#endif // CONTEST_H

