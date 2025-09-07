#ifndef LOGICOPERATION_H
#define LOGICOPERATION_H
#include"Logger.h"
#include"Validator.h"
#include"Loader.h"
#include<QTextEdit>
#include<optional>
#include<QTableWidgetItem>

class SerializerData;

class LogicOperation
{
public:
    bool handleAddStudent(const QString& file, const QString& data,QLineEdit* LineEditClear,QWidget* parent);
    QString handlePriviewFile(const QString& file,QTextEdit* display,QWidget* parent);
    bool handleSortStudent(const QString& file,const QString& saveFile,QWidget* parent);
    void handleDeleteStudent(const QString& file,const QString& name, const QString& score, QWidget* parent);
    void handleFindStudent(const QString& file, const QString& name, const QString& score,QWidget* parent);

    std::optional<double> handleAutoTestStudent(QTableWidgetItem* checkItem,QList<int>& averageScore);

    double converterTOnumberInString(const QString& number);

    void FillSettingsTable(QSettings& settings,QTableWidget* t);
    void FillTableWidget(QSettings& settings,QTableWidget* t,int row,int column);

};


#endif // LOGICOPERATION_H
