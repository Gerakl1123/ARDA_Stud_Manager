#ifndef ARDAEDITORFORM_H
#define ARDAEDITORFORM_H

#include <QWidget>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QMimeData>
#include"ModeValidator.h"
#include"parserjson.h"
#include"FileChooicer.h"
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include<QSettings>
#include<QFileSystemModel>

enum class EditorCancel
{
    CancelBack = 0,
    CancelSource = 1
};

namespace Ui {
class ArdaEditorForm;
}

class MainWindow;

class ArdaEditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit ArdaEditorForm(MainWindow *qMain, QWidget *parent = nullptr);
    ~ArdaEditorForm();
signals:
    void getData(const QString& text);
    void savePath(const QString& path);
private slots:
    void saveDocument();
    void openDocument();
    void PrinterDocumentNative();
    void SaveAsDocument();
    void FindText(const QString& findValue);
    void replaceText(const QString& textReplaced, const QString &readyReplaceText);
    void Cancel(const EditorCancel cancel);
    void BackText();
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
private:
    QString path_;
    QString currChangedText_,CurrBackText_,SourceText_;
    MainWindow* mainWindow;
    std::unique_ptr<FileManager> fileManager_;
    void openFile(QFile&file, ModeValidator validator);
    Ui::ArdaEditorForm *ui;
};

#endif // ARDAEDITORFORM_H
