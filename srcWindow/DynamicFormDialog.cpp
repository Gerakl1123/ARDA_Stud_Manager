#include"DynamicFormDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QDebug>
#include<ManagerStudent.h>
#include"Validator.h"

DynamicDialog::DynamicDialog(Mode mode, QWidget* parent)
    : QDialog(parent), currentMode(mode), fileManager(std::make_unique<FileManager>())
{
    handleAdd = std::make_unique<IHandleStudent>();
    serializer = std::make_unique<SerializerData>();

    setupUI();
    clearForm();
    buildFormForMode();

}


void DynamicDialog::clearForm(){

    while(QLayoutItem* item = formLayout->takeAt(0))
    {
        if(QWidget* w = item->widget())
        {
            w->deleteLater();
        }
        delete item;
    }
}

void DynamicDialog::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout;
    mainLayout->addLayout(formLayout);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, &QDialogButtonBox::accepted, this, &DynamicDialog::onAccept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mainLayout->addWidget(buttons);
}

void DynamicDialog::buildFormForMode()
{


    switch (currentMode) {
    case Mode::AddStudent: {

        auto widgets = FormBuilder::buildAddStudentForm(this);

        ManagerStudent_addStudentFileEdit = widgets.fileEdit;
        ManagerStudent_addStudentDataEdit = widgets.dataEdit;
        btnAddStudentBrowse = widgets.browseButton;

        ManagerStudent_addStudentFileEdit->setObjectName("addStudentFileEdit_ManagerStudent_");
        ManagerStudent_addStudentDataEdit->setObjectName("addStudentDataEdit_ManagerStudent_");


        serializer->DataSerelization(this, ModeSerelization::ManagerStudent);

        LayaoutBuilder::addStudentLayout(formLayout, btnAddStudentBrowse, ManagerStudent_addStudentFileEdit, ManagerStudent_addStudentDataEdit);

        FormBuilder::setupBrowseButton(btnAddStudentBrowse, ManagerStudent_addStudentFileEdit, fileManager.get());

        setWindowTitle("Добавить студента");
        break;
    }
    case Mode::PreviewFile: {

        auto widgets = FormBuilder::builSeeFileStudentForm(this);

        ManagerStudent_printFileEdit = widgets.printFileEdit;
        studentDisplay = widgets.studentDisplay;
        btnPrintFileBrowse = widgets.btnPrintFileBrowse;


        ManagerStudent_printFileEdit->setObjectName("printFileEdit_ManagerStudent_");

        serializer->DataSerelization(this, ModeSerelization::ManagerStudent);

        LayaoutBuilder::addSeeFiletLayout(formLayout, btnPrintFileBrowse, ManagerStudent_printFileEdit, studentDisplay);

        FormBuilder::setupBrowseButton(btnPrintFileBrowse, ManagerStudent_printFileEdit, fileManager.get());

        studentDisplay->setReadOnly(true);

        setWindowTitle("Просмотр содержимого файла");
        break;
    }
    case Mode::SortStudent: {

        auto widgets = FormBuilder::buildSortStudentForm(this);

        ManagerStudent_sortInputFileEdit = widgets.sortInputFileEdit;
        ManagerStudent_sortOutputFileEdit = widgets.sortOutputFileEdit;
        btnSortInputBrowse = widgets.btnSortInputBrowse;

        ManagerStudent_sortInputFileEdit->setObjectName("sortInputFileEdit_ManagerStudent_");
        ManagerStudent_sortOutputFileEdit->setObjectName("sortOutputFileEdit_ManagerStudent_");


        serializer->DataSerelization(this, ModeSerelization::ManagerStudent);

        LayaoutBuilder::addSortLayout(formLayout, btnSortInputBrowse, ManagerStudent_sortInputFileEdit, ManagerStudent_sortOutputFileEdit);

        FormBuilder::setupBrowseButton(btnSortInputBrowse, ManagerStudent_sortInputFileEdit, fileManager.get());

        setWindowTitle("Сортировка файла");
        break;
    }
    case Mode::DeleteStudent: {

        auto widgets = FormBuilder::builDeletedStudentForm(this);

        ManagerStudent_deleteFileEdit = widgets.deleteFileEdit;
        ManagerStudent_deleteNameEdit = widgets.deleteNameEdit;
        ManagerStudent_deleteScoreEdit = widgets.deleteScoreEdit;
        btnDeleteFileBrowse = widgets.btnDeleteFileBrowse;

        ManagerStudent_deleteFileEdit ->setObjectName("deleteFileEdit_ManagerStudent_");
        ManagerStudent_deleteNameEdit ->setObjectName("deleteNameEdit_ManagerStudent_");
        ManagerStudent_deleteScoreEdit->setObjectName("deleteScoreEdit_ManagerStudent_");

        serializer->DataSerelization(this, ModeSerelization::ManagerStudent);

        LayaoutBuilder::addDeleteLayout(formLayout, btnDeleteFileBrowse, ManagerStudent_deleteFileEdit, ManagerStudent_deleteNameEdit, ManagerStudent_deleteScoreEdit);

        FormBuilder::setupBrowseButton(btnDeleteFileBrowse, ManagerStudent_deleteFileEdit, fileManager.get());

        setWindowTitle("Удаление Студента");
        break;
    }
    case Mode::FindStudent: {

        auto widgets = FormBuilder::buildFindStudentForm(this);

        ManagerStudent_findFileEdit = widgets.findFileEdit;
        ManagerStudent_findNameEdit = widgets.findNameEdit;
        ManagerStudent_findScoreEdit = widgets.findScoreEdit;
        btnFindFileBrowse = widgets.btnFindFileBrowse;

        ManagerStudent_findFileEdit ->setObjectName("findFileEdit_ManagerStudent_");
        ManagerStudent_findNameEdit ->setObjectName("findNameEdit_ManagerStudent_");
        ManagerStudent_findScoreEdit->setObjectName("findScoreEdit_ManagerStudent_");


        serializer->DataSerelization(this, ModeSerelization::ManagerStudent);

        LayaoutBuilder::addDeleteLayout(formLayout, btnFindFileBrowse, ManagerStudent_findFileEdit, ManagerStudent_findNameEdit, ManagerStudent_findScoreEdit);

        FormBuilder::setupBrowseButton(btnFindFileBrowse, ManagerStudent_findFileEdit, fileManager.get());

        setWindowTitle("Найти Студента");
        break;
    }
    default:
        break;
    }
}

void DynamicDialog::handleAddStudent()
{
    const QString file = ManagerStudent_addStudentFileEdit->text();
    const QString data = ManagerStudent_addStudentDataEdit->text();
    handleAdd->handleAddStudent(file, data,ManagerStudent_addStudentDataEdit,this);
}

void DynamicDialog::handlePriviewFile()
{
   const QString file = ManagerStudent_printFileEdit->text().trimmed();
    handleAdd->handlePriviewFile(file,studentDisplay,this);
}

void DynamicDialog::handleSortStudent()
{
    const QString FileInput = ManagerStudent_sortInputFileEdit->text();
    const QString FileOutput = ManagerStudent_sortOutputFileEdit->text();

    handleAdd->handleSortStudent(FileInput,FileOutput,this);

}

void DynamicDialog::handleDeleteStudent()
{
    QString name = ManagerStudent_deleteNameEdit->text();
    QString ball = ManagerStudent_deleteScoreEdit->text();
    QString file = ManagerStudent_deleteFileEdit->text();
    handleAdd->handleDeleteStudent(file,name,ball,this);
}

void DynamicDialog::handleFindStudent()
{
    QString file = ManagerStudent_findFileEdit->text().trimmed();
    QString name = ManagerStudent_findNameEdit->text().trimmed();
    QString score = ManagerStudent_findScoreEdit->text().trimmed();
    handleAdd->handleFindStudent(file,name,score,this);
}

void DynamicDialog::onAccept()
{
    switch (currentMode) {
    case Mode::AddStudent:
        handleAddStudent();
        break;
    case Mode::PreviewFile:
        handlePriviewFile();
        break;
    case Mode::DeleteStudent:
        handleDeleteStudent();
        break;
    case Mode::FindStudent:
        handleFindStudent();
        break;
    case Mode::SortStudent:
        handleSortStudent();
        break;
    default:
        break;
    }
}

