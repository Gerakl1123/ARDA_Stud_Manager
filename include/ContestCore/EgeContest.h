#ifndef EGECONTEST_H
#define EGECONTEST_H
#include"Contest.h"
#include<vector>
#include<memory>


class Ege : public IEgeContest
{
    std::vector<std::shared_ptr<Student>> students; // для сохранения информации все студентов

public:
    void setStudents(const std::vector<std::shared_ptr<Student>>& students) override;


    ContestResult evaluateEge(double budgetThreshold, double contractThreshold, int budgetSlots) override;

};


#endif // EGECONTEST_H
