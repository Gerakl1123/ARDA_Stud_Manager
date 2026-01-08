#include "tablemanager.h"
#include<QSettings>
#include"JsonKeys.h"
TableManager::TableManager(QTableWidget *table, QObject *parent)
    : QObject{parent}
    , table_(table)
{}

void TableManager::processCellData(QTableWidgetItem *item)
{

    if(item->column() <= 5) return;

    if(item->text().isEmpty()) return;
    QString text = item->text();
    QString grades;
    QString marks;
    int row = item->row();

    for(const QChar& c : text)
    {
        if(c.isDigit())
        {
            grades+=c;
        }
        else{
            marks+=c;
        }
    }

    QTableWidgetItem* gradeItem = table_->item(row,4);
    if(!gradeItem)
    {
        gradeItem = new QTableWidgetItem();
        table_->setItem(row, 4, gradeItem);
    }
    QString currentTextGrades = gradeItem->text();

    if(!grades.isEmpty())
    {
        if(!currentTextGrades.isEmpty())
        {
            gradeItem->setText(currentTextGrades + ", " + grades);
        }
        else
        {
            gradeItem->setText(grades);
        }
    }
    QTableWidgetItem* marksItem = table_->item(row,5);
    if(!marksItem)
    {
        marksItem = new QTableWidgetItem();
        table_->setItem(row, 5, marksItem);
    }
    QString currentTextMarks = marksItem->text();

    if(!marks.isEmpty()){
        if(!currentTextMarks.isEmpty())
        {
            marksItem->setText(currentTextMarks + ", " + marks);
        }
        else
        {
            marksItem->setText(marks);
        }
    }
}

bool TableManager::deleteDataTable()
{
    QSettings settings(SerelizationData::ORG_NAME,"Lessons");
    int countColumn = settings.value("columnCount").toInt(nullptr);
    bool result = false;

    for(int row = 0; row < table_->rowCount();++row)
    {
        for(int col = 0;  col < table_->columnCount();++col)
        {
            qDebug() << "DeletefataTable";
             if(col >= 6)
            {
                settings.remove(QString("row_%1_col_%2").arg(row).arg(col));
                result = true;
            }
        }
    }
    if(result)
    {
        settings.setValue("columnCount",--countColumn);
        settings.sync();
    }

    return true;
}
