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


class MainWindow;

class WindowsManagerStudent : public QWidget
{
    Q_OBJECT
public:
  explicit WindowsManagerStudent(QWidget *parent = nullptr);


  private:

  //AddStud
  std::unique_ptr<QPushButton> ButtonAddStudent;
    std::unique_ptr<QLineEdit> lineFileToSaveData;
      std::unique_ptr<QLineEdit> lineDataStudent;
  //end Stud
      std::unique_ptr<QPushButton> ButtonBackMenu;
      std::unique_ptr<MainWindow> mainWin;

private slots:
      void addStudentTiFile();
    void backMainMenu();
signals:
      void authSuccess();

};

#endif // WINDOWSMANAGERSTUDENT_H
