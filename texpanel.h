#ifndef TEXPANEL_H
#define TEXPANEL_H

#include <QWidget>

namespace Ui {
class TexPanel;
}

class TexPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TexPanel(QWidget *parent = nullptr);
    ~TexPanel();

private:
    Ui::TexPanel *ui;
};

#endif // TEXPANEL_H
