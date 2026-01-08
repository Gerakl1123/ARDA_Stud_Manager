#include"Serializer.h"
#include<QList>
#include<QLineEdit>
#include"JsonKeys.h"
#include<QDateEdit>
#include<QComboBox>
#include"IOCore/IODataHandler.h"
#include"JsonKeys.h"
#include"Validator.h"
#include"settingsbinder.h"
#include"LogicOperation.h"
#include<QSpinBox>
#include<QCheckBox>

SerializerData::SerializerData(QObject* parent = nullptr)
    : saveDataManager(std::make_unique<ImportSaveData>()),
    logicOperation (std::make_unique<LogicOperation>())

{

}
SerializerData::~SerializerData()
{
}
void SerializerData::DataSerelization(QWidget *w, ModeSerelization mode)
{
    binder = new SettingsBinder(w); // передаю родитля утечки нету (вроде_-_)

    QString app = Validator::SwitchAppContest(mode);

    QSettings mainSettings(SerelizationData::ORG_NAME,app);
    QList<QLineEdit*> lines = w->findChildren<QLineEdit*>();

    for(const auto line : lines)
    {
        QString QLname = line->objectName();
        if(!Validator::IsObjectForMode(QLname, mode)) continue;

        QString key = app + QLname;


        line->setText(mainSettings.value(key).toString());

        binder->ConnectionsContest(line,SerelizationData::ORG_NAME,app,key);
    }
}

void SerializerData::DataSerelizationMenuStudentRecords(QTableWidget *t, QWidget *p,ModeSerelization mode)
{

    binder = new SettingsBinder(p);

    QString app = Validator::SwitchAppGradesMenu(mode);

    QSettings mainS(SerelizationData::ORG_NAME,app);

    binder->ConnectionsGradesMenu(t,SerelizationData::ORG_NAME,app);

   // mainS.setValue("columnCount",1);

    int currRow = mainS.value("rowCount").toInt();

    int currColumn = 0;

    if(mode == ModeSerelization::Lessons)
    {
        currColumn = mainS.value("columnCount",6).toInt();
    }
    else
    {
        currColumn = mainS.value("columnCount",static_cast<int>(mode)).toInt();
    }

    t->setRowCount(currRow);
    t->setColumnCount(currColumn);

    logicOperation->FillTableWidget(mainS,t,currRow,currColumn);

}

void SerializerData::DataSerelizationCourse(QTableWidget *t, QWidget *p)
{

    binder = new SettingsBinder(p);

    QString app = "CourseWork";
    QSettings mainS(SerelizationData::ORG_NAME,app);


    t->blockSignals(true);
    int rowCount = mainS.value("rowCount").toInt(); // 2
    int colCount = mainS.value("columnCount",7).toInt(); // 3

    t->setRowCount(rowCount);
    t->setColumnCount(colCount);


    logicOperation->FillTableWidgetCourse(p,mainS,t,app);

    t->blockSignals(false);

    binder->ConnectionsCourseWork(t,SerelizationData::ORG_NAME,app);

}

void SerializerData::DataSerelizationDiploma(QTableWidget *t, QWidget *p)
{

    binder = new SettingsBinder(p);

   QString app = "Diploma";
   QSettings mainS(SerelizationData::ORG_NAME,app);


   t->blockSignals(true);

   int rowCount = mainS.value("rowCount").toInt(); // 2
   int colCount = mainS.value("columnCount",10).toInt(); // 3

   t->setRowCount(rowCount);
   //  t->setColumnCount(colCount);


   logicOperation->FillTableWidgetDiploma(p,mainS,t,app);

   t->blockSignals(false);


   binder->ConnectionsDiploma(t,SerelizationData::ORG_NAME,app);


}

void SerializerData::DataSerelizationExtra(QWidget *thisWidget)
{


    binder = new SettingsBinder(thisWidget);

    QString app = "DataStudentsExtra";
    QSettings mainS(SerelizationData::ORG_NAME,app);

    QList<QLineEdit*> lineEdits = thisWidget->findChildren<QLineEdit*>();
    QList<QSpinBox*> SpinBoxes = thisWidget->findChildren<QSpinBox*>();
    QList<QCheckBox*> CheckBoxes = thisWidget->findChildren<QCheckBox*>();

    for(const auto& line : lineEdits)
    {
        QString key = line->objectName();


        line->blockSignals(true);
        line->setText(mainS.value(key).toString());
        line->blockSignals(false);

        binder->ConnectionsExtra(line,SerelizationData::ORG_NAME,app);
    }
    for(const auto& spins : SpinBoxes)
    {
        QString key = spins->objectName();

        spins->blockSignals(true);
        spins->setValue(mainS.value(key).toInt());
        spins->blockSignals(false);

        binder->ConnectionsExtra(spins,SerelizationData::ORG_NAME,app);
    }
    for(const auto& CheckBox : CheckBoxes)
    {
        QString key = CheckBox->objectName();

        CheckBox->blockSignals(true);
        CheckBox->setCheckState(static_cast<Qt::CheckState>(mainS.value(key).toInt()));
        CheckBox->blockSignals(false);
        binder->ConnectionsExtra(CheckBox,SerelizationData::ORG_NAME,app);
    }


}

void SerializerData::DataSerelizationPassport(QWidget *thisWidget)
{
    binder = new SettingsBinder(thisWidget);

    QString app = "DataStudentsPassport";
    QSettings mainS(SerelizationData::ORG_NAME,app);

    QList<QLineEdit*> lineEdits = thisWidget->findChildren<QLineEdit*>();
    QList<QComboBox*> ComboBoxes = thisWidget->findChildren<QComboBox*>();
    QList<QDateEdit*> dateEdits = thisWidget->findChildren<QDateEdit*>();


    for(const auto& line : lineEdits)
    {
        QString key = line->objectName();


        line->blockSignals(true);
        line->setText(mainS.value(key).toString());
        line->blockSignals(false);

        binder->ConnectionsPassport(line,SerelizationData::ORG_NAME,app);
    }
    for(const auto& comboBox : ComboBoxes)
    {
        QString key = comboBox->objectName();


        comboBox->blockSignals(true);
        comboBox->setCurrentText(mainS.value(key).toString());
        comboBox->blockSignals(false);

        binder->ConnectionsPassport(comboBox,SerelizationData::ORG_NAME,app);
    }
    for(const auto& date : dateEdits)
    {
        QString key = date->objectName();


        date->blockSignals(true);
        date->setDate(mainS.value(key).toDate());
        date->blockSignals(false);

        binder->ConnectionsPassport(date,SerelizationData::ORG_NAME,app);
    }

}
