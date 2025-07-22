#include "AttestatContest.h"

qint16 Attestat::findWinner(double ball, const QString &file, const QString &saveFile, QString &faculty)
{

    std::vector<Student> StudentsOnBudget =std::vector<Student>();

    Students = std::vector<Student>();

    ofile = std::make_shared<std::ofstream>(saveFile.toStdString(), std::ios::app);

    Students = loadStudentsFromFile(file);

    std::copy_if(this->Students.begin(), this->Students.end(), std::back_inserter(StudentsOnBudget),
                 [ball](const Student& s) {
                     return s.ball >= ball;
                 });

    qint16 countStudents = static_cast<qint16>(StudentsOnBudget.size());

    *ofile << " !!! " << faculty.toStdString() << " !!! " << "\n";
    logger->write(Students.at(2).name);
    for (const auto& c : StudentsOnBudget)
    {
        *ofile << c.name << " " << c.ball << "\n";

    }
    this->logger->write("Seccuful find students on budget " + faculty.toStdString() + " " + std::to_string(countStudents) + " людей!\n");

    return countStudents;
}

