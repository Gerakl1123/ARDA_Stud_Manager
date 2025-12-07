#include "backup.h"
#include "ui_backup.h"
#include<QListView>
#include<QStorageInfo>
#include<QGridLayout>
#include <QMessageBox>
#include"../confrimdialog.h"
#include"filemanagerdialog.h"
#include<QItemSelectionModel>

BackUp::BackUp(filemanagerdialog* fmd,QWidget *parent)
    : QWidget(parent)
    , fmd_(fmd)
    , ui(new Ui::BackUp)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    model->setRootPath("");
    QItemSelectionModel* selectModel = new QItemSelectionModel(model,this);
    ui->sourceB->setModel(model);
    ui->BackUpB->setModel(model);
    ui->sourceB->setSelectionModel(selectModel);
    ui->sourceB->setSelectionMode(QAbstractItemView::ExtendedSelection);

    worker = new BackupWorker;
    thread = new QThread(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(true);
    ui->textEdit->setReadOnly(true);


    connect(ui->BackUpB,&QListView::doubleClicked,this,&BackUp::on_sourceB_doubleClicked);
    connect(ui->bntBckUp,&QPushButton::clicked,this,[this](){
        ui->bntBckUp->setEnabled(false);
        QMessageBox::StandardButton confrim = QMessageBox::question(
            this,
            "Подтверждение",
            "Вы уверены что хотите выполнить резервное копирование?",
            QMessageBox::Yes | QMessageBox::No
        );

        if (confrim == QMessageBox::Yes) {
            QModelIndex index = ui->BackUpB->currentIndex();
            QString s = model->filePath(ui->sourceB->rootIndex());
            QString b = model->filePath(index);
            qDebug()<< s << " " << b;
            emit startOperration(s, b);
        } else {
            QMessageBox::information(this, "Отмена", "Действие отменено");
            ui->bntBckUp->setEnabled(true);
        }
    });
    connect(worker,&BackupWorker::unlockBTN,this,[this](){
        ui->bntBckUp->setEnabled(true);
    });
    connect(worker,&BackupWorker::logMessage,this,[this](const QString& msg){
        ui->textEdit->append(msg);
    });
    connect(worker,&BackupWorker::finishedCopy,this,[this](){
        QMessageBox::information(this,"Копирование","Копирование файло завершенно!");
        ui->bntBckUp->setEnabled(true);
    });
    connect(worker,&BackupWorker::progressChanged,ui->progressBar,&QProgressBar::setValue);
    connect(ui->btnQuit,&QPushButton::clicked,this,&BackUp::Back);


    connect(this,&BackUp::startOperration,worker,&BackupWorker::runBackUp);
    connect(ui->sourceB->selectionModel(),&QItemSelectionModel::selectionChanged,this,&BackUp::onSelectionChanged);
    connect(ui->btnSelectElement,&QPushButton::clicked,this,[this](){
        QModelIndex index = ui->BackUpB->currentIndex();
        QString b = model->filePath(index);
        qDebug()<< b << " " << QString::number(files_.size());
        emit startOperation(files_,b);
    });

    connect(this,&BackUp::startOperation,worker,&BackupWorker::runBackUpNew);

    worker->moveToThread(thread);
    thread->start();
}

BackUp::~BackUp()
{

    thread->quit();
    thread->wait();
    worker->deleteLater();
    delete ui;
}



void BackUp::on_sourceB_doubleClicked(const QModelIndex &index)
{

    QListView* listView = qobject_cast<QListView*>(sender());

    QFileInfo fileInfo = model->fileInfo(index);

    if(fileInfo.fileName() == ".")
    {
        listView->setRootIndex(model->index(""));
    }else if(fileInfo.fileName() == "..")
    {
        QDir dir = fileInfo.path();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    }else if(fileInfo.isDir())
    {
        listView->setRootIndex(index);
    }
}

void BackUp::Back()
{
    this->close();
    fmd_->show();
}



// == WORKER LOGIC ==
void BackupWorker::runBackUp(QString sPath, QString bPath)
{
    QDir dir(sPath);
    sPath = dir.absolutePath();
    QDir dir2(bPath);
    bPath = dir2.absolutePath();

    if (!sPath.endsWith('/')) sPath += '/';
    if (!bPath.endsWith('/')) bPath += '/';

    int counter = 0;
    QDir s(sPath);
    QDir b(bPath);

    const bool isStorage = StorageBackup(s,b);
    if(!isStorage) return;
    QFileInfoList files;

    compareDirs(s, b, files);

    int totalFiles = files.size();

    for (const QFileInfo& c : files) {
        QString pathBackUp = c.filePath().replace(sPath, bPath);

        counter++;
        int progress = static_cast<int>((counter * 100.0) / totalFiles);
        emit progressChanged(progress);

        if (c.isDir()) {
            QDir().mkpath(pathBackUp);
        } else if (c.isFile()) {
            QFileInfo destFile(pathBackUp);
            QDir().mkpath(destFile.path());

            if (QFile::exists(pathBackUp)) {
                QFile::remove(pathBackUp);
            }

            if (!QFile::copy(c.absoluteFilePath(), pathBackUp)) {
                emit logMessage("Не удалось скопировать файл:" + c.filePath());
            } else {
                emit logMessage("Скопирован:" + c.filePath());
            }

        }
    }

    emit finishedCopy();
    qDebug()<< "End BackUp";
}
// ==========
void BackupWorker::recursiveList(QDir &sDir, QFileInfoList &filesList)
{
    QFileInfoList datas = sDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs
                                             ,QDir::Name | QDir::DirsFirst);

    for(const auto & info : datas)
    {
        filesList.append(info);
        if(info.isDir() && sDir.cd(info.fileName()))
        {
            recursiveList(sDir,filesList);
            sDir.cdUp();
        }
    }
}

void BackupWorker::compareDirs(QDir &sdir, QDir &ddir, QFileInfoList& fileList)
{
    for(const auto & c : sdir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs
                                            ,QDir::Name | QDir::DirsFirst))
    {
        bool foundFile = false;

        for( const auto & b : ddir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs
                                                ,QDir::Name | QDir::DirsFirst) )
        {
            if(c.fileName() == b.fileName())
            {
                if(c.isDir() || c.lastModified() <= b.lastModified())
                {
                    foundFile = true;
                }
                break;
            }
        }
        if(!foundFile)
        {
            fileList.append(c);
        }
        if(c.isFile()) continue;
        if(foundFile)
        {
            sdir.cd(c.fileName());
            ddir.cd(c.fileName());
            compareDirs(sdir,ddir,fileList);
            sdir.cdUp();
            ddir.cdUp();

        }else
        {
            sdir.cd(c.fileName());
            recursiveList(sdir,fileList);
            sdir.cdUp();
        }
    }
}

bool BackupWorker::StorageBackup(QDir &s,QDir& b)
{
    qint64 sizeCopyDir = getTotalSizeMBDirsCopy(s);
    QStorageInfo currStorage(b.rootPath());

    if (!currStorage.isReady() || !currStorage.isValid()) {
        emit logMessage("Диск недоступен!");
        emit unlockBTN();
        return false;
    }

    qint64 freeSizeMB = currStorage.bytesAvailable() / (1024 * 1024 );

    emit logMessage("Размер копируемых данных: " + QString::number(sizeCopyDir) + " MB");
    emit logMessage("Свободно на диске назначения: " + QString::number(freeSizeMB) + " MB");

    if(freeSizeMB <= sizeCopyDir )
    {
       emit logMessage("Недостаточно Места на диске!");
        emit unlockBTN();
        return false;
    }

    emit logMessage("Места достаточно. Можно копировать.");
    return true;

}

qint64 BackupWorker::getTotalSizeMBDirsCopy(QDir &s)
{
    qint64 totalSize = 0;

    QFileInfoList files = s.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for(const auto& c : files)
    {
        if (c.isDir()) {
            QDir subDir(c.absoluteFilePath());
            totalSize += getTotalSizeMBDirsCopy(subDir);
        } else
        {
            totalSize += c.size();
        }
    }

    return totalSize / (1024* 1024 ); // MB
}




void BackUp::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
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

bool BackupWorker::runBackUpNew(QFileInfoList files, QString dPath)
{
    bool success = true;

    for (const auto& dataFile : files)
    {
        if (dataFile.isFile())
        {
            QString destFilePath = dPath + QDir::separator() + dataFile.fileName();

            if(QFile(destFilePath).exists())
            {
                if(dataFile.lastModified() > QFileInfo(destFilePath).lastModified()){
                    QFile(destFilePath).remove();
                }
            }

            if (!QFile::copy(dataFile.absoluteFilePath(), destFilePath)) {
                logger->write("Ошибка копирования файла:" + dataFile.absoluteFilePath().toStdString()
                    + " в " + destFilePath.toStdString());
                success = false;
            } else {
                logger->write("Успешно скопирован файл:" + dataFile.absoluteFilePath().toStdString()
                    + " в " + destFilePath.toStdString());
            }
        }
        else if(dataFile.isDir())
        {
            QString destDir = dPath + QDir::separator() + dataFile.fileName();
            QString sourceDir = dataFile.absoluteFilePath();
            recursiveCopy(sourceDir,destDir);
        }
        else {

            logger->write("Пропуск не файлового объекта: " + dataFile.absoluteFilePath().toStdString());
        }
    }

    return success;
}



bool BackupWorker::recursiveCopy(QString& sPath, QString& dPath) {

    QDir sourceDir(sPath);
    QDir destDir(dPath);
    qDebug() << sPath << " " << dPath << " " << sourceDir.absolutePath() << " " << destDir.absolutePath();
    bool success = true;

    if (!destDir.exists()) {
        if (!destDir.mkpath(".")) {
            logger->write("Не удалось создать директорию:" + dPath.toStdString());
            return false;
        }
    }

    for (const auto& entryInfo : sourceDir.entryInfoList(QDir::Filters(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::DirsFirst))) {

        QString sourceEntryPath = sourceDir.absolutePath() + QDir::separator() + entryInfo.fileName();
        QString destEntryPath = destDir.absolutePath() + QDir::separator() + entryInfo.fileName();
        qDebug() << sourceEntryPath << " " << destEntryPath;

        if (entryInfo.isFile()) {
            if (QFile(destEntryPath).exists()) {
                if(entryInfo.lastModified() > QFileInfo(destEntryPath).lastModified())
                {
                    QFile(destEntryPath).remove();
                }
            }

            if (!QFile::copy(sourceEntryPath, destEntryPath)) {
                logger->write("Ошибка копирования файла:" + sourceEntryPath.toStdString() + " в " + destEntryPath.toStdString());
                success = false;
            } else {
                logger->write("Успешно скопирован файл:" + sourceEntryPath.toStdString() + " в " + destEntryPath.toStdString());
            }
        } else if (entryInfo.isDir()) {
            success = recursiveCopy(sourceEntryPath, destEntryPath);
        }
    }

    return success;
}
