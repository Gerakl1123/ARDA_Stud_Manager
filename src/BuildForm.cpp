#include "BuildForm.h"

AddStudentWidgets FormBuilder::buildAddStudentForm(QWidget* parent) {
    AddStudentWidgets widgets;

    widgets.fileEdit = new QLineEdit(parent);
    widgets.dataEdit = new QLineEdit(parent);
    widgets.browseButton = new QPushButton("Выбрать 📁", parent);

    return widgets;
}

SortStudentWidgets FormBuilder::buildSortStudentForm(QWidget *parent)
{
    SortStudentWidgets widgets;

    widgets.sortInputFileEdit = new QLineEdit(parent);
    widgets.sortOutputFileEdit = new QLineEdit(parent);
    widgets.btnSortInputBrowse = new QPushButton("Выбрать 📁",parent);

    return widgets;
}

DeleteStudentWidgets FormBuilder::builDeletedStudentForm(QWidget *parent)
{
    DeleteStudentWidgets widgets;

    widgets.deleteFileEdit = new QLineEdit(parent);
    widgets.deleteNameEdit = new QLineEdit(parent);
   widgets.deleteScoreEdit = new QLineEdit(parent);
    widgets.btnDeleteFileBrowse = new QPushButton("Выбрать 📁",parent);

   return widgets;

}

SeeFileStudentWidgets FormBuilder::builSeeFileStudentForm(QWidget *parent)
{
    SeeFileStudentWidgets widgets;

    widgets.printFileEdit = new QLineEdit(parent);
    widgets.studentDisplay = new QTextEdit(parent);
    widgets.btnPrintFileBrowse=new QPushButton("Выбрать 📁",parent);

    return widgets;

}

FindStudentWidgets FormBuilder::buildFindStudentForm(QWidget *parent)
{
    FindStudentWidgets widgets;

    widgets.findFileEdit = new QLineEdit(parent);
    widgets.findNameEdit = new QLineEdit(parent);
    widgets.findScoreEdit = new QLineEdit(parent);
    widgets.btnFindFileBrowse=new QPushButton("Выбрать 📁",parent);

    return widgets;
}

void LayaoutBuilder::addStudentLayout(QFormLayout* formLayout, QPushButton* btn, QLineEdit* file, QLineEdit* data)
{
    formLayout->addRow("Файл Сохранения:", file);
    formLayout->addRow("Данные:", data);
    formLayout->addWidget(btn);
}

void LayaoutBuilder::addSortLayout(QFormLayout *formLayout, QPushButton *btn, QLineEdit *file, QLineEdit *data)
{
    formLayout->addRow("Файл считывания:", file);
    formLayout->addRow("Файл сохранения:", data);
    formLayout->addWidget(btn);
}

void LayaoutBuilder::addSeeFiletLayout(QFormLayout *formLayout, QPushButton *btn, QLineEdit *file, QTextEdit *display)
{
    formLayout->addRow("Файл считывания:", file);
    formLayout->addRow("", display);
    formLayout->addWidget(btn);
}

void LayaoutBuilder::addFindLayout(QFormLayout *formLayout, QPushButton *btn, QLineEdit *file, QLineEdit *name, QLineEdit *score)
{
    formLayout->addRow("Файл где искать", file);
    formLayout->addRow("Имя:", name);
    formLayout->addRow("Балл для точного поиска:",score);
    formLayout->addWidget(btn);

}

void LayaoutBuilder::addDeleteLayout(QFormLayout *formLayout, QPushButton *btn, QLineEdit *file, QLineEdit *name, QLineEdit *score)
{
    formLayout->addRow("Файл где искать:", file);
    formLayout->addRow("Имя", name);
    formLayout->addRow("Балл для точного поиска:",score);
    formLayout->addWidget(btn);

}
//======================= =====================
void FormBuilder::setupNameHash()
{
    nameLineButton["lineEdit_Attestat_FileSave"] = "btnBrowseAttestatSaveFile";
    nameLineButton["lineEdit_Attestat_Fakyltet"]="btnAttestatFaculty";
    nameLineButton["lineEdit_Attestat_FileLog"]="btnAttestatFileLog";
    nameLineButton["lineEdit_Attestat_InputFile"]="btnAttestatInputFile";
    //MaxScore
    nameLineButton["lineEdit_MaxScore_FileInput"]="btnBrowseMaxScoreInputFile";
    nameLineButton["lineEdit_MaxScore_FileSave"] = "btnMaxScoreFileSave";
    nameLineButton["lineEdit_MaxScore_FileLog"]="btnMaxScoreFileLog";

}

QList<QPair<QLineEdit*,QPushButton*>> FormBuilder::initializer(QWidget *w)
{
    setupNameHash();

    QList<QPair<QLineEdit*,QPushButton*>> temp;

    if(w == nullptr)
        return temp;


    for(auto i = nameLineButton.cbegin(); i != nameLineButton.cend(); ++i)
    {
        QString lineName = i.key(); //first
        QString btnName = i.value(); //second

        QList<QLineEdit*> lineEdits = w->findChildren<QLineEdit*>(lineName);
        QList<QPushButton*> buttons = w->findChildren<QPushButton*>(btnName);

        if(lineEdits.size() == 1 && buttons.size() == 1)
        {
            QLineEdit* line = lineEdits.first();
            QPushButton* btn = buttons.first();

            temp.emplace_back(line,btn);
        }
         else
         {
             qWarning() << "Не удалось найти QLineEdit или QPushButton данные: "
                        << lineName << " - " << btnName;
         }
    }
    return temp;
}

void FormBuilder::setupBrowseButton(QPushButton *btn,QLineEdit* line,FileManager* fileManager)
{

    QObject::connect(btn, &QPushButton::clicked, btn, [=]() {
        QString fileName = fileManager->chooseFile();
        if (!fileName.isEmpty()) {
            line->setText(fileName);
        }
    });

}

