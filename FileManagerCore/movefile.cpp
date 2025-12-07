#include "movefile.h"
#include "ui_movefile.h"
#include<QDesktopServices>
#include<QItemSelectionModel>
#include<QDir>
#include<QFile>
#include<QMessageBox>
#include"filemanagerdialog.h"


MoveFile::MoveFile(filemanagerdialog* FMD, QWidget *parent)
    : QWidget(parent)
    , dlg_(FMD)
    , ui(new Ui::MoveFile)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    formBuilder= new BuilderForm(this);
    worker = new MoveFileWorker;
    threadWorker = new QThread(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries);
    model->setRootPath("");


    QItemSelectionModel* selectModel = new QItemSelectionModel(model, this);

    ui->listView->setModel(model);
    ui->listView_2->setModel(model);
    ui->listView->setSelectionModel(selectModel);

    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);


    connect(ui->listView_2, &QListView::doubleClicked, this, &MoveFile::on_listView_doubleClicked);
    connect(ui->listView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MoveFile::onSelectionChanged);

    connect(ui->btnMoveSelect,&QPushButton::clicked,this,[this](){
        if(files_.size() != 0)
        {
            auto confrim = formBuilder->confrimSomething();
            if(confrim == QMessageBox::Yes)
            {
                QModelIndex index = ui->listView_2->currentIndex();
                QString b = model->filePath(index);
                emit startOperation(files_,b);
            }else
            {
                QMessageBox::information(this,"Перемещение","Отменено");
                logger->write("Перемещение отменено");
            }
        }
    });


    connect(ui->btnMoveAll, &QPushButton::clicked, this, [this](){

        auto confrim = formBuilder->confrimSomething();

        if(confrim == QMessageBox::Yes) {
            QModelIndex sourceIndex = ui->listView->rootIndex();
            QString sourceDir = model->filePath(sourceIndex);

            QModelIndex targetIndex = ui->listView_2->rootIndex();
            QString targetDir = model->filePath(targetIndex);

            emit startOperationAll(sourceDir, targetDir);

        } else {
            QMessageBox::information(this,"Перемещение","Отменено");
            logger->write("Перемещение отменено");
        }
    });

    connect(this, &MoveFile::startOperation, this, [this](QFileInfoList list, QString s){
        QMetaObject::invokeMethod(worker, "runMoveFile", Qt::QueuedConnection,
                                  Q_ARG(QFileInfoList, list),
                                  Q_ARG(QString, s));
    });

    connect(this, &MoveFile::startOperationAll, this, [this](QString s, QString b){
        QMetaObject::invokeMethod(worker, "runMoveFileAll", Qt::QueuedConnection,
                                  Q_ARG(QString, s),
                                  Q_ARG(QString, b));
    });

    connect(worker,&MoveFileWorker::SuccesOperation,this,[this](bool succes){

        if(succes == true)
        {
            QMessageBox::information(this,"Перемещение","Успешно");
            logger->write("Перемещение успешно");
        }
        else
        {

            QModelIndex index = ui->listView_2->currentIndex();
            QString b = model->filePath(index);
            QMessageBox::warning(this,"Перемещение","Перемещение не доступно");
            logger->write("Перемещение из директорий " + files_.at(0).absolutePath().toStdString()
                          + " В директорию " + b.toStdString() + " Недоступно так как это идентичные директории");
        }
    });



    connect(worker,&MoveFileWorker::SuccesOperationAll,this,[this](bool succes){

        if(succes == true)
        {
            QMessageBox::information(this,"Перемещение","Успешно");
            logger->write("Перемещение успешно");
        }
        else
        {
            QMessageBox::warning(this,"Перемещение","Перемещение не доступно");
            logger->write("Ошибка Перемещения");
        }
    });
    connect(ui->btnQuit,&QPushButton::clicked,this,&MoveFile::BackMenu);


    worker->moveToThread(threadWorker);
    threadWorker->start();
}

MoveFile::~MoveFile()
{
    threadWorker->quit();
    threadWorker->wait();
    worker->deleteLater();
    delete ui;
}

void MoveFile::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList selectedIndexes = ui->listView->selectionModel()->selectedIndexes();
    files_.clear();

    QString path;

    for(const auto& index : selectedIndexes)
    {
        if(index.isValid() && index.column() == 0)
        {
            path = model->filePath(index);
            QFileInfo info(path);
            sourcePath = info.absolutePath();
            qDebug()<< "source " << sourcePath;
            if(info.fileName() != ".." && info.fileName() != ".")
            {
                files_.append(info);
            }
        }
    }

    QModelIndexList deselectedIndexes = deselected.indexes();
    for(const auto& index : deselectedIndexes)
    {
        if(index.isValid() && index.column() == 0)
        {
            path = model->filePath(index);
            QFileInfo info(path);
            if(info.fileName() != ".." && info.fileName() != ".")
            {
                files_.removeOne(info);
            }
        }
    }

    for(const auto& file : files_)
    {
        qDebug() <<"================"<< "File:" << file.absoluteFilePath();
        setWindowTitle(file.absoluteFilePath());

    }
}

void MoveFile::on_listView_doubleClicked(const QModelIndex &index)
{
    QListView* listView = qobject_cast<QListView*>(sender());
    if (!listView) return;

    QString path = model->filePath(index);
    QFileInfo info(path);


    if(info.fileName() == "..")
    {
        QDir temp = info.filePath();
        listView->setRootIndex(model->index(temp.absolutePath()));
    }
    else if(info.fileName() == ".")
    {
        listView->setRootIndex(model->index(""));
    }
    else if(info.isDir())
    {
        listView->setRootIndex(index);
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
    }

    listView->clearSelection();
}

void MoveFile::BackMenu()
{
    this->close();
    dlg_->show();
}


bool MoveFileWorker::runMoveFile(QFileInfoList listFiles, QString bDir)
{
    QDir b(bDir);

    if(!b.exists())
    {
        b.mkpath(bDir);
    }

    if(listFiles.at(0).absolutePath() == b.absolutePath())
    {
        emit SuccesOperation(false);
        return false;

    }

    for(const auto& c : listFiles)
    {
        QString sourcePath = c.absoluteFilePath();
        QString fileName  = c.fileName();
        QString destPath = bDir + QDir::separator() + fileName;

        if(QFile::exists(destPath))
        {
            QFile(destPath).remove();
        }

        if(c.isDir())
        {
            if(!moveDirectoryRecursive(sourcePath, destPath)) {
            } else {
                QDir(sourcePath).removeRecursively();
            }
        }
        else
        {
            if (!QFile::copy(sourcePath, destPath)) {
            } else {
                QFile(sourcePath).remove();
            }
        }
    }
    emit SuccesOperation(true);
    return true;
}

bool MoveFileWorker::moveDirectoryRecursive(const QString &sourceDir, const QString &destDir)
{

    QDir s(sourceDir);
    QDir d(destDir);

    if (!d.exists()) {
        d.mkpath(".");
    }

    QStringList files = s.entryList(QDir::Files);
    for(const auto& c : files)
    {
        QString srcFilePath = sourceDir + QDir::separator() + c;
        QString destFilePath = destDir + QDir::separator() + c;

        if(QFile::exists(destFilePath))
        {
            QFile::remove(destFilePath);
        }
        if(!QFile::copy(srcFilePath,destFilePath))
        {
            return false;
        }

    }

    QStringList dirs = s.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(const auto& c : dirs)
    {
        QString srcDirPath = sourceDir + QDir::separator() + c;
        QString destDirPath = destDir + QDir::separator() + c;

        if(QDir(destDirPath).exists())
        {
             QDir(destDirPath).removeRecursively();
        }
        if(!moveDirectoryRecursive(srcDirPath,destDirPath))
        {
            return false;
        }
    }

    return true;
}

//==========ALL==========
bool MoveFileWorker::runMoveFileAll(QString sPath, QString bPath)
{
    QDir sourceDir(sPath);
    QDir targetDir(bPath);

    if(!sourceDir.exists()) {
        logger->write("Ошибка исходная директория пропала" + sPath.toStdString());
        return false;
    }

    if (!targetDir.exists()) {
        targetDir.mkpath(".");
    }


    if(sourceDir.absolutePath() == targetDir.absolutePath()) {
        emit SuccesOperationAll(false);
        return false;
    }

    bool success = moveDirectoryRecursive(sPath, bPath);

    emit SuccesOperationAll(success);
    return success;
}
