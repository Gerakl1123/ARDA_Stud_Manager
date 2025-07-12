#include "windowsmanagerstudent.h"
#include "mainwindow.h"
#include<QIcon>
#include<QGroupBox>
#include<QFile>

Stud manag("LogStudent.txt");

WindowsManagerStudent::WindowsManagerStudent(QWidget *parent) : QWidget(parent)
{
 mainWin = std::make_unique<MainWindow>();

    if (!mainWin) {
        mainWin = std::make_unique<MainWindow>();
    }

    Style();
    applyStyle();
    setupConnections();
}

void WindowsManagerStudent::addStudentTiFile()
{
    QString file = lineFileToSaveData->text();
    QString data = lineDataStudent->text();

    std::string fileSTR = file.toStdString();
    std::string dataSTR = data.toStdString();



    bool success = manag.uploadDataToFile(fileSTR, dataSTR);


    if (success) {
        QMessageBox::information(this, "Менеджр", "Успешно добавлен!");
        emit authSuccess();
        lineDataStudent->clear();
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
void WindowsManagerStudent::SortStud()
{
    manag.SortStudent();
}

void WindowsManagerStudent::SaveGlobalEdit()
{
    QString Sfile = lineFileToSave->text();

    std::string fileSTR = Sfile.toStdString();

    manag.uploadReadyFile(fileSTR);

}
void WindowsManagerStudent::FindStudent()
{

    QString file = lineFiletoFind->text();
    QString name = lineNameFindStudent->text();
    QString ballStr = lineBallFindStudent->text();

    bool ok = false;
    double ballValue = ballStr.toDouble(&ok);


    std::string fileSTR = file.toStdString();
    std::string nameSTR = name.toStdString();

     std::optional<double> ballOpt;

    if (ok && !ballStr.isEmpty()) {
        ballOpt = ballValue;  // передаём значение, если введено корректно
    } else {
        ballOpt = std::nullopt; // пустое значение
    }

     bool found = manag.findStudent(fileSTR, nameSTR, ballOpt);

    if (found) {
        QMessageBox::information(this, "Поиск", "Студент найден");
    } else {
        QMessageBox::warning(this, "Поиск", "Студент не найден");
    }
}

void WindowsManagerStudent::DeleteStudent()
{
    QString file = lineFileToDelete ->text();
    QString name = linenNameToDelete ->text();
    QString ballStr = lineBallToDelete ->text();

    bool ok = false;
    double ballValue = ballStr.toDouble(&ok);


    std::string fileSTR = file.toStdString();
    std::string nameSTR = name.toStdString();

    std::optional<double> ballOpt;

    qDebug() << "Файл:" << QString::fromStdString(fileSTR);
    qDebug() << "Имя:" << QString::fromStdString(nameSTR);
    qDebug() << "Балловое значение:" << (ballOpt ? QString::number(*ballOpt) : "nullopt");
    if (ok && !ballStr.isEmpty())
    {
        ballOpt = ballValue;
    }
    else
    {
        ballOpt = std::nullopt;
    }

    bool found = manag.DeleteStudentFromFile(fileSTR,nameSTR,ballOpt);

    if (found) {
       QMessageBox::information(this, "Удаление", QString("Студент удален %1").arg(name));
    } else {
        QMessageBox::warning(this, "Удаление", QString("Студент не удален %1").arg(name));
    }

}

void WindowsManagerStudent::Style()
{
    setWindowTitle("Менеджр Студентов");
    resize(1280,800);

    this->setStyleSheet(R"(
    QWidget {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                    stop:0 #1e3c72, stop:1 #2a5298);
        color: white;
        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        font-size: 14px;
    }

    QGroupBox {
        border: 1px solid rgba(255, 255, 255, 0.3);
        border-radius: 8px;
        margin-top: 15px;
        padding: 10px 15px 15px 15px;
        color: white;
    }

    QGroupBox:title {
        subcontrol-origin: margin;
        subcontrol-position: top left;
        padding: 0 3px;
        font-weight: bold;
        font-size: 16px;
    }

    QLabel {
        color: white;
        font-weight: normal;
        font-size: 14px;
    }

    QLineEdit {
        background-color: rgba(255, 255, 255, 0.15);
        border: none;
        border-radius: 6px;
        padding: 6px 10px;
        color: white;
        font-size: 14px;
    }
    QLineEdit::placeholder {
        color: rgba(255, 255, 255, 0.5);
    }

    QPushButton {
        background-color: #4fc3f7;
        color: white;
        border: none;
        border-radius: 15px;
        padding: 12px 30px;
        font-size: 18px;
        font-weight: bold;
        transition: all 0.3s ease;
        min-width: 180px;
    }
    QPushButton:hover {
        background-color: #29b6f6;
    }
    QPushButton:pressed {
        background-color: #1e88e5;
    }
)");

}

void WindowsManagerStudent::applyStyle()
{


    // ========== Создание виджетов ==========
    auto makeLine = [this](const QString& placeholder) {
        QLineEdit* line = new QLineEdit(this);
        line->setPlaceholderText(placeholder);
        line->setFixedSize(180, 30);
        return line;
    };

    auto makeButton = [this](const QString& text) {
        QPushButton* btn = new QPushButton(text, this);
        btn->setMinimumSize(140, 35);
        btn->setMaximumWidth(200);
        return btn;
    };

    // --- Добавление ---
    lineFileToSaveData = makeLine("Файл");
    lineDataStudent = makeLine("ИмяФамилия Балл");
    ButtonAddStudent = makeButton("Добавить");

    // --- Сортировка ---
    ButtonSortStud = makeButton("Сортировать");

    // --- Сохранение ---
    lineFileToSave = new QLineEdit("Файл_сохранения.txt", this);
    lineFileToSave->setFixedSize(180, 30);
    ButtonSaveEdit = makeButton("Сохранить");

    // --- Главное меню ---
    ButtonBackMenu = makeButton("Главное меню");

    // --- Поиск ---
    lineFiletoFind = makeLine("Файл");
    lineNameFindStudent = makeLine("Имя");
    lineBallFindStudent = makeLine("Балл");
    ButtonFindStudent = makeButton("Найти");

    // --- Удаление ---
    lineFileToDelete = makeLine("Файл");
    linenNameToDelete = makeLine("Имя");
    lineBallToDelete = makeLine("Балл");
    ButtonDeleteStudent = makeButton("Удалить");

    // ========== Группы ==========
    auto createGroup = [](const QString& title, QLayout* layout) {
        QGroupBox* box = new QGroupBox(title);
        box->setLayout(layout);
        return box;
    };

    // --- Группа добавления ---
    QGridLayout* layoutAdd = new QGridLayout();
    layoutAdd->addWidget(new QLabel("Файл:"), 0, 0);
    layoutAdd->addWidget(lineFileToSaveData, 0, 1);
    layoutAdd->addWidget(new QLabel("Данные:"), 1, 0);
    layoutAdd->addWidget(lineDataStudent, 1, 1);
    layoutAdd->addWidget(ButtonAddStudent, 2, 1);
    QGroupBox* groupAdd = createGroup("Добавление", layoutAdd);

    // --- Группа сортировки ---
    QVBoxLayout* layoutSort = new QVBoxLayout();
    layoutSort->addWidget(ButtonSortStud);
    QGroupBox* groupSort = createGroup("Сортировка", layoutSort);

    // --- Группа сохранения ---
    QGridLayout* layoutSave = new QGridLayout();
    layoutSave->addWidget(new QLabel("Файл:"), 0, 0);
    layoutSave->addWidget(lineFileToSave, 0, 1);
    layoutSave->addWidget(ButtonSaveEdit, 1, 1);
    QGroupBox* groupSave = createGroup("Сохранение", layoutSave);

    // --- Группа поиска ---
    QGridLayout* layoutFind = new QGridLayout();
    layoutFind->addWidget(new QLabel("Файл:"), 0, 0);
    layoutFind->addWidget(lineFiletoFind, 0, 1);
    layoutFind->addWidget(new QLabel("Имя:"), 1, 0);
    layoutFind->addWidget(lineNameFindStudent, 1, 1);
    layoutFind->addWidget(new QLabel("Балл:"), 2, 0);
    layoutFind->addWidget(lineBallFindStudent, 2, 1);
    layoutFind->addWidget(ButtonFindStudent, 3, 1);
    QGroupBox* groupFind = createGroup("Поиск", layoutFind);

    // --- Группа удаления ---
    QGridLayout* layoutDelete = new QGridLayout();
    layoutDelete->addWidget(new QLabel("Файл:"), 0, 0);
    layoutDelete->addWidget(lineFileToDelete, 0, 1);
    layoutDelete->addWidget(new QLabel("Имя:"), 1, 0);
    layoutDelete->addWidget(linenNameToDelete, 1, 1);
    layoutDelete->addWidget(new QLabel("Балл:"), 2, 0);
    layoutDelete->addWidget(lineBallToDelete, 2, 1);
    layoutDelete->addWidget(ButtonDeleteStudent, 3, 1);
    QGroupBox* groupDelete = createGroup("Удаление", layoutDelete);

    // ========== Компоновка ==========
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Верхний ряд: добавление + сортировка
    QHBoxLayout* topRow = new QHBoxLayout();
    topRow->addWidget(groupAdd);
    topRow->addWidget(groupSort);

    // Средний ряд: сохранение + поиск
    QHBoxLayout* midRow = new QHBoxLayout();
    midRow->addWidget(groupSave);
    midRow->addWidget(groupFind);

    // Нижний ряд: удаление + главное меню
    QHBoxLayout* bottomRow = new QHBoxLayout();
    bottomRow->addWidget(groupDelete);
    bottomRow->addStretch();
    bottomRow->addWidget(ButtonBackMenu);

    mainLayout->addLayout(topRow);
    mainLayout->addLayout(midRow);
    mainLayout->addLayout(bottomRow);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    setLayout(mainLayout);
}

void WindowsManagerStudent::setupConnections()
{
    connect(ButtonAddStudent,&QPushButton::clicked,this,&WindowsManagerStudent::addStudentTiFile);
    connect(ButtonBackMenu,&QPushButton::clicked,this,&WindowsManagerStudent::backMainMenu);
    connect(ButtonSortStud,&QPushButton::clicked,this,&WindowsManagerStudent::SortStud);
    connect(ButtonSaveEdit,&QPushButton::clicked,this,&WindowsManagerStudent::SaveGlobalEdit);
    connect(ButtonFindStudent, &QPushButton::clicked, this, &WindowsManagerStudent::FindStudent);
    connect(ButtonDeleteStudent,&QPushButton::clicked,this,&WindowsManagerStudent::DeleteStudent);

}

