#include "dataeditor.h"
#include "ui_dataeditor.h"
#include<QTimer>
#include"parserjson.h"
#include"dynamiccreateformeditordatajson.h"
#include<QDragEnterEvent>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QUrl>
#include"mainwindow.h"
DataEditor::DataEditor(MainWindow *qMain, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataEditor)
    , main_(qMain)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    setAcceptDrops(true);
    this->setWindowTitle("Редактор Данных✏️");
    this->setWindowIcon(QIcon(":/icons/Edit.png"));

    setStyleSheet(R"(
        DataEditor {
            border: 3px dashed #aaa;
            border-radius: 10px;
            background-color: #f5f5f5;
            padding: 20px;
            margin: 10px;
        }

        DataEditor:hover {
            border-color: #0078d7;
            background-color: #e8f4fd;
        }
    )");

    setAttribute(Qt::WA_StaticContents);
    fileChooicer = std::make_unique<FileManager>();
    JSONFormCreator = new DynamicCreateFormEditorDataJSON(this);


    connect(ui->pushButton,&QPushButton::clicked,this,&DataEditor::back);
}
void DataEditor::back()
{
    this->close();
    main_->show();
}

DataEditor::~DataEditor()
{
    delete ui;
}

void DataEditor::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {
        setWindowTitle("x:" + QString::number(event->pos().rx()) + " " + "y:"+QString::number(event->pos().ry()));

        fileName = fileChooicer->chooseFileJson();
        if(fileName.isEmpty()) return;

        emit getFileName(fileName);
        qDebug() << fileName;

        JSONFormCreator->show();
        getData();

        QTimer::singleShot(1000, this, [this]() {
            setStyleSheet("");
        });
    }

    QWidget::mousePressEvent(event);
}

void DataEditor::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
        addDragOverStyle();
        m_dragOver = true;
    }
}

void DataEditor::dragLeaveEvent(QDragLeaveEvent *event) {
    removeDragOverStyle();
    m_dragOver = false;
    event->accept();
}

void DataEditor::dropEvent(QDropEvent *event) {
    removeDragOverStyle();
    m_dragOver = false;
    if (event->mimeData()->hasUrls()) {
        auto url = event->mimeData()->urls().first();
        QString file = url.toLocalFile();
        fileName = file;
        qDebug() << file;

        emit getFileName(file);


    }

    event->acceptProposedAction();

    JSONFormCreator->show();

    getData();

}


void DataEditor::getData()
{
    qDebug() << "getData";
    std::unique_ptr<ParserJson> p = std::make_unique<ParserJson>();

    QFileInfo info(fileName);
    if(info.size() == 0) return;
    auto data = p->ParsingJsonEditorForm(fileName);


    emit GetInfoData(data);

}

void DataEditor::addDragOverStyle() {
    QString currentStyle = this->styleSheet();
    if (!currentStyle.contains("drag-over")) {
        this->setStyleSheet(currentStyle +
            R"(
            DataEditor {
                border: 3px solid #0078d7;
                background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 rgba(0, 120, 215, 0.15),
                    stop:1 rgba(0, 120, 215, 0.05));
                border-radius: 10px;
            }
            )");
    }
}

void DataEditor::removeDragOverStyle() {
    this->setStyleSheet(R"(
        DataEditor {
            border: 3px dashed #aaa;
            border-radius: 10px;
            background-color: #f5f5f5;
            padding: 20px;
            margin: 10px;
        }

        DataEditor:hover {
            border-color: #0078d7;
            background-color: #e8f4fd;
        }
    )");
}
