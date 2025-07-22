#include"TopBallContest.h"

Student TopContest::TopBall(const QString &ifile, const QString &saveFile)
{
    Students = std::vector<Student>();

    Students = loadStudentsFromFile(ifile);

    if (Students.empty()) {
        logger->write("No students to compare.\n");
        return Student();
    }

    ofile = std::make_shared<std::ofstream>(saveFile.toStdString(), std::ios::app);
    if (!ofile->is_open()) {
        logger->write("Failed to open save file.\n");
        return Student();
    }


    auto res = std::max_element(Students.begin(), Students.end(), [](const Student& s1, const Student& s2)
                                {
                                    return s1.ball < s2.ball;
                                });


    ofile = readWinStudent(ofile, *res);

    logger->write("Winner: " + res->name + " with score " + std::to_string(res->ball));

    return {res->name, res->ball};

}
qint16 TopContest::findWinner(double score, const QString& file, const QString& saveFile, QString& faculty)
{
    // просто заглушка
    return 0;
}
