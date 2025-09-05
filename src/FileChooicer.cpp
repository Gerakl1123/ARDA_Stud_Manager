#include "FileChooicer.h"



FileManager::FileManager(QWidget *parent)
    : parentWidget(parent)
{

}
QString FileManager::saveFile()
{
    return QFileDialog::getSaveFileName(
        parentWidget,
        "Сохранить конфиг",
        "",
        "JSON файлы (*.json);;Все файлы (*.*)"
        );
}

QString FileManager::chooseFile()
{
    return QFileDialog::getOpenFileName(parentWidget,
        "Выберите файл",
        "",
        "Текстовые файлы (*.txt);;Все файлы (*.*)"
        );
}

QString FileManager::chooseFileJson()
{
    return QFileDialog::getOpenFileName(parentWidget,
        "Выберите файл",
        "",
        "Текстовые файлы (*.json);;Все файлы (*.*)"
        );
}

QString FileManager::saveFilePDF()
{
    return QFileDialog::getSaveFileName(parentWidget,
        "Выберите файл",
        "",
        "Pdf файл (*.pdf);; Все Файлы(*.*)"
        );
}
