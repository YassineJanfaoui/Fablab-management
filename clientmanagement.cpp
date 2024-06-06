#include "clientmanagement.h"
#include "ui_clientmanagement.h"
#include "client.h"
#include "connection.h"
#include "menu.h"
#include "sms.h"
#include "arduino.h"

ClientManagement::ClientManagement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientManagement)
{
    ui->setupUi(this);
    QSqlQueryModel* model = temp.getAllClients();
    ui->tableView->setModel(model);
    ControlInput();
    setupChart();
        // Check if SSL/TLS is available
        if (QSslSocket::supportsSsl()) {
            qDebug() << "SSL/TLS support is available.";
        } else {
            qDebug() << "SSL/TLS support is not available.";
        }

        /*int ret=ard.connect_arduino(); // lancer la connexion à arduino

            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< ard.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<ard.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available"<<ard.getarduino_port_name();
            }
           // QObject::connect(ard.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
            QObject::connect(ard.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));
            //le slot update_label suite à la reception du signal readyRead (reception des données).*/


}



void ClientManagement::ControlInput()
{
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->client_date->setDate(QDate::currentDate());
    ui->client_id->setValidator(new QIntValidator(1, 99999999, this));
    //ui->client_pn->setValidator(new QIntValidator(10000000, 999999999999, this));
    const QString namePattern = "^[A-Za-z ]{1,50}$";
    QValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression(namePattern), this);
    ui->client_name->setValidator(nameValidator);

}

ClientManagement::~ClientManagement()
{
    delete ui;
}



void ClientManagement::on_pushButton_10_clicked()
{
    menu *newWindow = new menu;
   newWindow->show();
   hide();
}

void ClientManagement::populateList()
{
    QSqlQueryModel* model = temp.getAllClients();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void ClientManagement::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
            int row = index.row();
            QVariant id = ui->tableView->model()->data(ui->tableView->model()->index(row, 0));
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this client?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (temp.deleteClient(id.toInt())) {
                    ui->tableView->model()->removeRow(row);
                    // refresh stats
                    QLayoutItem* item;
                    while ((item = ui->chartlayout->takeAt(0)) != nullptr) {
                            delete item->widget();
                            delete item;
                    }
                    setupChart();
                    populateList();
                }
                else {
                    QMessageBox::critical(this, "Error", "Could not delete client");
                }
            }
        }
}

void ClientManagement::on_add_client_clicked()
{
    // get the values from the input fields
        int id = ui->client_id->text().toInt();
        QString name = ui->client_name->text();
        QString gender = ui->client_gd->currentText();
        QString phoneNumber = ui->client_pn->text();
        QString email = ui->client_email->text();
        QDate membershipDate = ui->client_date->date();
        sms s;

        // create a new client object
        Client client(id, name, gender, phoneNumber, membershipDate, email);
        bool result = client.addClient();
        if (email.contains('@') && email.contains('.') ){
            if (result) {
                // refresh stats
                QLayoutItem* item;
                while ((item = ui->chartlayout->takeAt(0)) != nullptr) {
                        delete item->widget();
                        delete item;
                }
                setupChart();
                s.sendSMS("", "New Customer");
                QMessageBox::information(this, "Success", "Client added successfully");
                populateList();
            }
            else {
                QMessageBox::critical(this, "Error", "Could not add client");
            }
        }
        else {
            QMessageBox::critical(this, "Error", "Enter a valid email adress");
        }

}

void ClientManagement::on_edit_client_clicked()
{
    int id = ui->client_id->text().toInt();
    QString name = ui->client_name->text();
        QString gender = ui->client_gd->currentText();
        QString phoneNumber = ui->client_pn->text();
        QDate membershipDate = ui->client_date->date();
        QString email = ui->client_email->text();
        Client Client(id,name,gender,phoneNumber, membershipDate, email);
        bool test = Client.updateClient(id,name,gender,phoneNumber,membershipDate,email);
        if (email.contains('@') && email.contains('.') ){
            if(test)
            {
                qDebug() << "Updated well!";
                populateList();
                // refresh stats
                QLayoutItem* item;
                while ((item = ui->chartlayout->takeAt(0)) != nullptr) {
                        delete item->widget();
                        delete item;
                }
                setupChart();
            }
            else
            {
                qDebug() << "error: not updated!";
            }
        }
        else {
            QMessageBox::critical(this, "Error", "Enter a valid email adress");
        }
}



void ClientManagement::on_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        // Get the selected row
        int row = index.row();

        // Get data from the model for the selected row
        int id = index.sibling(row, 0).data().toInt();
        QString name = index.sibling(row, 1).data().toString();
        QString gender = index.sibling(row, 2).data().toString();
        QString phoneNumber = index.sibling(row, 3).data().toString();
        QDate membershipDate = index.sibling(row, 4).data().toDate();
        QString email = index.sibling(row, 5).data().toString();


        // Display the data in appropriate UI elements
        ui->client_id->setText(QString::number(id));
        ui->client_name->setText(name);
        ui->client_pn->setText(phoneNumber);
        int genderIndex = ui->client_gd->findText(gender);
                if (genderIndex != -1) {
                    ui->client_gd->setCurrentIndex(genderIndex);
                }
        ui->client_date->setDate(membershipDate);
        ui->client_email->setText(email);
    }
}



void ClientManagement::on_reset_client_clicked()
{
    ui->client_id->clear();
    ui->client_name->clear();
    ui->client_pn->clear();
    ui->client_date->setDate(QDate::currentDate());
    ui->client_email->clear();
}


void ClientManagement::on_Newest_clicked()
{
    QSqlQueryModel* model = temp.sortMembershipDesc();
    ui->tableView->setModel(model);
    ControlInput();
}


void ClientManagement::on_Oldest_clicked()
{
    QSqlQueryModel* model = temp.sortMembershipAsc();
    ui->tableView->setModel(model);
    ControlInput();
}

void ClientManagement::on_Refresh_clicked()
{
    QSqlQueryModel* model = temp.getAllClients();
    ui->tableView->setModel(model);
    ControlInput();
}


void ClientManagement::on_Search_clicked()
{
    QString Name = ui->client_search->text();
    ui->tableView->setModel(temp.searchName(Name));
}






void ClientManagement::on_PDF_clicked()
{
        // Get the file path from the user using QFileDialog
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), QDir::homePath(), tr("PDF Files (*.pdf)"));

        // Check if the user canceled the dialog
        if (filePath.isNull())
            return;

        // Create a PDF writer with the specified file path
        QPdfWriter pdf(filePath);

        // Create a QPainter to draw on the PDF
        QPainter painter(&pdf);

        // Set initial vertical position for drawing
        int i = 4100;

        // Set text colors and fonts
        QColor dateColor(0x4a5bcf);
        QColor titleColor(0x341763);

        // Draw document title and rectangles
        painter.setPen(titleColor);
        painter.setFont(QFont("Montserrat SemiBold", 20));
        painter.drawText(2900, 2400, "Client");

        painter.setPen(Qt::black);
        painter.setFont(QFont("Time New Roman", 15));
        painter.drawRect(100, 100, 9400, 2500);
        painter.drawRect(100, 3300, 9400, 500);

        // Set font for attribute names and values
        painter.setFont(QFont("Montserrat SemiBold", 8));

        // Draw attribute names

        painter.drawText(500, 3600, "ID");
        painter.drawText(1500, 3600, "NAME");
        painter.drawText(3200, 3600, "GENDER");
        painter.drawText(4700, 3600, "PHONE NUMBER");
        painter.drawText(6400, 3600, "MEMBERSHIP DATE");
        painter.drawText(8200, 3600, "EMAIL");

        // Draw rectangles for data
        painter.setFont(QFont("Montserrat", 9));
        painter.drawRect(100, 3300, 9400, 9000);

        // Fetch data from the database and draw on the PDF
        QSqlQuery query;
        query.prepare("SELECT * FROM Client");
        query.exec();
        int y = 4300;

        while (query.next())
        {
            painter.drawLine(100, y, 9490, y);
            y += 500;

            // Draw client details
            painter.drawText(500, i, query.value(0).toString());
            painter.drawText(1500, i, query.value(1).toString());
            painter.drawText(3200, i, query.value(2).toString());
            painter.drawText(4700, i, query.value(3).toString());
            painter.drawText(6400, i, query.value(4).toDate().toString());
            painter.drawText(8200, i, query.value(5).toString());

            i += 500;
        }

        // Close the QPainter and release resources
        painter.end();

        // Show a message box with an option to open the PDF
        int response = QMessageBox::question(this, "Generate PDF", "PDF saved. Do you want to open it?", QMessageBox::Yes | QMessageBox::No);

        if (response == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
        }
}

void ClientManagement::setupChart()
{
    // Fetch data from the database for clients
    Client C;
    QSqlQueryModel *model = C.getAllClients();

    // Create a pie series
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

    // Count the number of male and female clients
    int maleCount = 0;
    int femaleCount = 0;

    // Iterate through the data and count male and female clients
    for (int i = 0; i < model->rowCount(); ++i) {
        // Extracting data from the model
        QString gender = model->record(i).value("Gender").toString();

        // Count male and female clients
        if (gender.toLower() == "male")
            maleCount++;
        else if (gender.toLower() == "female")
            femaleCount++;
    }

    // Add data to the series
    series->append("Male", maleCount);
    series->append("Female", femaleCount);

    // Create a chart and add the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Client Genders");

    // Set the theme of the chart
    chart->setTheme(QtCharts::QChart::ChartThemeLight);

    // Create a chart view and set the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the chart view to the chart layout
    ui->chartlayout->addWidget(chartView);
}







void ClientManagement::on_Chart_clicked()
{
    // Prepare the SQL query to fetch client IDs and their counts
    QSqlDatabase db = QSqlDatabase::database(); // Retrieve the default database connection
    QSqlQuery query(db);
    query.prepare("SELECT id, (SELECT COUNT(*) FROM participation WHERE clientid = client.id) AS participation_count,(SELECT COUNT(*) FROM reservation WHERE clientid = client.id) AS reservation_count FROM client;");

    // Execute the query
    if(query.exec())
    {
        // Create a table to display the results
        QTableWidget *tableWidget = new QTableWidget(this);
        tableWidget->setColumnCount(2);
        tableWidget->setHorizontalHeaderLabels(QStringList() << "Client ID" << "Pack");

        // Iterate through the query results
        while(query.next())
        {
            int clientID = query.value("id").toInt();
            int participationCount = query.value("participation_count").toInt();
            int reservationCount = query.value("reservation_count").toInt();

            // Determine the pack based on counts
            QString pack;
            int totalCount = participationCount + reservationCount;
            if (totalCount == 0)
                pack = "Bronze";
            else if (totalCount == 1)
                pack = "Silver";
            else
                pack = "Gold";

            // Add the client ID and pack to the table
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(clientID)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(pack));
        }

        // Resize the table widget to a larger size
        tableWidget->resize(220, 300); // Adjust the size as needed

        // Move the table widget to a new position
        tableWidget->move(1200, 300); // Adjust the position as needed

        // Show the table
        tableWidget->show();
    }
    else
    {
        // Handle query execution error
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}


