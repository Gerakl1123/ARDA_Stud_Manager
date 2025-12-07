#include "builderform.h"

BuilderForm::BuilderForm(QWidget *parent)
    : QWidget{parent}
{}

void BuilderForm::setupNameHash()
{
    nameLineButton["lineEdit_Attestat_FileSave"] = "btnBrowseAttestatSaveFile";
    nameLineButton["lineEdit_Attestat_FileLog"]="btnAttestatFileLog";
    nameLineButton["lineEdit_Attestat_InputFile"]="btnAttestatInputFile";
    //MaxScore
    nameLineButton["lineEdit_MaxScore_FileInput"]="btnBrowseMaxScoreInputFile";
    nameLineButton["lineEdit_MaxScore_FileSave"] = "btnMaxScoreFileSave";
    nameLineButton["lineEdit_MaxScore_FileLog"]="btnMaxScoreFileLog";

}

QList<QPair<QLineEdit*,QPushButton*>> BuilderForm::initializer(QWidget *w)
{
    setupNameHash();

    QList<QPair<QLineEdit*,QPushButton*>> temp;

    if(w == nullptr)
        return temp;


    for(auto i = nameLineButton.cbegin(); i != nameLineButton.cend(); ++i)
    {
        QString lineName = i.key();
        QString btnName = i.value();

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
            qWarning() << "Не удалось найти line и btn: "
                       << lineName << " " << btnName;
        }
    }
    return temp;
}

void BuilderForm::setupBrowseButton(QPushButton *btn, QLineEdit *line, FileManager *fileManager)
{

    connect(btn, &QPushButton::clicked,btn,[=]()
            {
        QString file = fileManager->chooseFile();
        if(!file.isEmpty())
            line->setText(file);
    });


}

QMessageBox::StandardButton BuilderForm::confrimSomething()
{

    QMessageBox::StandardButton confrim = QMessageBox::question(
        nullptr,
        "Подтверждение",
        "Вы уверены что хотите выполнить удалление файла?",
        QMessageBox::Yes | QMessageBox::No
    );

    return confrim;
}
