#include "addedobjectfiles.h"
#include "ui_addedobjectfiles.h"
#include <QProcess>
#include <QMessageBox>
#include <QFileInfo>
#include "../LogicOperation.h"
#include<QDesktopServices>
#include<QInputDialog>
#include"filemanagerdialog.h"

AddedObjectFiles::AddedObjectFiles(filemanagerdialog *fmd, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddedObjectFiles)
    , fmd_(fmd)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    model->setRootPath("");
    QItemSelectionModel* selectModel = new QItemSelectionModel(model,this);
    ui->listView->setModel(model);
    ui->listView->setSelectionModel(selectModel);
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(ui->listView,&QListView::doubleClicked,this,&AddedObjectFiles::on_listView_doubleClicked);
    connect(ui->listView->selectionModel(),&QItemSelectionModel::selectionChanged,this,&AddedObjectFiles::onSelectionChanged);
    connect(ui->btnZIP,&QPushButton::clicked,this,&AddedObjectFiles::zipData);
    connect(ui->btnQuit,&QPushButton::clicked,this,&AddedObjectFiles::backMenu);
}

AddedObjectFiles::~AddedObjectFiles()
{
    delete ui;
}

void AddedObjectFiles::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList indexes = selected.indexes();
    QString filePath;

    for(const auto& index : indexes)
    {
        if(index.column() == 0)
        {
            filePath = model->filePath(index);
            QFileInfo info(filePath);
            if(info.fileName() != "." && info.fileName() != "..")
            {
                files_.append(info);
            }
        }
    }

    QModelIndexList delIndexes = deselected.indexes();

    for(const auto& index : delIndexes)
    {
        if(index.column() == 0)
        {
            filePath = model->filePath(index);
            QFileInfo info(filePath);
            if(info.fileName() != "." && info.fileName() != "..")
            {
                files_.removeOne(info);
            }
        }
    }


}
bool AddedObjectFiles::zipData()
{

    if(files_.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Выбирете файлы & папки для архивации");
        return false;
    }




    QModelIndex index = ui->listView->rootIndex();
    QFileInfo info(model->filePath(index));

    QString zipFileName = QInputDialog::getText(
        this,
        "Введите название архива",
        "Имя:",
        QLineEdit::Normal,
        "",
        nullptr
    );

    zipFileName +=  ".zip";

    QStringList command;
    command << "-Command" << "Compress-Archive";

    QStringList filePaths;
    for(const auto& fileInfo : files_) {
        filePaths << fileInfo.absoluteFilePath();
    }

    command << "-Path" << ("'" + filePaths.join("','") + "'");
    command << "-DestinationPath" << ("'" + info.absoluteFilePath() + QDir::separator() + zipFileName + "'");
    command << "-Force";

    QProcess process;
    process.start("powershell", command);

    if (!process.waitForFinished(1800000))
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать архив через powershell ");
        return false;
    }

    if(process.exitCode() == 0) {
        QMessageBox::information(this, "Успех", "Архив создан: " + zipFileName);
        return true;
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка создания архива\n" + process.readAllStandardError());
        return false;
    }
}

void AddedObjectFiles::on_listView_doubleClicked(const QModelIndex &index)
{
    QFileInfo info(model->filePath(index));

    setWindowTitle(info.absolutePath());

    if(info.fileName() == ".")
    {
        ui->listView->setRootIndex(model->setRootPath("."));
    }
    else if(info.fileName() == "..")
    {
        QDir dir = info.path();
        dir.cdUp();
        ui->listView->setRootIndex(model->index(dir.absolutePath()));
    }
    else if(info.isDir())
    {
        ui->listView->setRootIndex(index);
    } else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
    }
}

void AddedObjectFiles::backMenu()
{
    fmd_->show();
    this->close();
}
