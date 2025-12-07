#include "FileChooicer.h"



FileManager::FileManager(QWidget *parent)
    : QWidget(parent)
{

}
QString FileManager::saveFile()
{
    return QFileDialog::getSaveFileName(
        this,
        "Сохранить конфиг",
        "",
        "JSON файлы (*.json);;Все файлы (*.*)"
        );
}

QString FileManager::chooseFile()
{
    return QFileDialog::getOpenFileName(this,
    "Выберите файл",
    "",
    "Текстовые файлы (*.txt);;Все файлы (*.*)"
    );
}

QString FileManager::chooseFileJson()
{
    return QFileDialog::getOpenFileName(this,
        "Выберите файл",
        "",
        "Текстовые файлы (*.json);;Все файлы (*.*)"
        );
}

QString FileManager::saveFilePDF()
{
    return QFileDialog::getSaveFileName(this,
        "Выберите файл",
        "",
        "Pdf файл (*.pdf);; Все Файлы(*.*)"
        );
}

QString FileManager::chooseFileAbsolute()
{
    return QFileDialog::getOpenFileName(this,
        "Выберите папку",
        "",
        "Все Файлы(*)"
        );
}

QString FileManager::saveAbsoluteFile()
{
    return QFileDialog::getSaveFileName(this,
        "Выберите файл",
        "",
        "Все Файлы(*)"
        );
}

QString FileManager::saveDB()
{
    return QFileDialog::getSaveFileName(this,
        "Выберите файл",
        "",
        "DB файл (*);; Все файлы(*.*)"
        );
}

QString FileManager::ChoiceDB()
{
    return QFileDialog::getOpenFileName(this,
        "Выберите файл",
        "",
        "Текстовые файлы (*.db);;Все файлы (*.*)"
        );
}
