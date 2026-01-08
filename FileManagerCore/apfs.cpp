#include "apfs.h"
#include "ui_apfs.h"
#include"filemanagerdialog.h"
#include<QMessageBox>
#include<QStack>
APFS::APFS(filemanagerdialog* fmd,QWidget *parent)
    : QWidget(parent)
    ,fmd_(fmd)
    , ui(new Ui::APFS)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    model->setRootPath(QDir::rootPath());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ui->tableView, 1);
    mainLayout->addWidget(ui->textEdit, 1);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(ui->btnStart);
    buttonLayout->addWidget(ui->btnQuit);
    buttonLayout->addWidget(ui->progressBar,1);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);



    worker = new APFSworker;
    thread = new QThread();

    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(true);

    ui->tableView->setModel(model);

    connect(ui->btnStart, &QPushButton::clicked, this, &APFS::onCountFilesClicked);

    connect(ui->tableView,&QTableView::clicked,this,[&](const QModelIndex& CurrIndex){
        index = CurrIndex;
    });

    connect(this,&APFS::startOperation,worker,[this](ModeView mode, const QString& path){
        ui->btnStart->setEnabled(false);
        worker->viewInfoObject(mode,path);
    });

    connect(worker,&APFSworker::finished,this,[this]()
    {
        ui->btnStart->setEnabled(true);
    });

    connect(worker,&APFSworker::requestInfoTextEdit,this,[this](const QString& msg){
        ui->textEdit->setText(msg);
    });

    connect(worker,&APFSworker::progressValuer,ui->progressBar,&QProgressBar::setValue);

    connect(ui->btnQuit,&QPushButton::clicked,this,&APFS::Back);



    worker->moveToThread(thread);
    thread->start();
}


APFS::~APFS()
{
    thread->quit();
    thread->wait(3000);
    worker->deleteLater();
    delete ui;
}

bool APFSworker::viewInfoObject(ModeView mode, const QString &path)
{
    if(mode == ModeView::Dir){
        FileStats Objects = recursiveDirTraversal(path);
        qint64 size = getSizeTravelDirectiry(path);
        QString data = getFullPath(path);
            QString message = "Директорий: "+QString::number(Objects.dirs) + ":\n " + "Файлов: " + QString::number(Objects.files) +
                          "\n путь: " + path + " \n общий размер в MB: " + QString::number(size / (1024* 1024)) + "\n обoий размер в ГБ: " + QString::number(size / (std::pow(1024,3)))
            + data;


            emit requestInfoTextEdit(message);

        return true;
    }else if(mode == ModeView::File)
    {
        qint64 size = getSizeTravelDirectiry(path);
        QString data = getFullPath(path);
        QString message  = data;


        emit requestInfoTextEdit(message);
        return true;
    }

    return false;

}

qint64 APFSworker::getSizeTravelDirectiry(const QString& path)
{
    qint64 totalSize = 0;
    QStack<QDir> stack;
    stack.push(QDir(path));

    while (!stack.isEmpty())
    {
        QDir dir = stack.pop();

        QFileInfoList infList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot,
                                                  QDir::Name | QDir::DirsFirst);

        for (const QFileInfo& info : infList)
        {
            if (info.isDir() && !info.isSymLink())
            {
                stack.push(QDir(info.absoluteFilePath()));
            }
            else if (info.isFile())
            {
                totalSize += info.size();

            }
        }
    }

     return totalSize;
}

QString APFSworker::getFullPath(const QString &path)
{

    QFileInfo info(path);

    QString result = QString("\nАбсолютный Путь: %1"
                             "\nИмя: %2"
                             "\nОтносительный Путь: %3"
                             "\nБазовое имя: %4"
                             "\nДата создания: %5"
                             "\nBundle Имя: %6")
                         .arg(info.absolutePath())
                         .arg(info.fileName())
                         .arg(info.filePath())
                         .arg(info.baseName())
                         .arg(info.birthTime().toString("yyyy-MM-dd HH:mm:ss"))
                         .arg(info.bundleName());

    return result;

}

FileStats APFSworker::recursiveDirTraversal(const QString& path)
{
    FileStats stats = {0, 0};
    int counter = 0;

    QStack<QDir> stack;
    QSet<QString> visited;
    stack.push(QDir(path));
    visited.insert(QDir(path).absolutePath());


    qint64 totalFiles = getRecursiveMKpath(path); // 100

    while (!stack.isEmpty())
    {
        QDir dir = stack.pop();

        QFileInfoList entries = dir.entryInfoList(
            QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot,
            QDir::Name | QDir::DirsFirst
        );

        for (const QFileInfo& info : entries)
        {
            counter++;
            int progress = static_cast<int>((counter * 100.0) / totalFiles);
            emit progressValuer(progress);


            if (info.isDir() && !info.isSymLink())
            {
                QString absPath = info.absoluteFilePath();
                if (!visited.contains(absPath))
                {
                    visited.insert(absPath);
                    stack.push(QDir(absPath));
                    stats.dirs++;
                }
            }
            else if (info.isFile())
            {
                stats.files++;
            }


        }


    }

    emit finished();

    return stats;
}

qint64 APFSworker::getRecursiveMKpath(const QString &path)
{
    QStack<QDir> stack;
    QSet<QString> visited;

    stack.push(QDir(path));
    visited.insert(QDir(path).absolutePath());

    qint64 fileCount = 0;


    qDebug() << "path: " << path;
    while(!stack.isEmpty()){

        QDir dir = stack.pop();

        QFileInfoList entries = dir.entryInfoList(
            QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot,
            QDir::Name | QDir::DirsFirst
        );

        for(const auto& info : entries)
        {
            if(info.isDir() && !info.isSymLink())
            {
                QString absPath = info.absoluteFilePath();
                if (!visited.contains(absPath))
                {
                    visited.insert(absPath);
                    stack.push(QDir(absPath));
                }
            }
            else
            {
                fileCount++;
            }
        }


    }

    qDebug() << "file-> " << QString::number(fileCount);
    return fileCount;
}



void APFS::onCountFilesClicked()
{

    QMessageBox::StandardButton confrim = QMessageBox::question(
        this,
        "Подтверждение",
        "Вы уверены что хотите выполнить просмотри информации?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (confrim == QMessageBox::Yes) {
        QModelIndex currentRoot = index;
        QString currentPath = model->filePath(currentRoot);

        QFileInfo dirInfo(currentPath);
        if(dirInfo.isDir()) {
            emit startOperation(ModeView::Dir, currentPath);
        }
        else
        {
            emit startOperation(ModeView::File, currentPath);
        }
    } else {
        QMessageBox::information(this, "Отмена", "Действие отменено");
        ui->btnStart->setEnabled(true);
    }

}






void APFS::on_tableView_doubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = model->fileInfo(index);

    if(fileInfo.fileName() == ".")
    {
        ui->tableView->setRootIndex(model->setRootPath(""));
    }else if(fileInfo.fileName() == "..")
    {
        QDir dir = fileInfo.path();
        dir.cdUp();
        qDebug() << dir.absolutePath()<< " \n";
        ui->tableView->setRootIndex(model->setRootPath(dir.absolutePath()));
    }
    else if(fileInfo.isDir())
    {
        ui->tableView->setRootIndex(index);
    }
}

void APFS::Back()
{
    this->close();
    fmd_->show();
}

