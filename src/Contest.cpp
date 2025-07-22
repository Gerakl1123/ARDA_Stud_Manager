#include "Contest.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

std::vector<Student> ContestBase::loadStudentsFromFile(const QString& fileName)
{
    std::ifstream ifile(fileName.toStdString());
    std::vector<Student> vecStudentTemp;

    std::string temp, name;
    double ball = 0.0;

    while (std::getline(ifile, temp))
    {
        std::istringstream iss(temp);
        iss >> name >> ball;
        vecStudentTemp.emplace_back(name, ball);
    }

    return vecStudentTemp; //auto  RVO
}

std::shared_ptr<std::ofstream>& ContestBase::readWinStudent(std::shared_ptr<std::ofstream>& file, Student& res)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_s(&tm, &t);

    *ofile << "Win! " << res.name << " " << res.ball << " ";

    *ofile << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] " << "\n";

    return file;
}
