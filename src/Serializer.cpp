#include"Serializer.h"
#include<QList>
#include<QSettings>
#include<QLineEdit>

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

        if(mode == ModeSerelization::Attestat && !QLname.contains("_Attestat_") ||
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
