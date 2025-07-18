#pragma once
#include"../include/Libs.h"
#include <functional>
#include"../include/Logger.h"
#include "../include/Student.h"

class BaseContest {
public:

	BaseContest() = default;
	BaseContest(const std::string& contest, std::shared_ptr<std::vector<Student>>& otherStudent, const std::string& LogFILE)
		: Contest(contest), CurretStudents(otherStudent)
	{
		Logger = Log::create(LogFILE);
	};

	virtual std::string currentContest(const std::string&) = 0;
    virtual	qint64 ContestBudget(double, const std::string&, const std::string&,QString& )  = 0;

	~BaseContest() = default;

protected:
	std::string Contest;
    QString FakyltetMain;

	static std::shared_ptr<std::vector<std::string>> contestVec;

	std::shared_ptr<std::vector<Student>> CurretStudents;

	 std::shared_ptr<Log> Logger;

	static std::shared_ptr<std::vector<std::string>> createContest();

	std::shared_ptr<std::ofstream> ofile;

};


class CurretContest : public BaseContest
{
public:
	CurretContest() = default;
	CurretContest(const std::string& contest, std::shared_ptr<std::vector<Student>>& otherStudent, const std::string& FILE)
		: BaseContest(contest, otherStudent, FILE) {

	};

	std::string currentContest(const std::string& File) override;

    qint64 ContestBudget(double score, const std::string& File, const std::string& SaveFile,QString& Fakyltet) override;


};
