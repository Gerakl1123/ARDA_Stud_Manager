#include "dynamiccreateformeditordatajson.h"
#include"LogicOperation.h"
#include<QHeaderView>
#include"JsonKeys.h"
#include<QThread>
#include<QTimer>
DynamicCreateFormEditorDataJSON::DynamicCreateFormEditorDataJSON(DataEditor *form, QWidget *parent)
    : QWidget{parent},
    formEditor(form)
{


    setAttribute(Qt::WA_DeleteOnClose);


    model = new QStandardItemModel(this);
    tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    logicWorker = new LogicOperation();




    initUI();
    resize(1920,400);

    connect(formEditor,&DataEditor::getFileName,this,[this](const QString& file){
        filePath = file;
        this->setWindowTitle(filePath);


    });

    connect(formEditor,&DataEditor::GetInfoData,this,&DynamicCreateFormEditorDataJSON::setDataTable);

    connect(Save,&QPushButton::clicked,this,&DynamicCreateFormEditorDataJSON::SaveEditedData);
    connect(back,&QPushButton::clicked,this,[this](){
        this->close();
    });



}

DynamicCreateFormEditorDataJSON::~DynamicCreateFormEditorDataJSON()
{

}

bool DynamicCreateFormEditorDataJSON::setDataTable(const QList<QHash<QString, QString> > &data)
{

    bool success = logicWorker->setDataTableViewEditorForm(model,data);

    return success;
}


bool DynamicCreateFormEditorDataJSON::SaveEditedData()
{

    QFile file(filePath);
    if(filePath.isEmpty()) return false;

    auto confrim = Builder->confrimSomething();
    if(confrim == QMessageBox::No) return false;

    std::pair<bool,bool> isArrayInObjects = {false,false};

    LogicOperation::ValidFile(file,ModeValidator::DeleteWrite);
    QJsonArray arr;

    for(int row = 0; row != model->rowCount(); ++row)
    {   QJsonObject currOBJ;
        QJsonArray grades;
        QJsonArray marks;
        for(int col = 0; col != model->columnCount(); ++col)
        {
            if(model->headerData(col,Qt::Horizontal).toString() == JsonKeys::MarksStudent)
            {
                marks.append(model->index(row,col).data().toString());
                isArrayInObjects.first = true;

            }
            else if(model->headerData(col,Qt::Horizontal).toString() == JsonKeys::StudentGrades)
            {

                grades.append(model->index(row,col).data().toString());
                isArrayInObjects.second= true;

            }else
            {
                currOBJ[model->headerData(col,Qt::Horizontal).toString()] = model->index(row,col).data().toString();
            }

        }

        if(isArrayInObjects.first == true && isArrayInObjects.second == true){
        currOBJ[JsonKeys::MarksStudent] = marks;
        currOBJ[JsonKeys::StudentGrades] = grades;
        }
        arr.append(currOBJ);

    }


    QJsonDocument doc(arr);

    file.write(doc.toJson());
    file.close();
    return true;
}




void DynamicCreateFormEditorDataJSON::initUI()
{



    Builder = new BuilderForm(this);
    back = new QPushButton("Назад", this);
    Save = new QPushButton("Сохранить",this);
    layaout = new QVBoxLayout(this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(back);
    buttonLayout->addStretch();
    buttonLayout->addWidget(Save);

    layaout->addLayout(buttonLayout);
    layaout->addWidget(tableView);

    setLayout(layaout);

}
