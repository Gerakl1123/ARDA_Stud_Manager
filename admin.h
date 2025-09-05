#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

class MainWindow;

namespace Ui {
class ADMIN;
}

class ADMIN : public QWidget
{
    Q_OBJECT

public:
    explicit ADMIN(MainWindow* main, QWidget *parent = nullptr);
    ~ADMIN();

private:
    Ui::ADMIN *ui;
    MainWindow* mainWindow;   // ссылка на главное окно
};

#endif // ADMIN_H
