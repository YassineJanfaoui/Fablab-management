#include "workshop.h"

Workshop::Workshop() {
    // Initialize member variables with default values
    IDWorkshop = 0;
    NameWorkshop = "default";
    DescWorkshop = "default";
    MaxParticip = 0;
    NbrParticip = 0;
    StartDate = QDateTime::currentDateTime();
    Duration = 0;
    manager_id = 0;
}
Workshop::Workshop(int id, QString name, QString desc, int max, int num, QDateTime start, int duration, int manager)
{
    this->IDWorkshop = id;
    this->NameWorkshop = name;
    this->DescWorkshop = desc;
    this->MaxParticip = max;
    this->NbrParticip = num;
    this->StartDate = start;
    this->Duration = duration;
    this->manager_id = manager;
}

bool Workshop::create()
{
    QSqlQuery query;
    query.prepare("INSERT INTO workshop (NAME, DESCRIPTION, MAXPART, NUMPART, STARTDATE, DURATION,EMPLOYEEID) "
                  "VALUES ( :NameWorkshop, :DescWorkshop, :MaxParticip, :NbrParticip, :StartDate, :Duration,:manager)");
    query.bindValue(":NameWorkshop", NameWorkshop);
    query.bindValue(":DescWorkshop", DescWorkshop);
    query.bindValue(":MaxParticip", MaxParticip);
    query.bindValue(":NbrParticip", NbrParticip);
    query.bindValue(":StartDate", StartDate);
    query.bindValue(":Duration", Duration);
    query.bindValue(":manager",manager_id);

    if (!query.exec()) {
        return false;
    }
    return true;
}

QSqlQueryModel* Workshop::read()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM WORKSHOP");
    return model;
}

bool Workshop::Delete(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM WORKSHOP WHERE ID = :workshopID");
    query.bindValue(":workshopID", id);
    if (!query.exec()) {
        return false;
    }
    return true;
}
QSqlQueryModel* Workshop::Participation()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM PARTICIPATION ORDER BY workshopid DESC");
    query.exec();
    model->setQuery(query);
    return model;
}
bool Workshop::DeleteParticip(int Clientid,int workshopid)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Participation WHERE clientID = :clientID and workshopid =:workshopID");
    query.bindValue(":workshopID", workshopid);
    query.bindValue(":clientID", Clientid);
    if (!query.exec()) {
        return false;
    }
    return true;
}

bool Workshop::Update(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE WORKSHOP SET NAME = :Name , DESCRIPTION = :Desc, MAXPART = :Max, NUMPART = :Nbr, STARTDATE = :Start, DURATION = :Duration ,EMPLOYEEID = :manager "
                  "WHERE ID = :id");
    query.bindValue(":Name", NameWorkshop);
    query.bindValue(":Desc", DescWorkshop);
    query.bindValue(":Max", MaxParticip);
    query.bindValue(":Nbr", NbrParticip);
    query.bindValue(":Start", StartDate);
    query.bindValue(":Duration", Duration);
    query.bindValue(":manager",manager_id);
    query.bindValue(":id",id);

    if (!query.exec()) {
        return false;
    }
    return true;
}

QSqlQueryModel* Workshop::sort_newest()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM WORKSHOP ORDER BY STARTDATE DESC");
    return model;
}

QSqlQueryModel* Workshop::sort_oldest()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM WORKSHOP ORDER BY STARTDATE ASC");
    return model;
}

QSqlQueryModel* Workshop::search(QString name)
{
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();
    query.prepare("SELECT * FROM WORKSHOP WHERE UPPER(NAME) LIKE UPPER(:name)");
    query.bindValue(":name", "%" + name + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

bool Workshop::importer_pdf(QPrinter &printer)
{
    QTextDocument document;
    QTextCursor cursor(&document);
    QFont font("Gill sans MT", 16);
    document.setDefaultFont(font);

    QSqlQuery query("SELECT * FROM workshop");
    while (query.next())
    {
        QString id = query.value("id").toString();
        QString name = query.value("name").toString();
        QString description = query.value("description").toString();
        QString maxPart = query.value("maxpart").toString();
        QString numPart = query.value("numpart").toString();
        QString startDate = query.value("startdate").toString();
        QString duration = query.value("duration").toString();
        QString employeeId = query.value("employeeid").toString();

        cursor.insertText("Workshop ID: " + id);
        cursor.insertBlock();
        cursor.insertText("Workshop Name: " + name);
        cursor.insertBlock();
        cursor.insertText("Workshop Description: " + description);
        cursor.insertBlock();
        cursor.insertText("Maximum Participants: " + maxPart);
        cursor.insertBlock();
        cursor.insertText("Number of Participants: " + numPart);
        cursor.insertBlock();
        cursor.insertText("Start Date: " + startDate);
        cursor.insertBlock();
        cursor.insertText("Duration: " + duration);
        cursor.insertBlock();
        cursor.insertText("Employee ID: " + employeeId);
        cursor.insertBlock();
        cursor.insertBlock();
        cursor.insertBlock();
    }
    if (document.isEmpty()) {
        qDebug() << "The document is empty. No data to save to PDF.";
        return false;
    } else {
        document.print(&printer);
        qDebug() << "Printing the PDF document is done.";
        return true;
    }
}
QtCharts::QChartView* Workshop::stats()
{
    QPieSeries *series = new QPieSeries;
    QChart *chart = new QChart;
    chart->setTitle("Number of Workshops by Duration");

    QSqlQuery query("SELECT duration, COUNT(*) AS workshop_count FROM workshop GROUP BY duration");

    while (query.next()) {
        int duration = query.value("duration").toInt();
        int workshopCount = query.value("workshop_count").toInt();
        QString durationLabel = QString::number(duration);
        QString countLabel = QString::number(workshopCount);

        // Concatenate duration and count for label
        QString label = durationLabel +" weeks" + " (" + countLabel + ")";

        // Add slice to the series with label and percentage
        QPieSlice *slice = series->append(label, workshopCount);
        slice->setLabelVisible(true); // Display label on slice
    }

    chart->addSeries(series);
    chart->legend()->setVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundBrush(QBrush(QColor("#f0f0f0")));
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;


}


QString Workshop::checkDate()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QSqlQuery query;
    query.prepare("SELECT startdate,name FROM workshop WHERE TO_CHAR(startdate, 'DD-MON-RR HH.MI AM') = :currentDate");
    query.bindValue(":currentDate", currentDateTime.toString("dd-MMM-yy hh.mm AP").toUpper());
    if (!query.exec()) {

        qDebug() << "Error executing query:" << query.lastError().text();

        return "false";
    }

    if (query.next()) {
        QString name= query.value(1).toString();

        qDebug() << "good!!!";
        return name;
    }
    else
        return "false";
}

bool Workshop::addClient(int clientId,int workshopId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO PARTICIPATION (WORKSHOPID,CLIENTID) VALUES (:workshop, :client)");
    query.bindValue(":workshop",workshopId);
    query.bindValue(":client",clientId);
    bool success = query.exec();
    if(success)
    {
        query.prepare("UPDATE workshop SET numpart = numpart + 1 WHERE Id = :workshopId");
        query.bindValue(":workshopId", workshopId);
        query.exec();
    }
    return success;
}

void Workshop::fetchWorkshopDetails(int workshopId, QString &name, QString &description, int &maxParticipants, int &numParticipants, QDateTime &startDate, int &duration, int &managerId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM WORKSHOP WHERE ID = :id");
    query.bindValue(":id", workshopId);
    query.exec();

    if (query.next()) {
        name = query.value(1).toString();
        description = query.value(2).toString();
        maxParticipants = query.value(3).toInt();
        numParticipants = query.value(4).toInt();
        startDate = query.value(5).toDateTime();
        duration = query.value(6).toInt();
        managerId = query.value(7).toInt();
    }
}
void Workshop::fetchClientDetails(int clientId, QString &email, QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT email, name FROM client WHERE ID = :id");
    query.bindValue(":id", clientId);
    query.exec();

    if (query.next()) {
        email = query.value(0).toString();
        name = query.value(1).toString();
    }
}

QList<int> Workshop::fetchEmployeeIds()
{
    QList<int> employeeIds;
    QSqlQuery query;
    query.exec("SELECT ID FROM EMPLOYEES");
    while (query.next()) {
        int id = query.value(0).toInt();
        employeeIds.append(id);
    }
    return employeeIds;
}
