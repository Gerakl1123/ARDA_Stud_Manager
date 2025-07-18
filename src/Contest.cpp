
#include "../include/Contest.h"
#include<algorithm>
#include<vector>
std::shared_ptr<std::vector<std::string>> BaseContest::contestVec = nullptr;

std::shared_ptr<std::vector<std::string>> BaseContest::createContest()
{
    return std::make_shared<std::vector<std::string>>(
        std::initializer_list<std::string>
            {"Sportakiada", "certificate", "Hackathon"}
    );
}


std::string CurretContest::currentContest(const std::string& File)
{
    if (contestVec == nullptr)
    {
        contestVec = createContest();
        Logger->write("Create Contest!");

    }
        
    ofile = std::make_shared<std::ofstream>(File, std::ios::app);

    if (std::find(contestVec->cbegin(), contestVec->cend(), Contest) == contestVec->end()) {
        std::cerr << "No Contest!\n";
        Logger->write("Unknown contest: " + Contest);
        return "";
    }
    

    if (Contest != "certificate") {
        Logger->write("Contest '" + Contest + " <No logic>");
        return "";
    }

    Logger->write("Processing certificate contest");

    if (!CurretStudents || CurretStudents->empty()) {
        Logger->write("No students to compare.\n");
        return"";
    }
    //Logic find winner
    auto res = std::max_element(CurretStudents->begin(), CurretStudents->end(), [](const Student& s1, const Student& s2)
    {
        return s1.ball < s2.ball;
    });

    
    *ofile << "Win! " << res->name << " " << res->ball << "\n";

    Logger->write("Winner: " + res->name + " with score " + std::to_string(res->ball));


   // ofile->close();

    return res->name;
}

qint64 CurretContest::ContestBudget(double score, const std::string& File, const std::string& SaveFile,QString& Fakyltet)
{
    std::vector<Student> StudentsOnBudget = std::vector<Student>();
    CurretStudents = std::make_shared<std::vector<Student>>();

    ofile = std::make_shared<std::ofstream>(SaveFile, std::ios::app);
    std::ifstream ifile(File);

    std::string temp,name;
    double ball;
    while(std::getline(ifile,temp))
    {
        std::istringstream iss(temp);
        iss >> name>>ball;
        CurretStudents->emplace_back(name,ball);
    }

    std::copy_if(CurretStudents->begin(), CurretStudents->end(), std::back_inserter(StudentsOnBudget),
                 [score](const Student& s) {
                     return s.ball >= score;
    });

    int countStudents = static_cast<qint64>(StudentsOnBudget.size());

    *ofile << " !!! " << Fakyltet.toStdString()<<" !!! " <<"\n";

    for (const auto& c : StudentsOnBudget)
    {

        *ofile << c.name << " " << c.ball << "\n";
    }
    
    //ofile->close();

    return countStudents;
}
