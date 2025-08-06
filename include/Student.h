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
#include"../include/Libs.h"
#include"../include/Logger.h"
#include<QIcon>
#include"QString"

struct Student
{
    std::string name = "";
    double ball = 0.0;
    QString Fakulty;

    Student() = default;

    QString name_;
    QVector<QString> grades_;

    Student( QString& name, QVector<QString>& grades)
        : name_(name), grades_(grades) {};


    Student(const std::string& n, double b) : name(n), ball(b) {};



    bool operator<(const Student& other) const {
        return name < other.name;
    }

    bool operator==(const Student& other)  {
        return name == other.name && ball == other.ball;
    }
    bool empty() const
    {
        return this->name.empty() || this->ball == 0.0;
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


