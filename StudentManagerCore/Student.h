/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#pragma once
#include"../Libs.h"
#include"../Logger.h"

// OLD CODE НЕ ТРОГАЙ И ТАК РАБОТАЕТ
struct Student
{
    QString name = "";
    double ball = 0.0;

    Student() = default;


    Student(const QString& n, double b) : name(n), ball(b)
    {

    }



    bool operator<(const Student& other) const {
        return name < other.name;
    }

    bool operator==(const Student& other)  {
        return name == other.name && ball == other.ball;
    }
    bool empty() const
    {
        return this->name.isEmpty() || this->ball == 0.0;
    }

    Student& operator=(const Student& other)
    {
        if(this != &other)
        {
            name = other.name;
            ball= other.ball;
        }
        return *this;
    }

};


