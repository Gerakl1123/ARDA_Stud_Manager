#include "settingsbinder.h"
#include"JsonKeys.h"
#include"LogicOperation.h"
#include<QCheckBox>
#include<QSpinBox>
#include<QComboBox>
#include<QDateEdit>

SettingsBinder::SettingsBinder(QObject *parent)
    : QObject{parent}
{
    logicOperation = std::make_unique<LogicOperation>();
}


void SettingsBinder::ConnectionsContest(QLineEdit* line, const QString& org, const QString& app, const QString& key)
{

    QObject::connect(line, &QLineEdit::textChanged, this, [org, app, key](const QString& text){
        QSettings settings(org, app);
        settings.setValue(key, text);
    });


}

void SettingsBinder::ConnectionsGradesMenu(QTableWidget* table,const QString& org,const QString& app)
{

    QObject::connect(table,&QTableWidget::cellChanged,this,[=](){
        QSettings settings(org,app);

        settings.setValue("rowCount",table->rowCount());
        settings.setValue("columnCount",table->columnCount());
        qDebug() << "SettengsBinder connect";
        if (logicOperation)
            logicOperation->FillSettingsTable(settings, table);

    });

}

void SettingsBinder::ConnectionsCourseWork(QTableWidget *t, const QString &org, const QString &app)
{

    QObject::connect(t,&QTableWidget::cellChanged,this,[=](){
        QSettings mainS(org,app);


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

void SettingsBinder::ConnectionsDiploma(QTableWidget *t, const QString &org, const QString &app)
{
    QObject::connect(t,&QTableWidget::cellChanged,this,[=](){
        QSettings mainS(org,app);


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

void SettingsBinder::ConnectionsExtra(QWidget *thisWidget, const QString &org, const QString &app)
{


    static QSettings mainS(org,app);

    if(auto* LineEdit = dynamic_cast<QLineEdit*>(thisWidget))
    {


        QObject::connect(LineEdit,&QLineEdit::textChanged,[=](const QString& text){

            mainS.setValue(LineEdit->objectName(),text);

        });
        mainS.sync();
        return;
    }else if(auto* CheckBox = dynamic_cast<QCheckBox*>(thisWidget))
    {

        QObject::connect(CheckBox,&QCheckBox::checkStateChanged,[=](Qt::CheckState state){


            mainS.setValue(CheckBox->objectName(),static_cast<int>(state));

        });
        mainS.sync();
        return;
    }else if(auto* SpinBox = dynamic_cast<QSpinBox*>(thisWidget))
    {


        QObject::connect(SpinBox,&QSpinBox::valueChanged,[=](int value){

            mainS.setValue(SpinBox->objectName(),value);

        });
        mainS.sync();
        return;
    }
}

void SettingsBinder::ConnectionsPassport(QWidget *thisWidget, const QString &org, const QString &app)
{

    static QSettings mainS(org,app);


    if(auto* LineEdit = dynamic_cast<QLineEdit*>(thisWidget))
    {


        QObject::connect(LineEdit,&QLineEdit::textChanged,[=](const QString& text){

            mainS.setValue(LineEdit->objectName(),text);

        });
        mainS.sync();
        return;
    }else if(auto *ComboBox = dynamic_cast<QComboBox*>(thisWidget))
    {

        QObject::connect(ComboBox,&QComboBox::currentTextChanged,[=](const QString& text){

            mainS.setValue(ComboBox->objectName(),text);

        });
        mainS.sync();
        return;
    }
    else if( auto* Date = dynamic_cast<QDateEdit*>(thisWidget))
    {

        QObject::connect(Date,&QDateEdit::dateChanged,[=](const QDate& date){

            mainS.setValue(Date->objectName(),date);
        });

        mainS.sync();
        return;
    }
}

