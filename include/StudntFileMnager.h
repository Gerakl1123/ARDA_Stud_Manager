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
#include<string>
#include<memory>
#include <filesystem>
#include<ManagerStudent.h>
#include"../include/Logger.h"

namespace fs = std::filesystem;

class Stud;
class Log;

class StudFileMngr {


public:

	std::shared_ptr<Log> Logger;
	explicit StudFileMngr(const std::string& file)
		: Logger(Log::create(file)) {
	};



	void CreateDir(std::string& path_dir, const std::string& NameFolder, const std::string nameFileToUploadData, Stud& other, const std::string& fileNameInputData) const;
	uintmax_t SizeFileByte(std::string& path_dir);
};
