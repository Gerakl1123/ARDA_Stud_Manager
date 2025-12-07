#ifndef ADDFULLINFOSTUDENT_H
#define ADDFULLINFOSTUDENT_H

#include <QWidget>
class StudentDataService;

namespace Ui {
class AddFullInfoStudent;
}

class AddFullInfoStudent : public QWidget
{
    Q_OBJECT

public:
    explicit AddFullInfoStudent(StudentDataService* pStudentDataS, QWidget *parent = nullptr);
    ~AddFullInfoStudent();

private:
    Ui::AddFullInfoStudent *ui;
    StudentDataService* StudentDataS;
public slots:
    void openPassportData();
    void openExtraData();
private slots:
    void BackMenu();
};

#endif // ADDFULLINFOSTUDENT_H
