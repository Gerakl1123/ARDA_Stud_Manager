#pragma once
#include"../include/Libs.h"
#include <functional>
#include"../include/Logger.h"
#include "../include/Student.h"
#include<chrono>


class BaseContest {
public:
    BaseContest() = default;
    BaseContest(const std::string& contest, const std::string& LogFILE) : Contest(contest)
    {
        Logger = Log::create(LogFILE);
    };
	BaseContest(const std::string& contest, std::vector<Student>& otherStudent, const std::string& LogFILE)
		: Contest(contest), CurretStudents(otherStudent)
	{
		Logger = Log::create(LogFILE);
	};

    virtual QString currentContest(const std::string&,const std::string&) = 0;
    virtual	qint64 ContestBudget(double, const std::string&, const std::string&,QString& )  = 0;

	~BaseContest() = default;

protected:
	std::string Contest;
    QString FakyltetMain;

	static std::vector<std::string> contestVec;
	std::vector<Student> CurretStudents;
	 std::shared_ptr<Log> Logger;
	static std::vector<std::string> createContest();
	std::shared_ptr<std::ofstream> ofile;

};


class CurrentContest : public BaseContest
{
public:
    CurrentContest() = default;
    CurrentContest(const std::string& contest,const std::string& LogFILE) : BaseContest(contest,LogFILE){};
    CurrentContest(const std::string& contest, std::vector<Student>& otherStudent, const std::string& FILE)
		: BaseContest(contest, otherStudent, FILE) {

	};

    QString currentContest(const std::string& File,const std::string& FILEinput) override;
    qint64 ContestBudget(double score, const std::string& File, const std::string& SaveFile,QString& Fakyltet) override;

private:
    std::shared_ptr<std::ofstream>& readWinStudent(std::shared_ptr<std::ofstream>&,Student&);
    std::vector<Student> loadStudentsFromFile(const std::string&);

};
