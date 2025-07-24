#include"ManagerStudent.h"
bool Stud::findStudent(const std::string& nameF, const std::string& name, std::optional<double> value = std::nullopt)
{
    if (!Logger) {
        std::cerr << "Logger не инициализирован!" << std::endl;
        return false;
    }



    Students.clear();

    std::ifstream ifile(nameF);

    if (!ifile.is_open()) {
        std::ofstream create(nameF);
        Logger->write("Failed open file: " + nameF);
        create.close();
        return false;
    }

    Students = ContestBase::loadStudentsFromFile(QString::fromStdString(nameF));

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
    if (!logStud.is_open()) {

        std::ofstream create("data.txt");
        create.close();
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
            Logger->write("login to account " + login);
            return true;
        }

    }
    Logger->write("Fail login to account " + login);
    return false;
}

//======================================================================


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

    ofile << name << " " << double(ball) << "\n";


    Logger->write("Student successful " + name + " " + std::to_string(ball));


    return true;
}

void Stud::SortStudent(const QString& Ofile,const QString& Ifile)
{

    uploadInfoStud(Ifile.toStdString()); // rezerv upload data stud

    cast(); // input rezerv data to vector students

    std::sort(Students.begin(), Students.end(), [](const Student& a, const Student& b) {
        return a.ball > b.ball;
    });

    rezerv_info_stud.clear();

    for (const auto& st : Students)
    {
        rezerv_info_stud.emplace(st.name, st.ball);
    }

    Logger->write("Sorsted Seccuful!");


    uploadReadyFile(Ofile.toStdString());

}
//PRIVATE METHODS
void Stud::uploadInfoStud(const std::string& file)
{
    std::string line;
    std::ifstream ifile(file);

    if (!ifile.is_open()) {
        Logger->write("Failed to open file for reading: " + file);
        return;
    }

    while (std::getline(ifile, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string name;
        double ball;

        if (!(iss >> name >> ball))
        {
            Logger->write("Invalid line format (ignored): " + line);
            continue;
        }

        if (!std::isfinite(ball)) {
            Logger->write("Invalid number (not finite) for " + name + ": " + std::to_string(ball));
            continue;
        }

        rezerv_info_stud.emplace(name, ball);
    }

    Logger->write("Successful Backup!");
    ifile.close();
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
    std::ofstream ofile(file, std::ios::trunc);
    if (!ofile.is_open()) {
        Logger->write("Failed to open file: " + file);
        return;
    }

    for (const auto& st : Students)
        ofile << st.name << " " << st.ball << "\n";

    Logger->write("Upload data to ready file! ");

    rezerv_info_stud.clear();
    Students.clear();
}
//==============END PRIVATE METHODS=====================

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


    std::ofstream ofile(filename, std::ios::trunc);
    if (!ofile.is_open()) {

        return false;
    }

    for (const auto& s : filter)
    {
        ofile << s << "\n";
    }
    ofile.close();


    return thisStudents.size() != filter.size();
}

