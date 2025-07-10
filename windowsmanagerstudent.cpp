#include "windowsmanagerstudent.h"
#include "mainwindow.h"


WindowsManagerStudent::WindowsManagerStudent(QWidget *parent) : QWidget(parent)
{
    if (!mainWin) {
        mainWin = std::make_unique<MainWindow>();
    }


    setWindowTitle("Менеджр Студентов");
    resize(400, 300);


    setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1e3c72, stop:1 #2a5298);");


    lineFileToSaveData = std::make_unique<QLineEdit>(this);
    lineFileToSaveData->setPlaceholderText("Файл сохранения");

    lineDataStudent = std::make_unique<QLineEdit>(this);
    lineDataStudent->setPlaceholderText("Данныe (имя балл) ");

    ButtonAddStudent = std::make_unique<QPushButton>("добавить",this);

    ButtonBackMenu  = std::make_unique<QPushButton>("Главное меню",this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(lineFileToSaveData.get());
    layout->addWidget(lineDataStudent.get());
    layout->addWidget(ButtonAddStudent.get());
    layout->addWidget(ButtonBackMenu.get());

    setLayout(layout);




    connect(ButtonAddStudent.get(),&QPushButton::clicked,this,&WindowsManagerStudent::addStudentTiFile);
    connect(ButtonBackMenu.get(),&QPushButton::clicked,this,&WindowsManagerStudent::backMainMenu);

}

void WindowsManagerStudent::addStudentTiFile()
{
    QString file = lineFileToSaveData->text();
    QString data = lineDataStudent->text();

    std::string fileSTR = file.toStdString();
    std::string dataSTR = data.toStdString();


    Stud manag("LogStudent.txt");

    bool success = manag.uploadDataToFile(fileSTR, dataSTR);


    if (success) {
        QMessageBox::information(this, "Менеджр", "Успешно добавлен!");
        emit authSuccess();
    } else {
        QMessageBox::warning(this, "Менеджр", "Не удалось сохранить в файл ( проблема с создание файла");
        QMessageBox::warning(this, "Менеджр", "Укажите другой.txt");

    }

}

void WindowsManagerStudent::backMainMenu()
{
    if (mainWin) {
        mainWin->show();
    }
    this->close();

}
