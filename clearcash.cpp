#include "clearcash.h"
#include<QFile>
#include"Validator.h"
#include"QMessageBox"
#include"confrimdialog.h"

ClearCash::ClearCash() {}

void ClearCash::clearCashFiles()
{
    bool isClear = false;
    ConfrimDialog dlg;
    QStringList noCorrectFiles;

    if(dlg.exec() == QDialog::Accepted)
    {
        for(const auto& c : files)
        {
            QFile file(c);
            if(!file.open(QIODevice::Truncate | QIODevice::WriteOnly))
            {
                noCorrectFiles<<c;
            }
        }


    }else
    {
     QMessageBox::information(nullptr, "Очистка кэша", "Действие отменено");
     return;

    }

    if (noCorrectFiles.isEmpty()) {
        QMessageBox::information(nullptr, "Очистка кэша", "Кэш успешно очищен!");
    } else {
        QMessageBox::warning(nullptr, "Очистка кэша",
                             "Не удалось очистить файлы:\n" + noCorrectFiles.join("\n"));
    }

}

