#include"LogicOperation.h"
#include"ManagerStudent.h"
#include"DynamicFormDialog.h"

bool IHandleStudent::handleAddStudent(const QString &file, const QString &data,QLineEdit* LineEditClear,QWidget* parent)
{
    auto logger = Log::create("AddStudentLog.txt");
    Stud manager(logger);

    try
    {
        QFile ofile(file);
        Validator::isFileValid(ofile,ModeValidator::WriteFile);
    }
    catch(const std::invalid_argument&e)
    {
        logger->write(e.what());
        return false;
    }

    bool success = manager.uploadDataToFile(file.toStdString(),data.toStdString());

    if (success) {
        QMessageBox::information(parent, "Менеджeр", "Успешно добавлен!");
        LineEditClear->clear();
    } else {
        QMessageBox::warning(parent, "Менеджр", "Не удалось сохранить в файл (проблема с созданием файла)");
        QMessageBox::warning(parent, "Менеджр", "Укажите другой .txt");
        return false;
    }

    return true;
}

QString IHandleStudent::handlePriviewFile(const QString &file, QTextEdit *display, QWidget *parent)
{
    auto logger = Log::create("PriviewLog.txt");
    Stud manager(logger);

    try
    {
        QFile ofile(file);
        Validator::isFileValid(ofile,ModeValidator::ReadFile);
    }
    catch(const std::invalid_argument&e)
    {
        logger->write(e.what());
        return "";
    }

    QString show = manager.PrintSortStud(file.toStdString());


    if (show.isEmpty()) {
        display->setPlainText("Файл пустой или не удалось прочитать.");
    } else {
        display->setPlainText(show);
    }

    return show;
}

bool IHandleStudent::handleSortStudent(const QString &file, const QString &saveFile, QWidget *parent)
{
    auto logger = Log::create("SortLogStudent.txt");
    Stud manager(logger);

    try
    {
        QFile ofile(file);
        QFile ifile(saveFile);
        Validator::isFileValid(ofile,ModeValidator::ReadFile);
        Validator::isFileValid(ifile,ModeValidator::WriteFile);
    }
    catch(const std::invalid_argument&e)
    {
        logger->write(e.what());
        return false;
    }

    bool success = manager.SortStudent(saveFile,file);


    if (success) {
        QMessageBox::information(parent, "Сортировка", "Сортировка прошла успешно!");
    } else {
        QMessageBox::warning(parent, "Сортировка", "Не известная ошибка перезапустите программу :(");
        QMessageBox::warning(parent, "Сортировка", " Укажите другой .txt");
        return false;
    }

    return true;

}

void IHandleStudent::handleDeleteStudent(const QString &file, const QString &name, const QString &score, QWidget *parent)
{
    auto logger = Log::create("LogDeleted.txt");
    Stud manager(logger);


    try {
        QFile ifile(file);
        Validator::isFileValid(ifile, ModeValidator::ReadFile);
    } catch (std::invalid_argument& e) {
        logger->write(e.what());
        QMessageBox::warning(parent, "Ошибка валидации файла", e.what());
        return;
    }

    std::optional<double> scoreOpt;
    try
    {
        scoreOpt = Validator::ValidOptional(score);
    }catch (std::invalid_argument& e) {
        logger->write(e.what());
        QMessageBox::warning(parent, "Ошибка валидации балла", e.what());
        return;
    }


    bool deleted = manager.DeleteStudentFromFile(file.toStdString(),name.toStdString(),scoreOpt);


    if (deleted) {
        QMessageBox::information(parent, "Удаление", QString("Студент удален: %1").arg(name));
    } else {
        QMessageBox::warning(parent, "Удаление", QString("Студент не удален: %1").arg(name));
    }

}

void IHandleStudent::handleFindStudent(const QString &file, const QString &name, const QString &score, QWidget *parent)
{
    auto logger = Log::create("LogFind.txt");
    Stud manager(logger);

    std::optional<double> scoreOpt;

    try{
        QFile ifile(file);
        Validator::isFileValid(ifile,ModeValidator::ReadFile);
    }catch(std::invalid_argument& e)
    {
        logger->write(e.what());
        QMessageBox::warning(parent, "Ошибка валидации файла", e.what());
        return;
    }

    try{
        scoreOpt = Validator::ValidOptional(score);
    }catch(std::invalid_argument& e)
    {
        logger->write(e.what());
        QMessageBox::warning(parent, "Ошибка валидации балла", e.what());
        return;
    }

    bool found = manager.findStudent(file.toStdString(),name.toStdString(),scoreOpt);


    if (found) {
        QMessageBox::information(parent, "Найти", QString("Студент найден: %1").arg(name));
    } else {
        QMessageBox::warning(parent, "Найти", QString("Студент не найден: %1").arg(name));
    }



}
