#ifndef STUDENTDATAHANDLER_H
#define STUDENTDATAHANDLER_H
#include"DataHandler.h"
#include"FileChooicer.h"

class ImportSaveData
{
private:
    std::vector<std::shared_ptr<Student>> students;
public:
    ~ImportSaveData() = default;
    ImportSaveData() = default;

    std::vector<std::shared_ptr<Student>> loadFromFile(const QString& fileName);
    bool saveData(const QString& fileName,std::vector<std::shared_ptr<Student>>& students);

    void saveConfig(QWidget* parent);

private:
    std::unique_ptr<FileManager> fileManager;
};

#endif // STUDENTDATAHANDLER_H
