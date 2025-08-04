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
#include<fstream>
#include<chrono>
#include<iomanip>
#include<iostream>
#include<string>
#include <memory>

class Stud;
class StudFileMngr;


class Log
{
	friend class Stud;
	friend class StudFileMngr;

private:
	std::ofstream logFile;


	Log(const std::string& nameFile)
	{
		logFile.open(nameFile, std::ios::app);
	};


public:

	static std::shared_ptr<Log> create(const std::string& nameFile)
	{
		return std::shared_ptr<Log>(new Log(nameFile));
	}

	void write(const std::string& msg);

    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

	~Log()
	{
		logFile.close();
	}

};
