#include "texpanel.h"
#include "ui_texpanel.h"

TexPanel::TexPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TexPanel)
{
    ui->setupUi(this);

}

TexPanel::~TexPanel()
{
    delete ui;
}
