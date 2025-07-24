#pragma once
#include"../include/Libs.h"
#include"../include/Logger.h"
#include<QIcon>

struct Student
{
    std::string name = "";
    double ball = 0.0;


    Student() = default;

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

    friend bool operator==(const Student& s, const std::pair<std::string, double>& item)
    {
        return s.name == item.first && s.ball == item.second;
    }

};


