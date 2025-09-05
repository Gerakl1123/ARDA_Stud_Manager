/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "../include/AttestatContest.h"
#include <algorithm>

void AttestatContest::setStudents(const std::vector<std::shared_ptr<Student>> &students)
{
    this->students = students;
}

ContestResult AttestatContest::evaluate(double budgetThreshold, double contractThreshold, int budgetSlots,int contractSlots)
{
    std::sort(students.begin(), students.end(), [](const auto& a, const auto& b) {
        return a->ball > b->ball;
    });

    ContestResult result;

    for (const auto& s : students)
    {
        if (s->ball >= budgetThreshold && (int)result.budget.size() < budgetSlots)
            result.budget.push_back(s);
        else if (s->ball >= contractThreshold && (int)result.contract.size() < contractSlots)
            result.contract.push_back(s);
        else
            result.reject.push_back(s);
    }
    return result;
}
