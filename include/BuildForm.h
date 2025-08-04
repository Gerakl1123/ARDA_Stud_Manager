#ifndef BUILDFORM_H
#define BUILDFORM_H
#include<QLineEdit>
#include<QPushButton>
#include<QTextEdit>
#include <QFormLayout>
#include"FileChooicer.h"
#include"dialogcontest.h"
#include<QString>

struct AddStudentWidgets
{
    QLineEdit* fileEdit;
    QLineEdit* dataEdit;
    QPushButton* browseButton;
};

struct SortStudentWidgets
{
    QLineEdit* sortInputFileEdit = nullptr;
    QLineEdit* sortOutputFileEdit = nullptr;
    QPushButton* btnSortInputBrowse = nullptr;

};

struct DeleteStudentWidgets
{
    QLineEdit* deleteFileEdit = nullptr;
    QLineEdit* deleteNameEdit = nullptr;
    QLineEdit* deleteScoreEdit = nullptr;
    QPushButton* btnDeleteFileBrowse = nullptr;
};
struct FindStudentWidgets
{
    QLineEdit* findFileEdit = nullptr;
    QLineEdit* findNameEdit = nullptr;
    QLineEdit* findScoreEdit = nullptr;
    QPushButton* btnFindFileBrowse = nullptr;
};

struct SeeFileStudentWidgets
{
    QTextEdit* studentDisplay = nullptr;
    QLineEdit* printFileEdit = nullptr;
    QPushButton* btnPrintFileBrowse = nullptr;
};



class FormBuilder
{
public:

     static AddStudentWidgets buildAddStudentForm(QWidget* parent);
    static  SortStudentWidgets buildSortStudentForm(QWidget* parent);
     static DeleteStudentWidgets builDeletedStudentForm(QWidget* parent);
    static  FindStudentWidgets buildFindStudentForm(QWidget* parent);
     static  SeeFileStudentWidgets builSeeFileStudentForm(QWidget* parent);
     //Contest Builder
     QList<QPair<QLineEdit*,QPushButton*>> initializer(QWidget* w);

    static void setupBrowseButton(QPushButton *btn,QLineEdit* line,FileManager* fileManager);

 private:
    QMap<QString,QString> nameLineButton;

      void setupNameHash();
};

class LayaoutBuilder
{
public:
    static void addStudentLayout(QFormLayout* formLayout, QPushButton*  btn, QLineEdit* file, QLineEdit*  data);
    static void addSortLayout(QFormLayout* formLayout, QPushButton*  btn, QLineEdit*  file, QLineEdit*  data);
    static void addSeeFiletLayout(QFormLayout *formLayout, QPushButton * btn, QLineEdit * file, QTextEdit * display);
    static void addFindLayout(QFormLayout* formLayout, QPushButton*  btn, QLineEdit*  file, QLineEdit*  name,QLineEdit* score);
    static void addDeleteLayout(QFormLayout* formLayout, QPushButton*  btn, QLineEdit*  file, QLineEdit*  name,QLineEdit* score);

};


#endif // BUILDFORM_H
