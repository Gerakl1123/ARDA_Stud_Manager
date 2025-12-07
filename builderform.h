#ifndef BUILDERFORM_H
#define BUILDERFORM_H

#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include"FileChooicer.h"

class BuilderForm : public QWidget
{
    Q_OBJECT
public:
    explicit BuilderForm(QWidget *parent = nullptr);

    QList<QPair<QLineEdit*,QPushButton*>> initializer(QWidget* w);

    static void setupBrowseButton(QPushButton *btn,QLineEdit* line,FileManager* fileManager);


    QMessageBox::StandardButton confrimSomething();

signals:
    void fileChosen(const QString &fileName);
private:
    QHash<QString,QString> nameLineButton;

    void setupNameHash();

    void browseButton();

};

#endif // BUILDERFORM_H
