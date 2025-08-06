/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */



#ifndef ATTESTATCONTEST_H
#define ATTESTATCONTEST_H
#include"Contest.h"

class AttestatContest : public IAttestatContest
{
    std::vector<std::shared_ptr<Student>> students;

public:
    void setStudents(const std::vector<std::shared_ptr<Student>>& students) override;

    ContestResult evaluate(double budgetThreshold,double contractThreshold,int budgetSlots) override;

};

#endif // ATTESTATCONTEST_H
