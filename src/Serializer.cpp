#include"Serializer.h"
#include<QList>
#include<QSettings>
#include<QLineEdit>
#include"../JsonKeys.h"
#include<QDateEdit>
#include<QComboBox>

void SerializerData::DataSerelization(QWidget *w, ModeSerelization mode)
{

    QString app;
    QString org = "ARDA";

    switch (mode) {
    case ModeSerelization::Attestat:
        app = "AttestatContest/";
        break;
    case ModeSerelization::MaxScore:
        app = "MaxScoreContest/";
        break;
    case ModeSerelization::ManagerStudent:
        app = "ManagerStudent/";
        break;
    default:
        break;
    }

    QSettings mainSettings(org,app);

    QList<QLineEdit*> lines = w->findChildren<QLineEdit*>();

    for(const auto line : lines)
    {
        QString QLname = line->objectName();

        if( mode == ModeSerelization::Attestat && !QLname.contains("_Attestat_") ||
            mode == ModeSerelization::MaxScore && !QLname.contains("_MaxScore_") ||
            mode == ModeSerelization::ManagerStudent && !QLname.contains("_ManagerStudent_"))
        {
            continue;
        }

        QString key = app + QLname;

        line->setText(mainSettings.value(key).toString());
        //Save Text
        QObject::connect(line,&QLineEdit::textChanged,w,[=](const QString& text){
            QSettings tempSettings(org,app);
            tempSettings.setValue(key,text);
        });

    }

}

void SerializerData::DataSerelizationMenuStudentRecords(QTableWidget *t, QWidget *p,ModeSerelization mode)
{
    QString app;
    QString org = "ARDA";

    switch (mode) {
    case  ModeSerelization::Lessons:
        app = "Lessons";
        break;
    case  ModeSerelization::Projects:
        app = "Projects";
        break;
    case ModeSerelization::Records:
        app="Records";
        break;
    default:
        break;
    }

    QSettings mainS(org,app);

    QObject::connect(t,&QTableWidget::cellChanged,p,[=](){
        QSettings mainS(org,app);
        mainS.setValue("rowCount",t->rowCount());
        mainS.setValue("columnCount",t->columnCount());


        for(int row=0;row< t->rowCount();row++)
        {

            for(int col=0;col< t->columnCount();col++)
            {
                QString key = QString("row_%1_col_%2").arg(row).arg(col);
                QTableWidgetItem* item = t->item(row, col);
                if (!item) continue;

                QString header = t->horizontalHeaderItem(col) ? t->horizontalHeaderItem(col)->text() : "";
                if (header == "Автомат" && (item->flags() & Qt::ItemIsUserCheckable)) {
                    mainS.setValue(key, static_cast<int>(item->checkState()));
                } else {
                    mainS.setValue(key, item->text());
                }
            }
        }

    });

    t->blockSignals(true);

    int currRow = mainS.value("rowCount").toInt();
    int currColumn = mainS.value("columnCount").toInt();


    t->setRowCount(currRow);

    for(int i = 0; i< currRow; i++)
    {
        for(int j = 0; j < currColumn;j++)
        {
            QString key = QString("row_%1_col_%2").arg(i).arg(j);
            QVariant value = mainS.value(key);
            QTableWidgetItem* item = t->item(i,j);            
            QString header = t->horizontalHeaderItem(j) ? t->horizontalHeaderItem(j)->text() : "";


            if (!item) {
                item = new QTableWidgetItem();
                t->setItem(i, j, item);
            }

            if (header == "Автомат") {
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                item->setCheckState(static_cast<Qt::CheckState>(mainS.value(key, Qt::Unchecked).toInt()));
            }  else {
                item->setText(value.toString());
            }

        }
    }

    t->blockSignals(false);

}

void SerializerData::DataSerelizationCourse(QTableWidget *t, QWidget *p)
{

    QString app = "CourseWork";
    QString org = "ARDA";
    QSettings mainS(org,app);


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
                    QSettings mainS(org, app);
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
                    QSettings mainS(org, app);

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
          QSettings mainS(org,app);


          mainS.setValue("rowCount", t->rowCount());
          mainS.setValue("columnCount", t->columnCount());

          for(int i = 0;i<t->rowCount();i++)
          {
              for(int j = 0;j<t->columnCount();j++)
              {
                  QTableWidgetItem* item = t->item(i,j);
                  QString key = QString("row_%1_col_%2").arg(i).arg(j);


                  if (item) {
                      mainS.setValue(key, item->text());
                  }
              }
          }
      });
}
