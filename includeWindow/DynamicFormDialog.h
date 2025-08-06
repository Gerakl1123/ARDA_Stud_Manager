#ifndef DYNAMICFORMDIALOG_H
#define DYNAMICFORMDIALOG_H
#include <QDialog>
#include<QTextEdit>
#include<QLineEdit>
#include<memory>
#include"mainwindow.h"
#include"FileChooicer.h"
#include<memory>
#include"BuildForm.h"
#include"Serializer.h"
#include"LogicOperation.h"

class QFormLayout;// использую 1 раз

class DynamicDialog : public QDialog {
    Q_OBJECT
public:
    enum class Mode {
        AddStudent,
        PreviewFile,
        DeleteStudent,
        Back,
        SortStudent,
        FindStudent
    };

    explicit DynamicDialog(Mode mode,QWidget* parent = nullptr);
    ~DynamicDialog() = default;

private slots:
    void onAccept();

private:
    Mode currentMode;
    QFormLayout* formLayout;
    std::unique_ptr<FileManager> fileManager;

    void setupUI();
    void buildFormForMode();
    void clearForm();

    void handleAddStudent();
    void handlePriviewFile();
    void handleSortStudent();
    void handleDeleteStudent();
    void handleFindStudent();


private:
    std::unique_ptr<SerializerData> serializer;
    std::unique_ptr<IHandleStudent> handleAdd;

    void Style();
    void SetBTNbrowse(QPushButton* btn,QLineEdit* line);
    QLineEdit* ManagerStudent_addStudentFileEdit = nullptr;
    QLineEdit* ManagerStudent_addStudentDataEdit = nullptr;

    // === Sort Students ===
    QLineEdit* ManagerStudent_sortInputFileEdit = nullptr;
    QLineEdit* ManagerStudent_sortOutputFileEdit = nullptr;

    // === Find Student ===
    QLineEdit* ManagerStudent_findFileEdit = nullptr;
    QLineEdit* ManagerStudent_findNameEdit = nullptr;
    QLineEdit* ManagerStudent_findScoreEdit = nullptr;

    // === Delete Student ===
    QLineEdit* ManagerStudent_deleteFileEdit = nullptr;
    QLineEdit* ManagerStudent_deleteNameEdit = nullptr;
    QLineEdit* ManagerStudent_deleteScoreEdit = nullptr;

    // === Print Students ===
    QTextEdit* studentDisplay = nullptr;
    QLineEdit* ManagerStudent_printFileEdit = nullptr;
private:
    QPushButton* btnAddStudentBrowse = nullptr;
    QPushButton* btnSortInputBrowse = nullptr;
    QPushButton* btnSortOutputBrowse = nullptr;
    QPushButton* btnFindFileBrowse = nullptr;
    QPushButton* btnDeleteFileBrowse = nullptr;
    QPushButton* btnPrintFileBrowse = nullptr;

};

#endif // DYNAMICFORMDIALOG_H
