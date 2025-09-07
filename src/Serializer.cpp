#include"Serializer.h"
#include<QList>
#include<QLineEdit>
#include"../JsonKeys.h"
#include<QDateEdit>
#include<QComboBox>
#include"../IODataHandler.h"
#include"../JsonKeys.h"
#include"Validator.h"
#include"../settingsbinder.h"
#include"LogicOperation.h"

SerializerData::SerializerData()
    : saveDataManager(std::make_unique<ImportSaveData>())

{
}
SerializerData::~SerializerData()
{
    delete logicOperation;
}
void SerializerData::DataSerelization(QWidget *w, ModeSerelization mode)
{

    SettingsBinder* binder = new SettingsBinder(w);

    QString app = Validator::SwitchAppContest(mode);
    QSettings mainSettings(SerelizationData::ORG_NAME,app);

    QList<QLineEdit*> lines = w->findChildren<QLineEdit*>();

    for(const auto line : lines)
    {
        QString QLname = line->objectName();
        if(!Validator::IsObjectForMode(QLname,mode))
        {
            continue;
        }
        QString key = app + QLname;

        line->setText(mainSettings.value(key).toString());
        //Save Text
        binder->ConnectionsContest(line,SerelizationData::ORG_NAME,app,key);

    }

}

void SerializerData::DataSerelizationMenuStudentRecords(QTableWidget *t, QWidget *p,ModeSerelization mode)
{

    SettingsBinder* binder = new SettingsBinder(p);
    logicOperation = new LogicOperation;

    QString app = Validator::SwitchAppGradesMenu(mode);
    QSettings mainS(SerelizationData::ORG_NAME,app);

    binder->ConnectionsGradesMenu(t,SerelizationData::ORG_NAME,mainS,app);

    int currRow = mainS.value("rowCount").toInt();
    int currColumn = mainS.value("columnCount").toInt();

    t->setRowCount(currRow);

    logicOperation->FillTableWidget(mainS,t,currRow,currColumn);

}

void SerializerData::DataSerelizationCourse(QTableWidget *t, QWidget *p)
{

    QString app = "CourseWork";
    QSettings mainS(SerelizationData::ORG_NAME,app);


    t->blockSignals(true);

    int rowCount = mainS.value("rowCount").toInt(); // 2
    int colCount = mainS.value("columnCount").toInt(); // 3

    t->setRowCount(rowCount);
    t->setColumnCount(colCount);

    for (int row = 0; row < rowCount; ++row) {

        for (int col = 0; col < colCount; ++col) {
            QString key = QString("row_%1_col_%2").arg(row).arg(col);
            QString header = t->horizontalHeaderItem(col)->text();
            QVariant value = mainS.value(key);


            if (header == JsonKeys::Date)
            {

                QDateEdit* dateEdit = new QDateEdit(p);
                QDate date = QDate::fromString(value.toString(), "dd.MM.yyyy");
                dateEdit->setDate(date);
                t->setCellWidget(row, col, dateEdit);

                QObject::connect(dateEdit, &QDateEdit::editingFinished, p, [=]() {
                    QSettings mainS(SerelizationData::ORG_NAME, app);
                    mainS.setValue(key, dateEdit->date().toString("dd.MM.yyyy"));
                });

            }
            else if(header == JsonKeys::StageWork)
            {
                QComboBox* comboBox = new QComboBox(p);
                comboBox->addItems(Stages::StageList);
                comboBox->setCurrentText(value.toString());
                t->setCellWidget(row,col,comboBox);

                QObject::connect(comboBox, &QComboBox::currentTextChanged, p, [=]() {
                    QSettings mainS(SerelizationData::ORG_NAME, app);
                    mainS.setValue(key, comboBox->currentText());
                });
            }
            else{
                QTableWidgetItem* item = new QTableWidgetItem(value.toString());
                t->setItem(row,col,item);
            }


        }
    }
      t->blockSignals(false);



      QObject::connect(t,&QTableWidget::cellChanged,p,[=](){
          QSettings mainS(SerelizationData::ORG_NAME,app);


          mainS.setValue("rowCount", t->rowCount());
          mainS.setValue("columnCount", t->columnCount());

          for(int i = 0;i<t->rowCount();i++)
          {
              for(int j = 0;j<t->columnCount();j++)
              {
                  QTableWidgetItem* item = t->item(i,j);
                  QString key = QString("row_%1_col_%2").arg(i).arg(j);

                  QString header = t->horizontalHeaderItem(i)->text();

                  if (item) {
                      mainS.setValue(key, item->text());
                  }
                  else if(header == JsonKeys::StageWork)
                  {
                      if (auto comboBox = qobject_cast<QComboBox*>(t->cellWidget(i, j))) {
                          mainS.setValue(key, comboBox->currentText());
                      }
                  }
                  else if(header == JsonKeys::Date)
                  {
                      if(auto CurrDate = qobject_cast<QDateEdit*>(t->cellWidget(i,j)))
                      {
                          mainS.setValue(key,CurrDate->date().toString("dd.MM.yyyy"));
                      }
                  }
              }
          }
      });
}

void SerializerData::DataSerelizationDiploma(QTableWidget *t, QWidget *p)
{

   QString app = "Diploma";
   QSettings mainS(SerelizationData::ORG_NAME,app);


    t->blockSignals(true);

    int rowCount = mainS.value("rowCount").toInt(); // 2
    int colCount = mainS.value("columnCount").toInt(); // 3

    t->setRowCount(rowCount);
//    t->setColumnCount(colCount);

//Вынрузка в таблицу из реестра

    for(int row = 0; row< t->rowCount(); ++row)
    {
        for(int col = 0; col <t->columnCount(); ++col)
        {
            QString key = QString("row_%1_col_%2").arg(row).arg(col);
            QString header = t->horizontalHeaderItem(col)->text();
            QVariant value = mainS.value(key);

            if(header == JsonKeys::Date)
            {
                QDateEdit* dateEdit = new QDateEdit(p);
                QDate date = QDate::fromString(value.toString(), "dd.MM.yyyy");
                dateEdit->setDate(date);

                t->setCellWidget(row,col,dateEdit);

                QObject::connect(dateEdit, &QDateEdit::dateChanged, p, [=](const QDate &d){
                    QSettings mainS(SerelizationData::ORG_NAME, app);
                    mainS.setValue(key, d.toString("dd.MM.yyyy"));
                });

            }
            else if(header == JsonKeys::StageWork)
            {
                QComboBox* combo = new QComboBox(p);
                combo->addItems(Stages::StageListDiplom);
                combo->setCurrentText(value.toString());

                t->setCellWidget(row,col,combo);


                QObject::connect(combo, &QComboBox::currentTextChanged, p, [=]() {
                    QSettings mainS(SerelizationData::ORG_NAME, app);
                    mainS.setValue(key, combo->currentText());
                });
            }
            else
            {
                QTableWidgetItem* item = new QTableWidgetItem(value.toString());
                if(item){
                    t->setItem(row,col,item);
                }else
                {
                    continue;
                }
            }

        }
    }

    t->blockSignals(false);

    QObject::connect(t,&QTableWidget::cellChanged,p,[=](){
        QSettings mainS(SerelizationData::ORG_NAME,app);


        mainS.setValue("rowCount", t->rowCount());
        mainS.setValue("columnCount", t->columnCount());

        for(int row = 0; row < t->rowCount(); ++row)
        {
            for(int col = 0; col<t->columnCount(); ++col)
            {
                QTableWidgetItem* item = t->item(row,col);
                QString key = QString("row_%1_col_%2").arg(row).arg(col);

                QString header = t->horizontalHeaderItem(col)->text();

                if (item) {
                    mainS.setValue(key, item->text());
                }
                else if(header == JsonKeys::StageWork)
                {
                    if (auto comboBox = qobject_cast<QComboBox*>(t->cellWidget(row, col))) {
                        mainS.setValue(key, comboBox->currentText());
                    }
                }
                else if(header == JsonKeys::Date)
                {
                    if(auto CurrDate = qobject_cast<QDateEdit*>(t->cellWidget(row,col)))
                    {
                        qDebug() << "Current date: "<< CurrDate->date().toString("dd.MM.yyyy");
                        mainS.setValue(key,CurrDate->date().toString("dd.MM.yyyy"));
                    }
                }


            }
        }

    });

}
