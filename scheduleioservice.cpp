#include "scheduleioservice.h"

ScheduleIOService::ScheduleIOService(QObject *parent)
    : QObject{parent}
{}


bool ScheduleIOService::exportToPDF(const QJsonArray &arr)
{

    FileManager fileManager;
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString filePDF = fileManager.saveFilePDF();
    printer.setOutputFileName(filePDF);
    printer.setPageSize(QPageSize(QPageSize::A4));


    QString html = "<h2 align='center'>Расписание занятий</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4' width='100%'>";
    html += "<tr>"
            "<th>Дата</th>"
            "<th>Кабинет</th>"
            "<th>Начало</th>"
            "<th>Конец</th>"
            "<th>Пара</th>"
            "<th>Предмет</th>"
            "<th>Учитель</th>"
            "<th>Месяц</th>"
            "<th>Неделя</th>"
            "<th>Семестр</th>"
            "<th>Учебный Год</th>"
            "</tr>";

    for (const auto &item : arr) {
        QJsonObject childObj = item.toObject();

        QString date = childObj.value("Дата").toString();
        QString room = childObj.value("Кабинет").toString();
        QString start = childObj.value("Начало").toString();
        QString end = childObj.value("Конец").toString();
        QString pair = QString::number(childObj.value("Пара").toInt());
        QString subject = childObj.value("Предмет").toString();
        QString teacher = childObj.value("Преподаватель").toString();
        QDate IsDate = QDate::fromString(date,"dd.MM.yyyy");

        QString semestr;

        if (IsDate.month() >= 1 && IsDate.month() < 9) {
            semestr = "Весна";
        } else {
            semestr = "Осень";
        }

        QString academicYear;
        int currentYear = IsDate.year();

        if(IsDate.month() >= 1 && IsDate.month() < 9)
        {
            academicYear = QString("%1 - %2").arg(currentYear - 1).arg(currentYear);
        }else
        {
            academicYear = QString("%1 - %2").arg(QString::number(currentYear)).arg(QString::number(currentYear + 1));
        }

        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "<td>%6</td>"
                        "<td>%7</td>"
                        "<td>%8</td>"
                        "<td>%9</td>"
                        "<td>%10</td>"
                        "<td>%11</td>"
                        "</tr>")
                    .arg(date, room, start, end, pair, subject, teacher,
                         QString::number(IsDate.month()),
                         QString::number(IsDate.weekNumber()),
                         semestr, academicYear);
    }

    html += "</table>";


    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    return true;




}
