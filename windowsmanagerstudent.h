#ifndef WINDOWSMANAGERSTUDENT_H
#define WINDOWSMANAGERSTUDENT_H

#include <QWidget>
#include<QScreen>
#include<QPushButton>
#include<QLabel>
#include <QLineEdit>
#include<QVBoxLayout>
#include"../include/Student.h"
#include<QMessageBox>
#include<QTextEdit>
#include "windowsmanagerstudent.h"
#include "mainwindow.h"
#include<QIcon>
#include<QGroupBox>
#include<QFile>

class MainWindow;

extern Stud manag;

class WindowsManagerStudent : public QWidget
{
    Q_OBJECT
public:
  explicit WindowsManagerStudent(QWidget *parent = nullptr);


  private:

  //AddStud
  QPushButton* ButtonAddStudent;
    QLineEdit* lineFileToSaveData;
      QLineEdit* lineDataStudent;
  //end Stud
      QPushButton* ButtonBackMenu;
      std::unique_ptr<MainWindow> mainWin;
      //SORT STUDENT
      QPushButton* ButtonSortStud;
      //SaveEdit
      QPushButton* ButtonSaveEdit;
      QLineEdit* lineFileToSave;
    //findStudent
      QPushButton* ButtonFindStudent;
      QLineEdit* lineFiletoFind;
      QLineEdit* lineNameFindStudent;
      QLineEdit* lineBallFindStudent;

    //DeleteStudentFromFile&&DeleteStudentFromVector
      QPushButton* ButtonDeleteStudent;
      QLineEdit* lineFileToDelete;
      QLineEdit* linenNameToDelete;
      QLineEdit* lineBallToDelete;
      //printStud
      QTextEdit* StudDisplayArea;
      QLineEdit* lineFileToPrint;
      QPushButton* ButtonShowContent;
//==========================

      void Style();
      void applyStyle();
      void setupConnections();
private slots:
      void addStudentTiFile();
    void backMainMenu();
      void SortStud();
    void FindStudent();
    void SaveGlobalEdit();
    void DeleteStudent();
    void ShowFileContent();

signals:
      void authSuccess();

};

#endif // WINDOWSMANAGERSTUDENT_H
