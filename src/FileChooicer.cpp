#include "FileChooicer.h"



FileManager::FileManager(QWidget *parent)
    : parentWidget(parent)
{

}

QString FileManager::chooseFile()
{
    return QFileDialog::getOpenFileName(parentWidget,
        "Выберите файл",
        "",
        "Текстовые файлы (*.txt);;Все файлы (*.*)"
        );
}
