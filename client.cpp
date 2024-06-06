#include "client.h"



Client::Client()
{
    // initialize the variables with default values
    id = 0;
    name = "default";
    gender = "default";
    phoneNumber = "default";
    membershipDate = QDate::currentDate();
    email = "default";
}

Client::Client(int id, QString name, QString gender, QString phoneNumber, QDate membershipDate, QString email)
{
    this->id = id;
    this->name = name;
    this->gender = gender;
    this->phoneNumber = phoneNumber;
    this->membershipDate = membershipDate;
    this->email = email;
}

bool Client::addClient()
{
    // create a new query
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("INSERT INTO client (ID, NAME , GENDER, PHONE_NUMBER, MEMBERSHIP_DATE, EMAIL) "
    "VALUES (:ID,:Nameclient, :Genderclient, :Phoneclient, TO_DATE(:MembershipDate, 'YYYY-MM-DD'), :Emailclient)");

    // bind the values to the query
    query.bindValue(":ID", id_string);
    query.bindValue(":Nameclient", name);
    query.bindValue(":Genderclient", gender);
    query.bindValue(":Phoneclient", phoneNumber);
    query.bindValue(":MembershipDate", membershipDate.toString("yyyy-MM-dd"));
    query.bindValue(":Emailclient", email);

    // execute the query
     return query.exec();
}

QSqlQueryModel* Client::getAllClients()
{
    // create a new query
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PhoneNumber"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Membership_date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    //model->setHeaderData(6, Qt::Horizontal, QObject::tr("Pack"));
    return model;
}


QSqlQueryModel* Client :: sortMembershipAsc()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from CLIENT order by membership_date asc;");
    return model;
}

QSqlQueryModel* Client :: sortMembershipDesc()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from CLIENT order by membership_date desc");
    return model;
}


QSqlQueryModel* Client ::searchName(QString n)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Using a parameterized query to avoid SQL injection
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT where name = :name;");
    query.bindValue(":name", n);

    if (query.exec())
    {
        model->setQuery(query);

    }
    else
    {
        qDebug() << "Error executing query: " << query.lastError().text();
        // Handle the error as needed
    }

    return model;
}

void Client::exportClientDetails_toPDF(int id, QString name, QString gender, QString phoneNumber, QDate membershipDate, QString email, QString filePath)
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);

    QFont titleFont("Arial", 18, QFont::Bold);
    QFont attributeFont("Arial", 12);

    QColor titleColor(0, 102, 204);
    QColor attributeColor(51, 51, 51);
    QColor borderColor(0, 0, 0);
    QColor backgroundColor(255, 255, 255);

    QRect rect = printer.pageRect();
    int pageWidth = rect.width();
    int pageHeight = rect.height();

    int centerX = pageWidth / 2;

    painter.setPen(borderColor);
    painter.drawRect(0, 0, pageWidth - 1, pageHeight - 1);
    painter.drawRect(50, 50, pageWidth - 100, pageHeight - 100);
    painter.fillRect(51, 51, pageWidth - 101, pageHeight - 101, backgroundColor);

    painter.setFont(titleFont);
    painter.setPen(titleColor);
    painter.drawText(rect, Qt::AlignTop | Qt::AlignHCenter, "Client Details");

    painter.setPen(borderColor);
    painter.drawLine(60, 120, pageWidth - 60, 120);
    painter.drawLine(60, 240, pageWidth - 60, 240);
    painter.drawLine(60, 360, pageWidth - 60, 360);
    painter.drawLine(60, 480, pageWidth - 60, 480);

    painter.setFont(attributeFont);
    painter.setPen(attributeColor);

    int ySpacing = 80;

    painter.drawText(centerX - 100, 150, "ID:");
    painter.drawLine(centerX - 70, 150, centerX + 70, 150);
    painter.drawText(centerX - 100, 150, QString::number(id));

    painter.drawText(centerX - 100, 150 + ySpacing, "Name:");
    painter.drawLine(centerX - 70, 150 + ySpacing, centerX + 70, 150 + ySpacing);
    painter.drawText(centerX - 100, 150 + ySpacing, name);

    painter.drawText(centerX - 100, 150 + 2 * ySpacing, "Gender:");
    painter.drawLine(centerX - 70, 150 + 2 * ySpacing, centerX + 70, 150 + 2 * ySpacing);
    painter.drawText(centerX - 100, 150 + 2 * ySpacing, gender);

    painter.drawText(centerX - 100, 150 + 3 * ySpacing, "Phone Number:");
    painter.drawLine(centerX - 70, 150 + 3 * ySpacing, centerX + 70, 150 + 3 * ySpacing);
    painter.drawText(centerX - 100, 150 + 3 * ySpacing, phoneNumber);

    painter.drawText(centerX - 100, 150 + 4 * ySpacing, "Membership Date:");
    painter.drawLine(centerX - 70, 150 + 4 * ySpacing, centerX + 70, 150 + 4 * ySpacing);
    painter.drawText(centerX - 100, 150 + 4 * ySpacing, membershipDate.toString());

    painter.drawText(centerX - 100, 150 + 5 * ySpacing, "Email:");
    painter.drawLine(centerX - 70, 150 + 5 * ySpacing, centerX + 70, 150 + 5 * ySpacing);
    painter.drawText(centerX - 100, 150 + 5 * ySpacing, email);

    painter.end();

    qDebug() << "Export to PDF successful. Saved at: " << filePath;
}




bool Client::updateClient(int id, QString name, QString gender, QString phoneNumber, QDate membershipDate, QString email)
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("UPDATE client SET NAME = :Name, GENDER = :Gender, PHONE_NUMBER = :PhoneNumber, MEMBERSHIP_DATE = TO_DATE(:MembershipDate, 'YYYY-MM-DD'), EMAIL = :Email WHERE ID = :id");

    query.bindValue(":id", id_string);
    query.bindValue(":Name", name);
    query.bindValue(":Gender", gender);
    query.bindValue(":PhoneNumber", phoneNumber);
    query.bindValue(":MembershipDate", membershipDate.toString("yyyy-MM-dd"));
    query.bindValue(":Email", email);


     return query.exec();
}

bool Client::deleteClient(int id)
{
    // create a new query
    QSqlQuery query;
    query.prepare("DELETE FROM client WHERE ID = :id");

    // bind the values to the query
    query.bindValue(":id", id);

    // execute the query
    return query.exec();
}

int Client::NbreservationClient(int id)
{
    int reservationCount = 0;
    QSqlQuery query;
    // Prepare the SQL query
    query.prepare("SELECT COUNT(*) AS reservation_count FROM reservation WHERE clientid = :client_id");
    query.bindValue(":client_id", id);

    // Execute the query
    if(query.exec())
    {
        // Fetch the result
        if(query.next())
        {
            reservationCount = query.value("reservation_count").toInt();
        }
    }
    else
    {
        // Handle query execution error
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    return reservationCount;
}

int Client::Nbparticipation(int id)
{
    int participationCount = 0;

    // Assuming you have an active database connection
    QSqlDatabase db = QSqlDatabase::database(); // Retrieve the default database connection
    QSqlQuery query(db);

    // Prepare the SQL query
    query.prepare("SELECT COUNT(*) AS participation_count FROM participation WHERE clientid = :client_id");
    query.bindValue(":client_id", id);

    // Execute the query
    if(query.exec())
    {
        // Fetch the result
        if(query.next())
        {
            participationCount = query.value("participation_count").toInt();
        }
    }
    else
    {
        // Handle query execution error
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    return participationCount;
}





