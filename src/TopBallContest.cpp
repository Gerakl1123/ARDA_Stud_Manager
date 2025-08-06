/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include"../include/TopBallContest.h"
#include"../include/ContestResult.h"
#include<QDebug>
void TopBallContest::setStudents(const std::vector<std::shared_ptr<Student>>& students)
{
    this->Students = students;
}


ContestResult TopBallContest::MaxScore()
{

    auto it = std::max_element(Students.begin(), Students.end(),[](const auto& a, const auto& b) {
            return a->ball < b->ball;
    });

    ContestResult result;

    if(it != Students.end())
    {
        auto topStudent = *it;

        Students.clear();
        result.winnerInfo.emplace_back(topStudent);

        qDebug() << "Winner:" << QString::fromStdString(topStudent->name) << topStudent->ball;
    }
    else
    {
        qDebug() << "No winner.";
    }

    return result;
}
