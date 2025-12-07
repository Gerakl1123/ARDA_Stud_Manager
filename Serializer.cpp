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
