#include"StudentDataHandler.h"
#include<QFile>
#include<QLineEdit>
#include<QList>
#include"Validator.h"
#include<QMessageBox>
#include<QJsonDocument>
#include<QJsonObject>




std::vector<std::shared_ptr<Student>> ImportSaveData::loadFromFile(const QString& filePath)
{
    std::vector<std::shared_ptr<Student>> temp;


}

bool ImportSaveData::saveData(const QString &fileName, std::vector<std::shared_ptr<Student>> &students)
{
    return true;
}

void ImportSaveData::saveConfig(QWidget *parent)
{

    fileManager = std::make_unique<FileManager>(parent);

    QJsonObject config;

    QList<QLineEdit*> temp = parent->findChildren<QLineEdit*>();

    for(const auto& lines : temp)
    {
        QString line = lines->objectName();
        QString key = lines->text();

        config[line]=key;
    }

   QString path = fileManager->saveFile();

    QFile file(path);

    try{
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }catch(const std::logic_error& e)
    {
        QMessageBox::warning(parent,"Error open"," Error open file mode: write");
        return;
    }

    QJsonDocument doc(config);
    file.write(doc.toJson());
    file.close();

}
