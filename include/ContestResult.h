/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef CONTESTRESULT_H
#define CONTESTRESULT_H
#include"Libs.h"
#include"Student.h"
#include<unordered_map>
#include<QString>
#include"Libs.h"

struct ContestResult // класс для хранения студентов
{
    // После 9
    std::vector<std::shared_ptr<Student>> budget;

    std::vector<std::shared_ptr<Student>> contract;

    std::vector<std::shared_ptr<Student>> reject; // те кто не постпли

    //Для конкурса высший балл среди студентов
    std::vector<std::shared_ptr<Student>> winnerInfo;

    // Еге
    std::vector<std::shared_ptr<Student>> budgetEge;

    std::vector<std::shared_ptr<Student>> contractEge;

    std::vector<std::shared_ptr<Student>> rejectEge; // те кто не постпли


};
#endif // CONTESTRESULT_H
