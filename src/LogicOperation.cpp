#include"LogicOperation.h"
#include"ManagerStudent.h"
#include"DynamicFormDialog.h"
#include"Serializer.h"

bool LogicOperation::handleAddStudent(const QString &file, const QString &data,QLineEdit* LineEditClear,QWidget* parent)
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

QString LogicOperation::handlePriviewFile(const QString &file, QTextEdit *display, QWidget *parent)
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

bool LogicOperation::handleSortStudent(const QString &file, const QString &saveFile, QWidget *parent)
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

void LogicOperation::handleDeleteStudent(const QString &file, const QString &name, const QString &score, QWidget *parent)
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

void LogicOperation::handleFindStudent(const QString &file, const QString &name, const QString &score, QWidget *parent)
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

std::optional<double> LogicOperation::handleAutoTestStudent(QTableWidgetItem* checkItem, QList<int>& averageScore)
{

    if (!checkItem) return std::nullopt;
    if(checkItem->checkState() != Qt::Checked) return std::nullopt;
    if (averageScore.isEmpty()) return std::nullopt;
    int sum = 0;

    for(const int c : averageScore) sum+= c;

    double result = static_cast<double>(sum) / averageScore .size();

    averageScore.clear();

    return result;

}

double LogicOperation::converterTOnumberInString(const QString &number)
{
    double Num;
    bool isNum = false;
    Num = number.toDouble(&isNum);

    return Num;
}

void LogicOperation::FillSettingsTable(QSettings &settings, QTableWidget* t)
{
    for(int row=0;row< t->rowCount();row++)
    {

        for(int col=0;col< t->columnCount();col++)
        {
            QString key = QString("row_%1_col_%2").arg(row).arg(col);
            QTableWidgetItem* item = t->item(row, col);
            if (!item) continue;

            QString header = t->horizontalHeaderItem(col) ? t->horizontalHeaderItem(col)->text() : "";
            if (header == "Автомат" && (item->flags() & Qt::ItemIsUserCheckable)) {
                settings.setValue(key, static_cast<int>(item->checkState()));
            } else {
                settings.setValue(key, item->text());
            }
        }
    }
}

void LogicOperation::FillTableWidget(QSettings &settings, QTableWidget *t,int row,int column)
{
    t->blockSignals(true);

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column;j++)
        {
            QString key = QString("row_%1_col_%2").arg(i).arg(j);
            QVariant value = settings.value(key);
            QTableWidgetItem* item = t->item(i,j);
            QString header = t->horizontalHeaderItem(j) ? t->horizontalHeaderItem(j)->text() : "";


            if (!item) {
                item = new QTableWidgetItem();
                t->setItem(i, j, item);
            }

            if (header == "Автомат") {
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                item->setCheckState(static_cast<Qt::CheckState>(settings.value(key, Qt::Unchecked).toInt()));
            }  else {
                item->setText(value.toString());
            }

        }
    }

    t->blockSignals(false);
}
