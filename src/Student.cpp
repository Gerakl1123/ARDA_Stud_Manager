#include "../include/Student.h"
#include"../include/Libs.h"
#include<cmath>
bool Stud::findStudent(const std::string& nameF, const std::string& name, std::optional<double> value = std::nullopt)
{
    if (!Logger) {
        std::cerr << "Logger не инициализирован!" << std::endl;
        return false;
    }



    Students.clear();
    std::ifstream ifile(nameF);

    if (!ifile.is_open()) {
        Logger->write("Failed open file: " + nameF);
        return false;
    }

    std::string line;
    std::string nameStud;
    double ballStud;

    while (std::getline(ifile, line)) {

        std::istringstream iss(line);

        if (!(iss >> nameStud >> ballStud)) {
            Logger->write("Неккоректная строка: " + line);
            continue;
        }

        Students.emplace_back(nameStud, ballStud);
    }


    auto result = std::find_if(Students.cbegin(),Students.cend(),[&](const Student& s)
                 {
        if (value.has_value())
            return s.name == name && s.ball == value.value();
        else
            return s.name == name;
    });

    if (result != Students.cend()) {
        Logger->write("Successful find student: " + result->name + " " + std::to_string(result->ball));
        return true;
    } else {
        Logger->write("Failed to find student: " + name + (value ? " " + std::to_string(value.value()) : ""));
        return false;
    }
}
//bool Stud::findStudent(const std::string& nameF, const std::string& name, double value)
//{
//	Students.clear();
//	std::ifstream ifile(nameF);
//	std::string line;
//	std::string nameStud;
//	double ballStud;
//
//
//
//	while (std::getline(ifile, line))
//	{
//		std::istringstream iss(line);
//		iss >> nameStud >> ballStud;
//		Stud::Students.emplace_back(nameStud, ballStud);
//
//	}
//	//std::pair <std::string, double > Key = {name,value};
//	//old solution
//	//auto result = std::find(Students.begin(), Students.end(), Key);
//	//
//	auto result = std::find_if(Students.begin(), Students.end(), [&](const Student& other)->bool {
//
//		Logger->write("Succeful find student " + name + " " + std::to_string(ballStud));
//		return other.name == name && other.ball == value;
//
//    });
//
//
//	Logger->write("Fail find student " + name + " " + std::to_string(ballStud));
//	return result != Students.end();
//
//
//}
//

// Блок Регестрации и авторизацийй + ХЕШ/DEHASH  fix 08.06.2025  update 16.07.2025 update 22 07 2025 + QCryptographicHash

QString Stud::hashPass(const std::string& password) {
    QByteArray ba = QByteArray::fromStdString(password);
    QByteArray hashed = QCryptographicHash::hash(ba, QCryptographicHash::Sha256);
    return QString(hashed.toHex());

}

bool Stud::registerStudent(std::string& login, std::string password)
{
    if (login.empty() || password.empty())
    {
        std::cerr << "Login or password is empty!\n";
        Logger->write("Fail register account " + login);
        return false;
    }

    std::ifstream logStud("data.txt");
    if (!logStud.is_open())
    {
        std::cerr << "Error opening file for reading!\n";
        return false;
    }

    std::string tempName, tempPass, tempLine;

    while (std::getline(logStud, tempLine))
    {
        std::istringstream iss(tempLine);
        iss >> tempName >> tempPass;
        if (tempName == login)
        {
            Logger->write("register account already exists: " + login);
            return false;
        }
    }

    logStud.close();

    // Хешируем пароль hashPass
    QString hashedPassword = hashPass(password);

    std::ofstream regStud("data.txt", std::ios::app);
    if (!regStud.is_open())
    {
        std::cerr << "Error opening file for writing!\n";
        return false;
    }

    regStud << login << " " << hashedPassword.toStdString() << "\n";
    Logger->write("Registered account: " + login);
    regStud.close();
    return true;
}



bool Stud::loginStudent(std::string& login, std::string password)
{
	std::ifstream logStud("data.txt");

    std::string fileUserName, filePassword;

	if (!logStud.is_open())
	{
		std::cerr << "Error not open file!\n";
		return false;
	}


	if (login.empty() || password.empty())
	{
		std::cerr << "Error!\n";
		return false;
	}

	std::string temp = "";

	while (std::getline(logStud, temp))
	{
        std::istringstream iss(temp);

        iss >> fileUserName >> filePassword;

        // Разъкешироваем пароль
        QString UnhashPass = hashPass(password);

        if (login == fileUserName && UnhashPass == QString::fromStdString(filePassword))
		{
			std::cout << " Suceful!";
			Logger->write("login to account " + login);
			return true;
		}

	}
	Logger->write("Fail login to account " + login);
	return false;
}

//======================================================================

void Stud::uploadInfoStud(const std::string& file)
{
	std::string line;
	std::ifstream ifile(file);

	while (std::getline(ifile, line))
	{
		info_stud.push_back(line);

		std::istringstream iss(line);
		std::string name;
		double ball;

		iss >> name >> ball;
		rezerv_info_stud.emplace(name, ball);
	}

	Logger->write("Successful Backup!");
	ifile.close();
}
//Fix
//=====================================
bool Stud::uploadDataToFile(const std::string& file, const std::string& data)
{
    std::ofstream ofile(file, std::ios::app);
    if (!ofile.is_open()) {
        return false;
    }

    std::istringstream iss(data);
    std::string name = "";
    double ball = 0.0;
    iss >> name >> ball;

    ofile << name << " " << std::to_string(ball) << "\n";

    // !!! Добавляем в резервную мапу
    rezerv_info_stud[name] = ball;

    Logger->write("Student successful " + name + " " + std::to_string(ball));

    cast(); // обновит Students из rezerv_info_stud
   // uploadReadyFile(file);

    return true;
}

void Stud::SortStudent()
{

    std::sort(Students.begin(), Students.end(), [](const Student& a, const Student& b) {
        return a.ball < b.ball;
        });

    rezerv_info_stud.clear();
   // Stud::i = 0;

    for (const auto& st : Students)
    {
        rezerv_info_stud.emplace(st.name, st.ball);
    }

    Logger->write("Sorsted Seccuful!");

}

void Stud::cast()
{
    Students.clear();

    for (const auto& [name, ball] : rezerv_info_stud)
    {
        if (std::isfinite(ball))
        {
            Students.emplace_back(name, ball);
        }
        else
        {
            Logger->write("Error: Invalid ball value for " + name + ": " + std::to_string(ball));
        }
    }
    Logger->write("cast Successful");
}

void Stud::uploadReadyFile(const std::string& file)
{
    std::ofstream ofile(file);

    for (const auto& [name, ball] : rezerv_info_stud)
    {
        ofile << name;
        ofile << " " << std::to_string(ball) << "\n"; // изменил double() std::to_string
    }
    Logger->write("Upload data to ready file! ");
    ofile.close();
}
//===================================

void Stud::SwapStudents(size_t index, size_t index2) // optimization
{

	std::swap(Students[index], Students[index2]); // optimization later
	Logger->write("swap Student!");
}

void Stud::RezervSort()
{
	BackUpStud.assign(Students.begin(), Students.end()); // good opt
	BackUpStud.swap(Students);

	Logger->write("BackUp 2x Student!");

}

QString Stud::PrintSortStud(const std::string& file)
{
	std::ifstream ifile(file);
	std::string line = "";
    Stud::id = 0;
	Key.clear();

	while (std::getline(ifile, line))
	{
		std::istringstream iss(line);
		Student s;
		if (iss >> s.name >> s.ball)
		{
            Key[++id] = s;
		}
	}

    std::ostringstream oss;

	for (const auto& [k, stud] : Key)
    {
        oss << k << ") " << stud.name << " - "
            << std::fixed << std::setprecision(2) << stud.ball << "\n";

	}

	Logger->write("Output data to Student!");

    ifile.close();

    return QString::fromStdString(oss.str());
}

bool Stud::DeleteStudent(size_t index)
{
	if (index >= 0 && index < Students.size())
	{
		Students.erase(Students.begin() + index);

		Logger->write("Seccuful delete Student" + std::to_string(index));
		return true;
	}

	Logger->write("Fail delete Student" + index);
	return false;
}

bool Stud::DeleteStudentFromFile(const std::string& filename, const std::string& targetName, std::optional<double> targetBall = std::nullopt)
{
    std::ifstream ifile(filename);
    if (!ifile.is_open()) {
        return false;
    }

    std::string line;
    std::vector<std::string> filter;
    std::vector<std::string> thisStudents; // Все прочитанные строки

    while (std::getline(ifile, line))
    {
        std::istringstream iss(line);
        std::string name;
        double ball;

        if (!(iss >> name >> ball)) {
            filter.push_back(line);
            continue;
        }

        thisStudents.push_back(line);

        bool shouldDelete = (name == targetName) && (!targetBall || std::abs(ball - *targetBall) < 1e-6);

        if (shouldDelete)
        {
            Logger->write("Deleted Student from file: " + name + (targetBall ? " " + std::to_string(*targetBall) : ""));

            continue;
        }

        filter.push_back(line);
    }

    ifile.close();

    // Запись оставшихся строк обратно в файл
    std::ofstream ofile(filename, std::ios::trunc);
    if (!ofile.is_open()) {
        // Не удалось открыть файл для записи
        return false;
    }

    for (const auto& s : filter)
    {
        ofile << s << "\n";
    }
    ofile.close();

    // Проверка успешности удаления
    return thisStudents.size() != filter.size();
}

std::ostream& operator<<(std::ostream& os, const Student& other)
{
	os << other.name << " " << other.ball;

	return os;
}
