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
#include<QString>
#include <sstream>

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
    template<typename T>
    Log& operator<<(const T& msg)
    {
        std::ostringstream oss;
        oss<<msg;
        write(oss.str());
        return *this;
    }

    Log& operator<<(const QString& msg)
    {
        write(msg.toStdString());
        return *this;
    }


    template<typename T>
    inline static std::shared_ptr<Log> create(const T& nameFile)
    {
        constexpr bool is_type =
            std::is_constructible_v<std::string, T> ||
            std::is_same_v<T, QString>;

        static_assert(is_type,
                      "Log::create() не поддерживает данный тип");

        if constexpr(std::is_same_v<T, QString>)
        {
            return std::shared_ptr<Log>(new Log(nameFile.toStdString()));
        }
        else
        {
            return std::shared_ptr<Log>(new Log(std::string(nameFile)));
        }
	}


    void write(const std::string_view& msg);

    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

	~Log()
	{
		logFile.close();
	}

};
