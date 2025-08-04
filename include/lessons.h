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
#include"../include/Student.h"

//enum class LessonsEnum
//{
//	Math,
//	History,
//	Information,
//	Ximia,
//	Geometry,
//	Physics,
//	Letarytyre
//}; 

class Lessons : public Student
{
private:
	short grade = 0;
	std::string book;

	static std::vector<std::string> lesson;

public:

	Lessons(const std::string& NameGradeBook, const std::string& nameStudent, double ball) : book(NameGradeBook), Student(nameStudent, ball)
	{

	};

	void setGradeStudent(const std::string& fileStudents, const std::string& less);

};
