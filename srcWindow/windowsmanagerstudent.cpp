#include "windowsmanagerstudent.h"

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
    ButtonSortStud->setEnabled(false); // отключаем кнопку

    QString Sfile = lineFileToSave->text();
    QString Ifile = lineFileToInput->text();

    manag.SortStudent(Sfile, Ifile);

    QMessageBox::information(this, "Сортировка", "Сортировка прошла успешно!");


    QTimer::singleShot(10000, this, [this]() {
        ButtonSortStud->setEnabled(true);
    });

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
        ballOpt = ballValue;
    } else {
        ballOpt = std::nullopt;
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

void WindowsManagerStudent::ShowFileContent()
{


    QString file = lineFileToPrint->text().trimmed();
    qDebug() << "Показываю файл:" << file;

    std::string fileSTR = file.toStdString();

    QString show = manag.PrintSortStud(fileSTR);

    if (show.isEmpty()) {
        StudDisplayArea->setPlainText("Файл пустой или не удалось прочитать.");
    } else {
        StudDisplayArea->setPlainText(show);
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
    QPushButton:disabled {
        background-color: #9e9e9e;
        color: #cccccc;
        border: none;
    }
)");

}


void WindowsManagerStudent::applyStyle()
{

    auto makeLine = [this](const QString& placeholder) {
        QLineEdit* line = new QLineEdit(this);
        line->setPlaceholderText(placeholder);
        line->setFixedSize(180, 30);
        return line;
    };

    auto makeButton = [this](const QString& text) {
        QPushButton* btn = new QPushButton(text, this);
        btn->setMinimumSize(160, 40);
        btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        btn->setFont(QFont("Segoe UI", 10));
        return btn;
    };

    // Добавление
    lineFileToSaveData = makeLine("Файл");
    lineDataStudent = makeLine("ИмяФамилия Балл");
    ButtonAddStudent = makeButton("Добавить");

    // Сортировка
    ButtonSortStud = makeButton("Сортировать");

    lineFileToInput = makeLine("Файл считывания студентов");
    lineFileToSave = makeLine("Файл сохранения");

    // Главное меню
    ButtonBackMenu = makeButton("Главное меню");

    // Поиск
    lineFiletoFind = makeLine("Файл");
    lineNameFindStudent = makeLine("Имя");
    lineBallFindStudent = makeLine("Балл (необязателен)");
    ButtonFindStudent = makeButton("Найти");

    // Удаление
    lineFileToDelete = makeLine("Файл");
    linenNameToDelete = makeLine("Имя");
    lineBallToDelete = makeLine("Балл");
    ButtonDeleteStudent = makeButton("Удалить");

    // Просмотр
    lineFileToPrint = makeLine("Файл для отображения");
    ButtonShowContent = makeButton("Показать содержимое");

    StudDisplayArea = new QTextEdit(this);
    StudDisplayArea->setReadOnly(true);
    StudDisplayArea->setMinimumHeight(100);
    StudDisplayArea->setFont(QFont("Arial", 10));
    StudDisplayArea->setStyleSheet("background-color: white; color: black;");

    // --- Layout'ы ---
    QGridLayout* layoutPrint = new QGridLayout();
    layoutPrint->addWidget(new QLabel("Файл:"), 0, 0);
    layoutPrint->addWidget(lineFileToPrint, 0, 1);
    layoutPrint->addWidget(ButtonShowContent, 1, 1);
    layoutPrint->addWidget(StudDisplayArea, 2, 0, 1, 2);
    QGroupBox* groupPrint = new QGroupBox("Просмотр файла");
    groupPrint->setLayout(layoutPrint);

    QGridLayout* layoutAdd = new QGridLayout();
    layoutAdd->addWidget(new QLabel("Файл:"), 0, 0);
    layoutAdd->addWidget(lineFileToSaveData, 0, 1);
    layoutAdd->addWidget(new QLabel("Данные:"), 1, 0);
    layoutAdd->addWidget(lineDataStudent, 1, 1);
    layoutAdd->addWidget(ButtonAddStudent, 2, 1);
    QGroupBox* groupAdd = new QGroupBox("Добавление");
    groupAdd->setLayout(layoutAdd);

    QGridLayout* layoutSort = new QGridLayout();
    layoutSort->addWidget(new QLabel("Файл (вход):"), 0, 0);
    layoutSort->addWidget(lineFileToInput, 0, 1);
    layoutSort->addWidget(new QLabel("Файл (сохранение):"), 1, 0);
    layoutSort->addWidget(lineFileToSave, 1, 1);
    layoutSort->addWidget(ButtonSortStud, 2, 0);



    QGroupBox* groupSort = new QGroupBox("Сортировка");
    groupSort->setLayout(layoutSort);

    QGridLayout* layoutFind = new QGridLayout();
    layoutFind->addWidget(new QLabel("Файл:"), 0, 0);
    layoutFind->addWidget(lineFiletoFind, 0, 1);
    layoutFind->addWidget(new QLabel("Имя:"), 1, 0);
    layoutFind->addWidget(lineNameFindStudent, 1, 1);
    layoutFind->addWidget(new QLabel("Балл:"), 2, 0);
    layoutFind->addWidget(lineBallFindStudent, 2, 1);
    layoutFind->addWidget(ButtonFindStudent, 3, 1);
    QGroupBox* groupFind = new QGroupBox("Поиск");
    groupFind->setLayout(layoutFind);

    QGridLayout* layoutDelete = new QGridLayout();
    layoutDelete->addWidget(new QLabel("Файл:"), 0, 0);
    layoutDelete->addWidget(lineFileToDelete, 0, 1);
    layoutDelete->addWidget(new QLabel("Имя:"), 1, 0);
    layoutDelete->addWidget(linenNameToDelete, 1, 1);
    layoutDelete->addWidget(new QLabel("Балл:"), 2, 0);
    layoutDelete->addWidget(lineBallToDelete, 2, 1);
    layoutDelete->addWidget(ButtonDeleteStudent, 3, 1);
    QGroupBox* groupDelete = new QGroupBox("Удаление");
    groupDelete->setLayout(layoutDelete);

    // --- Макеты ---
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* topRow = new QHBoxLayout();
    topRow->addWidget(groupAdd);
    topRow->addWidget(groupSort);

    QHBoxLayout* midRow = new QHBoxLayout();
    midRow->addWidget(groupFind);

    QHBoxLayout* bottomRow = new QHBoxLayout();
    bottomRow->addWidget(groupDelete);
    bottomRow->addStretch();
    bottomRow->addWidget(ButtonBackMenu);

    mainLayout->addWidget(groupPrint);
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
    connect(ButtonFindStudent, &QPushButton::clicked, this, &WindowsManagerStudent::FindStudent);
    connect(ButtonDeleteStudent,&QPushButton::clicked,this,&WindowsManagerStudent::DeleteStudent);
    connect(ButtonShowContent,&QPushButton::clicked,this,&WindowsManagerStudent::ShowFileContent);
}

