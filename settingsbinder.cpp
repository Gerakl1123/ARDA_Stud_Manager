#include "settingsbinder.h"
#include"JsonKeys.h"


SettingsBinder::SettingsBinder(QObject *parent)
    : QObject{parent}
{
    logicOperation = std::make_unique<LogicOperation>();
}


void SettingsBinder::ConnectionsContest(QLineEdit* line, const QString& org, const QString& app, const QString& key)
{
    QObject::connect(line,&QLineEdit::textChanged,this,[=](const QString& text){
        QSettings tempSettings(org,app);
        tempSettings.setValue(key,text);
    });
}

void SettingsBinder::ConnectionsGradesMenu(QTableWidget* table,const QString& org, QSettings& settings,const QString& app)
{

    QObject::connect(table,&QTableWidget::cellChanged,this,[=](){
        QSettings settings(org,app);

        settings.setValue("rowCount",table->rowCount());
        settings.setValue("columnCount",table->columnCount());

        if (logicOperation)
            logicOperation->FillSettingsTable(settings, table);

    });

}

