/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "../include/Logger.h"
#include<QMessageBox>
void Log::write(const std::string& msg)
{

	if (!logFile.is_open()) {
		std::cerr << "[Log error] Файл лога не открыт\n";
		return;
	}

	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm tm;
	localtime_s(&tm, &t);

	logFile << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] " << msg << "\n";

	logFile.flush();

	if (!logFile)
        QMessageBox::warning(nullptr,"[Log error]","Не удалось записать в лог");


}
