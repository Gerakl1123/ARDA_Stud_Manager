#ifndef LOGICOPERATION_H
#define LOGICOPERATION_H
#include"Logger.h"
#include"Validator.h"
#include"Loader.h"
#include"Serializer.h"
#include<QTextEdit>

class IHandleStudent
{
public:
    bool handleAddStudent(const QString& file, const QString& data,QLineEdit* LineEditClear,QWidget* parent);
    QString handlePriviewFile(const QString& file,QTextEdit* display,QWidget* parent);
    bool handleSortStudent(const QString& file,const QString& saveFile,QWidget* parent);
    void handleDeleteStudent(const QString& file,const QString& name, const QString& score, QWidget* parent);
    void handleFindStudent(const QString& file, const QString& name, const QString& score,QWidget* parent);

};


#endif // LOGICOPERATION_H
