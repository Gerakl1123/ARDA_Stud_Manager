
#include "../include/Contest.h"
#include<algorithm>
#include<vector>
#include<QDebug>

std::vector<std::string> BaseContest::createContest()
{
    return std::vector<std::string>(
        std::initializer_list<std::string>
            {"Sportakiada", "certificate", "Hackathon"}
    );
}

std::vector<std::string> BaseContest::contestVec = BaseContest::createContest();

std::shared_ptr<std::ofstream>& CurrentContest::readWinStudent(std::shared_ptr<std::ofstream>& file,Student& res)
{

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_s(&tm, &t);

    *ofile << "Win! " << res.name << " " << res.ball << " ";

    *ofile << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] " << "\n";

    return file;
}

std::vector<Student> CurrentContest::loadStudentsFromFile(const std::string& fileName)
{

    std::ifstream ifile(fileName);
    std::vector<Student> vecStudentTemp = std::vector<Student>();

    std::string temp,name;
    double ball;

    while(std::getline(ifile,temp))
    {
        std::istringstream iss(temp);
        iss >> name>>ball;
        vecStudentTemp.emplace_back(name,ball);
    }

    return std::move(vecStudentTemp);

}

QString CurrentContest::currentContest(const std::string& SaveFile,const std::string& ifile)
{

    CurretStudents = std::vector<Student>();

    if (contestVec.empty()) Logger->write("contestVec is empty!");
    if (CurretStudents.empty()) Logger->write("CurretStudents is empty!");
    if (!Logger) std::cerr << "Logger is nullptr!\n";


    if (contestVec.empty())
    {
        contestVec = createContest();
        Logger->write("Create Contest!");

    }
        
    ofile = std::make_shared<std::ofstream>(SaveFile, std::ios::app);

    if (std::find(contestVec.cbegin(), contestVec.cend(), Contest) == contestVec.end()) {
        std::cerr << "No Contest!\n";
        Logger->write("Unknown contest: " + Contest);
        return "";
    }
    

    if (Contest != "certificate") {
        Logger->write("Contest '" + Contest + " <No logic>");
        return "";
    }

    Logger->write("Processing certificate contest");


    CurretStudents = loadStudentsFromFile(ifile);

    if (CurretStudents.empty() || CurretStudents.empty()) {
        Logger->write("No students to compare.\n");
        return"";
    }
    //Logic find winner
    auto res = std::max_element(CurretStudents.begin(), CurretStudents.end(), [](const Student& s1, const Student& s2)
    {
        return s1.ball < s2.ball;
    });

    ofile = readWinStudent(ofile,*res);

    Logger->write("Winner: " + res->name + " with score " + std::to_string(res->ball));


    QString nameWinner = QString::fromStdString(res->name);

   // ofile->close();

    return nameWinner;
}

qint64 CurrentContest::ContestBudget(double score, const std::string& iFile, const std::string& SaveFile,QString& Fakyltet)
{
    std::vector<Student> StudentsOnBudget = std::vector<Student>();
    CurretStudents = std::vector<Student>();

    ofile = std::make_shared<std::ofstream>(SaveFile, std::ios::app);

    CurretStudents= loadStudentsFromFile(iFile);

    std::copy_if(CurretStudents.begin(), CurretStudents.end(), std::back_inserter(StudentsOnBudget),
                 [score](const Student& s) {
                     return s.ball >= score;
    });

    qint64 countStudents = static_cast<qint64>(StudentsOnBudget.size());

    *ofile << " !!! " << Fakyltet.toStdString()<<" !!! " <<"\n";

    for (const auto& c : StudentsOnBudget)
    {

        *ofile << c.name << " " << c.ball << "\n";
    }
    
    //ofile->close();

    return countStudents;
}
