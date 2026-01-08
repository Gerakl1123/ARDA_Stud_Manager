#include "ardaeditorform.h"
#include "ui_ardaeditorform.h"
#include"Validator.h"
#include <QTreeWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMenuBar>
#include <QAction>
#include<QCheckBox>
#include<QWidgetAction>
#include"LogicOperation.h"
#include"JsonKeys.h"
#include<QInputDialog>
#include"mainwindow.h"
#include<QtConcurrent/QtConcurrent>

ArdaEditorForm::ArdaEditorForm(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , mainWindow(main)
    , ui(new Ui::ArdaEditorForm)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    setAttribute(Qt::WA_DeleteOnClose);
    bold = new QCheckBox("Жирный", this);
    italic = new QCheckBox("Курсив", this);
    menuBar = new QMenuBar(this);
    More = new QMenu("Помощник", menuBar);
    printerAction = new QAction("Распечатать",More);
    openAction = new QAction("Открыть Файл", More);
    saveAction = new QAction("Сохранить", More);
    saveAsAction = new QAction("Сохранить как", More);
    checkBoxAction = new QWidgetAction(More);
    checkBoxSerAction = new QWidgetAction(More);
    exitAction = new QAction("Выход", More);

    checkBoxAction->setDefaultWidget(bold);
    checkBoxSerAction->setDefaultWidget(italic);
    More->addAction(openAction);
    More->addAction(saveAction);
    More->addAction(saveAsAction);
    More->addSeparator();
    More->addAction(exitAction);
    More->addAction(checkBoxAction);
    More->addAction(checkBoxSerAction);
    More->addAction(printerAction);
    menuBar->addMenu(More);


    QTimer::singleShot(100,this,&ArdaEditorForm::loadSettings);


}

ArdaEditorForm::~ArdaEditorForm()
{
    delete ui;
}



void ArdaEditorForm::saveDocument()
{
   QString path = path_;

   QString data = ui->textEdit->toPlainText();
   QByteArray bArr = data.toUtf8();


        QFile file(path);

        if(file.exists())
        {
         openFile(file,ModeValidator::DeleteWrite);
         file.write(bArr);
         QMessageBox::information(this,"Сохранение: ", "Путь файла: " + path);
         file.close();
         return;
        }

    openFile(file,ModeValidator::WriteFile);
    file.write(bArr);
    QMessageBox::information(this,"Сохранение: ", "Путь файла: " + path);
    file.close();


}

void ArdaEditorForm::openDocument()
{
    QString path = fileManager_->chooseFileAbsolute();;


    QFile file(path);
    QFileInfo inf(path);
    path_ = inf.absoluteFilePath();
    if(!file.exists()) return;


    setWindowTitle(inf.fileName());


    openFile(file,ModeValidator::ReadFile);
    QByteArray bArr = file.readAll();
    QString text = QString::fromUtf8(bArr);
    ui->textEdit->setText(text);
}

void ArdaEditorForm::PrinterDocumentNative()
{

    QPrinter printer;
    printer.setOutputFileName(fileManager_->saveFilePDF());
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);


    QTextDocument doc;
    doc.setPlainText(ui->textEdit->toPlainText());
    doc.print(&printer);

}

void ArdaEditorForm::SaveAsDocument()
{
    QString path = fileManager_->saveAbsoluteFile();

    QFile file(path);


    openFile(file,ModeValidator::WriteFile);
    QByteArray bArr(ui->textEdit->toPlainText().toUtf8());

    file.write(bArr);
    file.close();


}

void ArdaEditorForm::FindText(const QString &findValue)
{
    QTextDocument* document = ui->textEdit->document();
    QTextCursor cursor = ui->textEdit->textCursor();

    cursor = document->find(findValue,cursor);

    if(!cursor.isNull())
    {
        ui->textEdit->setTextCursor(cursor);
        ui->textEdit->ensureCursorVisible();
    }else {
        cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        ui->textEdit->setTextCursor(cursor);

        cursor = document->find(findValue, cursor);
        if (!cursor.isNull()) {
           ui-> textEdit->setTextCursor(cursor);
           ui-> textEdit->ensureCursorVisible();
        }
    }
}

void ArdaEditorForm::replaceText(const QString &textReplaced,const QString& readyReplaceText)
{
    if(textReplaced.isEmpty() && readyReplaceText.isEmpty()) return;

    QString readyText = ui->textEdit->toPlainText();
    int index = 0;

    while((index = readyText.indexOf(textReplaced,index)) != -1)
    {
        readyText.replace(index,textReplaced.length(),readyReplaceText);

        index+= readyReplaceText.length();

        if(index >= readyText.length())
        {
            break;
        }
    }

    ui->textEdit->setPlainText(readyText);
    currChangedText_ = readyReplaceText;
    CurrBackText_ = textReplaced;

}

void ArdaEditorForm::Cancel(const EditorCancel cancel)
{
    switch (cancel) {
    case EditorCancel::CancelBack:
        BackText();
        break;
    case EditorCancel::CancelSource:
        ui->textEdit->setPlainText(SourceText_);
        break;
    }

}

void ArdaEditorForm::BackText()
{
    qDebug() << currChangedText_ << CurrBackText_;
    replaceText(currChangedText_,CurrBackText_);
}


void ArdaEditorForm::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ArdaEditorForm::dropEvent(QDropEvent *dEvent)
{

    if(dEvent->mimeData()->hasUrls())
    {
        QList<QUrl> datas = dEvent->mimeData()->urls();
        QString path = datas.first().toLocalFile();
        QFile file(path);
        QFileInfo inf(path);
        if(!file.exists()) return;


        setWindowTitle(inf.fileName());

        openFile(file,ModeValidator::ReadFile);
        QByteArray bArr = file.readAll();
        QString text = QString::fromUtf8(bArr);
        ui->textEdit->setText(text);

    }

}
void ArdaEditorForm::loadSettings()
{
    QtConcurrent::run([this]() {
        QSettings settings(SerelizationData::ORG_NAME, "Editor");

        QString title = settings.value("Path").toString();
        QString path = title;
        QString fontName = settings.value("font").toString();
        QString text = settings.value("textEdit").toString();

        if (fontName == "MS Sans Serif" || fontName.isEmpty()) {
            fontName = "Microsoft Sans Serif";
        }

        bool ok = false;
        int size = settings.value("sizeFont").toInt(&ok);
        if (!ok) {
            size = 12;
        }

        QMetaObject::invokeMethod(this, [this, title, path, fontName, size, text]() {

            if (!title.isEmpty()) {
                setWindowTitle(title);
            }

            path_ = path;

            if (!fontName.isEmpty()) {
                ui->fontComboBox->setCurrentFont(QFont(fontName));
                ui->horizontalSlider->setValue(size);

                QFont font(fontName);
                font.setPointSize(size);
                ui->textEdit->setFont(font);
            }

            if (!text.isEmpty()) {
                ui->textEdit->setText(text);
                SourceText_ = text;
            }


            Connections();
        });
    });
}

void ArdaEditorForm::Connections()
{

    fileManager_ = std::make_unique<FileManager>();

    connect(ui->btnCancel,&QPushButton::clicked,this,[this]()
    {
        this->Cancel(EditorCancel::CancelBack);
    });

    connect(ui->btnSourceText,&QPushButton::clicked,this,[this](){
        this->Cancel(EditorCancel::CancelSource);
    });

    connect(exitAction,&QAction::triggered,this,[this](){
        this->close();
        mainWindow->show();
    });

    connect(ui->horizontalSlider,&QSlider::valueChanged,this,[this](int value)
    {
        QFont font = ui->textEdit->font();
        font.setPointSize(value);
        ui->textEdit->setFont(font);
        QSettings settings(SerelizationData::ORG_NAME,"Editor");
        settings.setValue("sizeFont",ui->horizontalSlider->value());

    });

    connect(ui->fontComboBox,&QFontComboBox::currentFontChanged,this,[this](const QFont& f){
        ui->textEdit->setFont(f);
        QSettings settings(SerelizationData::ORG_NAME,"Editor");
        settings.setValue("font",ui->fontComboBox->currentFont());
    });

    connect(bold,&QCheckBox::checkStateChanged,this,[this](){
        QFont font = ui->textEdit->font();
        font.setBold(true);
        ui->textEdit->setFont(font);
    });

    connect(italic,&QCheckBox::checkStateChanged,this,[this](){
        QFont font = ui->textEdit->font();
        font.setItalic(true);
        ui->textEdit->setFont(font);
    });

    connect(ui->lineEdit,&QLineEdit::textChanged,this,[this](const QString& text){
        this->FindText(text);

    });

    connect(openAction,&QAction::triggered,this,[this]()
    {
        this->openDocument();

        QSettings settings(SerelizationData::ORG_NAME,"Editor");
        settings.setValue("Path",path_);

    });

    connect(saveAction,&QAction::triggered,this,&ArdaEditorForm::saveDocument);
    connect(printerAction,&QAction::triggered,this,&ArdaEditorForm::PrinterDocumentNative);
    connect(saveAsAction,&QAction::triggered,this,&ArdaEditorForm::SaveAsDocument);

    connect(ui->btnReplace,&QPushButton::clicked,this,[this](){
        bool ok;
        QString textFinder = QInputDialog::getText(this,
        "Замена",
        "Введите текст дя замены:",
        QLineEdit::Normal,
        "",
        &ok
    );

    if (ok && !textFinder.isEmpty()) {
        bool ok2;
        QString textReplace = QInputDialog::getText(this,
        "Замена",
        "Введите текст на который заменить:",
        QLineEdit::Normal,
        "",
        &ok2
    );

    if(ok2 && !textReplace.isEmpty())
    {
        this->replaceText(textFinder,textReplace);
        QMessageBox::information(this,"Замена","Успешно!");
    }


    }
    });


    connect(ui->textEdit,&QTextEdit::textChanged,this,[this](){
        QSettings settings(SerelizationData::ORG_NAME,"Editor");
        settings.setValue("textEdit",ui->textEdit->toPlainText());

    });
}

void ArdaEditorForm::openFile(QFile &file, ModeValidator validator)
{
    switch (validator) {
    case ModeValidator::ReadFile:
        try
        {
            Validator::isFileValid(file,ModeValidator::ReadFile);
        }
        catch(const std::invalid_argument& e)
        {
            return;
        }
        break;
    case ModeValidator::WriteFile:
        try
        {
            Validator::isFileValid(file,ModeValidator::WriteFile);
        }
        catch(const std::invalid_argument& e)
        {
            return;
        }
        break;
    case ModeValidator::DeleteWrite:
        try
        {
            Validator::isFileValid(file,ModeValidator::DeleteWrite);
        }
        catch(const std::invalid_argument& e)
        {
            return;
        }
        break;
    default:
        break;
    }
}
