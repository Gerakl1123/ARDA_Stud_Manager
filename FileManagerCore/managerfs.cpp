#include "managerfs.h"
#include "ui_managerfs.h"
#include"filemanagerdialog.h"
#include"memory"
#include<QInputDialog>
#include<QMessageBox>
#include"createfiledialog.h"
#include<QItemSelectionModel>
#include<QShortcut>
#include<QDesktopServices>
#include<QItemDelegate>
#include<QMenu>
#include<QMenuBar>
#include<QWidgetAction>
#include<QCheckBox>
#include<QSettings>
#include"../JsonKeys.h"

ManagerFS::ManagerFS(filemanagerdialog* dlg, QWidget *parent)
    : QWidget(parent)
    , dlg_(dlg)
    , ui(new Ui::ManagerFS)
    , buildForm_(new BuilderForm(this))
    , SortModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    model = new QFileSystemModel(this);
    createFile = new CreateFileDialog(this);
    defaultExtesions = new QCheckBox(this);
    defaultExtesions->setText("Применить свое расширение");

    QSettings settings(SerelizationData::ORG_NAME,"FileManager");
    defaultExtesions->setCheckState(settings.value("Extesions").toInt());

    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* menu = new QMenu("Дополнительно", menuBar);
    QWidgetAction* actionBox = new QWidgetAction(menu);


    actionBox->setDefaultWidget(defaultExtesions);
    menu->addAction(actionBox);
    menuBar->addMenu(menu);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model->setFilter(QDir::AllEntries);
    model->setRootPath("");
    SortModel->setSourceModel(model);
    SortModel->setFilterKeyColumn(-1);
    SortModel->setFilterRole(Qt::DisplayRole);
    SortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    QItemSelectionModel* selection = new QItemSelectionModel(SortModel, this);

    QShortcut* deleteShorctCut = new QShortcut(QKeySequence(Qt::Key_Delete),this);
    worker = new ManagerWorker;
    threadWorker = new QThread(this);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setModel(SortModel);
    ui->tableView->setSelectionModel(selection);
    ui->tableView->verticalHeader()->setVisible(false);

    connect(ui->btnCreate,&QPushButton::clicked,this,&ManagerFS::onCreateDirClicked);
    connect(ui->btnCreateFile,&QPushButton::clicked,this,&ManagerFS::onCreateFileClicked);

    connect(defaultExtesions,&QCheckBox::checkStateChanged,this,[this](int state){
        QSettings settings(SerelizationData::ORG_NAME,"FileManager");
        settings.setValue("Extesions",state);

    });
    connect(ui->btnDelete,&QPushButton::clicked,[this](){

        auto confrim =  buildForm_->confrimSomething();

        if(confrim == QMessageBox::Yes)
        {
            QMetaObject::invokeMethod(worker,"RemoveSelecteFilesObjects",Qt::QueuedConnection,Q_ARG(QFileInfoList,files_));

        }
        else
        {
            QMessageBox::information(this,"Отмена","Действие отменено");
        }


    });

    connect(this,&ManagerFS::requestCreateDir,worker,[=](const QString& path,const QString& file){
        worker->CreateDir(path,file);
    });
    connect(this,&ManagerFS::requestCreateFile,worker,[=](const QString& path,const QString& file){
        worker->CreateFile(path,file);
    });
    connect(worker,&ManagerWorker::succesMessageCreateDir,this,&ManagerFS::onDirectoryOperationResult);

    connect(worker,&ManagerWorker::succesMessageCreateFile,this,&ManagerFS::onFilesOperationResult);
    connect(ui->btnQuit,&QPushButton::clicked,this,&ManagerFS::Back);


    connect(deleteShorctCut,&QShortcut::activated,[this](){
        auto confrim =  buildForm_->confrimSomething();

        if(confrim == QMessageBox::Yes)
        {
            QMetaObject::invokeMethod(worker,"RemoveSelecteFilesObjects",Qt::QueuedConnection,Q_ARG(QFileInfoList,files_));

        }
        else
        {
            QMessageBox::information(this,"Отмена","Действие отменено");
        }

    });

    connect(ui->tableView->selectionModel(),&QItemSelectionModel::selectionChanged,this,&ManagerFS::onSelectionChanged);

    connect(ui->lineEditFind, &QLineEdit::textChanged, this, [this](const QString& text){
        QModelIndex currentRoot = ui->tableView->rootIndex();

        SortModel->setFilterFixedString("");

        for (int row = 0; row < SortModel->rowCount(currentRoot); ++row) {
            QModelIndex index = SortModel->index(row, 0, currentRoot);
            QString fileName = SortModel->data(index).toString();

            bool shouldShow = text.isEmpty() || fileName.contains(text, Qt::CaseInsensitive);
            ui->tableView->setRowHidden(row, !shouldShow);
        }
    });
    connect(this,&ManagerFS::getFiles,worker,&ManagerWorker::setFiles,Qt::QueuedConnection);

    connect(ui->btnRename,&QPushButton::clicked,this,[this](){

        if(!files_.isEmpty())
        {
            QFileInfo info = files_.at(0);
            if(info.isDir())
            {
                QString name = QInputDialog::getText(this,
                    "Переименование",
                    "Введите новое имя:",
                    QLineEdit::Normal,
                    info.fileName()
                );

                emit requestRenameDir(info.absoluteFilePath(),info.absolutePath()+QDir::separator()+name);
            }
            else if(info.isFile())
            {

                QString name = QInputDialog::getText(this,
                 "Переименование",
                 "Введите новое имя:",
                 QLineEdit::Normal,
                 info.fileName()
                );

                if(!defaultExtesions->isChecked())
                {
                    emit requestRenameFile(info.absolutePath() + QDir::separator() + name + "." + info.completeSuffix());
                }else
                {
                    emit requestRenameFile(info.absolutePath() + QDir::separator() + name);
                }
            }
        }

    });

    connect(this,&ManagerFS::requestRenameDir,this,[this](const QString& old,const QString& name){

        QMetaObject::invokeMethod(worker,"renameDir",Qt::QueuedConnection,Q_ARG(QString,old),Q_ARG(QString,name));

    });

    connect(this,&ManagerFS::requestRenameFile,this,[this](const QString& name){

        QMetaObject::invokeMethod(worker,"renameFile",Qt::QueuedConnection,Q_ARG(QString,name));

    });

    connect(ui->lineEdiFindPath,&QLineEdit::textChanged,this,[this](const QString& path){
        QModelIndex index = SortModel->mapFromSource(model->setRootPath(path));
        ui->tableView->setRootIndex(index);
    });


    worker->moveToThread(threadWorker);
    threadWorker->start();
}
ManagerWorker::ManagerWorker(QObject *parent)
    : QObject(parent)
{

}


ManagerFS::~ManagerFS()
{

    threadWorker->quit();
    threadWorker->wait();
    worker->deleteLater();
    delete ui;
}


void ManagerFS::onDirectoryOperationResult(OperationState state, const QString& msg)
{
    if(state == OperationState::Success)
    {
        QMessageBox::information(this,"Успешно",msg);
    }else if(state == OperationState::Exists)
    {
        QMessageBox::warning(this,"Внимание",msg);
    }else if(state == OperationState::Error)
    {
        QMessageBox::critical(this,"Ошибка",msg);
    }

}

void ManagerFS::onFilesOperationResult(OperationState state, const QString &msg)
{
    if(state == OperationState::Success)
    {
        QMessageBox::information(this,"Успешно",msg);
    }else if(state == OperationState::Exists)
    {
        QMessageBox::warning(this,"Внимание",msg);
    }else if(state == OperationState::Error)
    {
        QMessageBox::critical(this,"Ошибка",msg);
    }
}

void ManagerFS::Back()
{
    this->close();
    dlg_->show();
}


void ManagerFS::onCreateDirClicked()
{

    QModelIndex index = SortModel->mapToSource(ui->tableView->rootIndex());
    QString currentPath = model->filePath(index);

    bool ok;
    QString text = QInputDialog::getText(
        nullptr,
        "Введите имя папки",
        "Имя:",
        QLineEdit::Normal,
        QString(),
        &ok
        );

    emit requestCreateDir(currentPath,text);

}

void ManagerFS::onCreateFileClicked()
{
    auto dlg = std::make_unique<CreateFileDialog>();

    QModelIndex index = SortModel->mapToSource(ui->tableView->rootIndex());
    QString currentPath = model->filePath(index);

    if(dlg->exec() == QDialog::Accepted)
    {
        emit requestCreateFile(currentPath,dlg->getFileName());
    }
}
// == WORKER LOGIC ==
bool ManagerWorker::CreateDir(const QString &path, const QString &fileName)
{

    logger->write(("Ввод: " + fileName).toStdString());

    QDir currentDir(path.isEmpty() ? QDir::currentPath() : path);
    logger->write(("Текущий путь: " + currentDir.absolutePath()).toStdString());

    QString newDirPath = currentDir.filePath(fileName);

    if (QDir(newDirPath).exists()) {
        emit succesMessageCreateDir(OperationState::Exists,"Папка уже существует:\n" + newDirPath);
        logger->write(("Папка уже существует: " + newDirPath).toStdString());
        return false;
    }

    if (currentDir.mkdir(fileName)) {
        logger->write(("Создана директория: " + newDirPath).toStdString());
        emit succesMessageCreateDir(OperationState::Success,"Папка создана успешно:\n" + newDirPath);
        return true;
    } else {
        logger->write(("Не удалось создать директорию: " + newDirPath).toStdString());
        emit succesMessageCreateDir(OperationState::Error,"Не удалось создать папку:\n" + newDirPath);
        return false;
    }

}

bool ManagerWorker::CreateFile(const QString& path, const QString& fileName)
{

    nameFile = fileName;

    logger->write(("Ввод: " + nameFile ).toStdString());

    QDir FullPath(path);

    QFile newFile(FullPath.filePath(nameFile));

    if(newFile.exists())
    {
        emit succesMessageCreateFile(OperationState::Exists,"Файл уже существует по путю: " + FullPath.absolutePath());
        logger->write("Файл уже существует по путю" + FullPath.absolutePath().toStdString());
        return false;
    }

    if (newFile.open(QIODevice::WriteOnly)) {
        newFile.close();
        emit succesMessageCreateFile(OperationState::Success,"Файл создан по путю: " + FullPath.absolutePath());
        logger->write("Файл: " + nameFile.toStdString() + " " + "создан по путю" + FullPath.absolutePath().toStdString());
        return true;
    } else {
        emit succesMessageCreateFile(OperationState::Error,"Не удалось открыть файл по путю: " + FullPath.absolutePath());
        logger->write("Не удалось открыть файл по путю: " + FullPath.absolutePath().toStdString());
        return false;
    }

}
bool ManagerWorker::renameFile(const QString &newName)
{
    if (newName.isEmpty()) {
        return false;
    }

    QFileInfo oldInfo = files.at(0);

    QFile file(oldInfo.absoluteFilePath());

    if(oldInfo.absoluteFilePath() == newName)
    {
        return false;
    }

    if (QFile::exists(newName)) {
        return false;
    }

    if (file.rename(newName)) {
        logger->write("Файл успешно переименован: " + oldInfo.fileName().toStdString() + " -> " + newName.toStdString());
        return true;
    } else {
        logger->write("Ошибка переименования:" + file.errorString().toStdString());
        return false;
    }
}

bool ManagerWorker::renameDir(const QString &oldName, const QString &newName)
{
    if (oldName.isEmpty() || newName.isEmpty()) {
        return false;
    }

    if (oldName == newName) {
        return true;
    }

    QDir dir;

    if (!QDir(oldName).exists()) {
        return false;
    }

    if (QDir(newName).exists()) {
        return false;
    }

    if (dir.rename(oldName, newName)) {
        logger->write("Папка успешно переименована: " + oldName.toStdString() + " -> " + newName.toStdString());
        return true;
    } else {
        logger->write("Ошибка переименования:");
        return false;
    }
}

void ManagerWorker::setFiles(QFileInfoList list)
{
    files = list;
}

bool ManagerWorker::removeDir(const QString &path)
{
    QDir remDir(path);

    return remDir.exists() ? remDir.removeRecursively() : false;
}

bool ManagerWorker::removeFile(const QString &path)
{
    QFile remFile(path);
    if(!remFile.exists()) return false;

    return remFile.exists() ? remFile.remove() : false;
}







void ManagerFS::on_tableView_doubleClicked(const QModelIndex &index)
{


    QModelIndex fileInfoIndex = SortModel->mapToSource(index);
    QString fileInfoPath = model->filePath(fileInfoIndex);
    QFileInfo fileInfo(fileInfoPath);

    if(fileInfo.fileName() == ".")
    {
        ui->tableView->setRootIndex(SortModel->mapFromSource(model->setRootPath("")));

    }else if(fileInfo.fileName() == "..")
    {
        QDir tempDir(fileInfo.path());
        tempDir.cdUp();
        ui->tableView->setRootIndex(SortModel->mapFromSource(model->setRootPath(tempDir.absolutePath())));

    }else if(fileInfo.isDir())
    {
        QModelIndex newDir = model->index(fileInfoPath);
        if(newDir.isValid())
        {
            ui->tableView->setRootIndex(SortModel->mapFromSource(newDir));
              ui->lineEditFind->clear();
        }
    }  else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfoPath));
    }
}

void ManagerFS::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{


    QModelIndexList indexs = selected.indexes();
    QString filePath;

    for(const QModelIndex& index : indexs)
    {
        filePath = "";
        if(index.column() == 0) {
            QModelIndex sourceIndex = SortModel->mapToSource(index);
            filePath = model->filePath(sourceIndex);
            QFileInfo fileInfo(filePath);
            if(fileInfo.fileName() != ".." && fileInfo.fileName() != ".")
            {
                files_.append(fileInfo);

            }
        }
    }

    QModelIndexList deselectedIndexes = deselected.indexes();

    for(const QModelIndex& delIndex : deselectedIndexes)
    {
        if(delIndex.column() == 0)
        {
            QModelIndex sourceIndex = SortModel->mapToSource(delIndex);
            QString Delinfo = model->filePath(sourceIndex);
            QFileInfo info(Delinfo);
            if(info.fileName() != ".." && info.fileName() != ".")
            {
                files_.removeOne(info);
            }
        }
    }

    emit getFiles(files_);

}





void ManagerWorker::RemoveSelecteFilesObjects(const QFileInfoList &files)
{

    qDebug() << "=================";
    for(const auto &c : files)
    {
        qDebug() << c.fileName();
    }

    for(const QFileInfo& info : files)
    {
        if (!info.exists()) {
            logger->write("Файл/директорий не существует: " + info.absoluteFilePath().toStdString());
            continue;
        }

        if (info.isDir() && !info.isSymLink()) {
            if (!removeDir(info.absoluteFilePath())) {
                logger->write( "Ошибка при удалении директории: " +  info.absoluteFilePath().toStdString());
            }
        } else if (info.isFile() && !info.isSymLink()) {
            if (!removeFile(info.absoluteFilePath())) {
                logger->write("Ошибка при удалении файла:" + info.absoluteFilePath().toStdString());
            }
        } else {
            logger->write("Пропущена символьческая ссылка:" + info.absoluteFilePath().toStdString());
        }
    }

}

