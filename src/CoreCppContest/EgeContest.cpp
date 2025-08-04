#include"../include/ContestCore/EgeContest.h"
#include"../include/ContestCore/ContestResult.h"

void Ege::setStudents(const std::vector<std::shared_ptr<Student>> &students)
{
    this->students = students;
}

ContestResult Ege::evaluateEge(double budgetThreshold, double contractThreshold, int budgetSlots)
{

    std::sort(students.begin(), students.end(), [](const auto& a, const auto& b) {
        return a->ball > b->ball;
    });

    ContestResult result;

    for(const auto& s : students)
    {
        if(s->ball >= budgetThreshold&& (int)result.budgetEge.size() < budgetSlots )
        {
            result.budgetEge.push_back(s);
        }
        else if(s->ball >=contractThreshold)
        {
            result.contractEge.push_back(s);
        }
        else
        {
            result.rejectEge.push_back(s);
        }

    }

    return result;
}
