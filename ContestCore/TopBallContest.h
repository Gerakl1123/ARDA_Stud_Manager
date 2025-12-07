/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef TOPBALLCONTEST_H
#define TOPBALLCONTEST_H

#include"Contest.h"
#include"../StudentManagerCore/Student.h"

class TopBallContest : public IMaxContest
{
private:
    std::vector<std::shared_ptr<Student>> Students;

public:
    void setStudents(const std::vector<std::shared_ptr<Student>>& students) override;

    ContestResult MaxScore() override;

};

#endif // TOPBALLCONTEST_H
