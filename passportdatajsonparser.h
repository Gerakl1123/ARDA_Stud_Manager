#ifndef PASSPORTDATAJSONPARSER_H
#define PASSPORTDATAJSONPARSER_H
#include<QWidget>
#include<QString>
#include<QComboBox>
#include"LogicOperation.h"
#include<QDateEdit>
#include"ManagerDataCore/extradata.h"
#include"ManagerDataCore/passport.h"
#include"FileChooicer.h"
class PassportDataJSONParser
{
public:
    PassportDataJSONParser();

public:
    void SaveJsonPassport(QWidget* w);
    void SaveJsonExtraData(QWidget* w);
private:

    std::unique_ptr<PassPort> Pass;
    std::unique_ptr<ExtraData> extraData;
    std::unique_ptr<FileManager> fileManager;
};

#endif // PASSPORTDATAJSONPARSER_H
