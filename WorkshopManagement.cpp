#include "WorkshopManagement.h"
#include "ui_WorkshopManagement.h"
#include "src/SmtpMime"


WorkshopManagement::WorkshopManagement(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::WorkshopManagement)
{
    ui->setupUi(this);

    timer.start(5000);
    QObject::connect(&timer, &QTimer::timeout, this, &WorkshopManagement::checkWorkshopDatetime);

    populateComboBox();
    populateList();

    ui->participationTable->setModel(temp.Participation());
    ui->participationTable->resizeColumnsToContents();
    ui->participationTable->resizeRowsToContents();

    ui->add_duration->setValidator(new QIntValidator(1,12, this));
    ui->edit_duration->setValidator(new QIntValidator(1,12, this));
    ui->add_max->setValidator(new QIntValidator(1,25, this));
    ui->edit_particip->setValidator(new QIntValidator(1,25, this));
    ui->edit_start->setDateTime(QDateTime::currentDateTime());
    ui->add_start->setDateTime(QDateTime::currentDateTime());

    const QString namePattern = "^[A-Za-z\\s]{1,250}$";
    QValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression(namePattern), this);
    ui->add_name->setValidator(nameValidator);
    ui->edit_name->setValidator(nameValidator);

    QLayoutItem* item;
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Add the new chartView widget
    QtCharts::QChartView* chartView = temp.stats();
    ui->verticalLayout->addWidget(chartView);


    //arduino
    /*int ret=A.connect_arduino(); // launch the connection to arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }*/

}

WorkshopManagement::~WorkshopManagement()
{
    delete ui;
}


void WorkshopManagement::populateComboBox()
{
    QList<int> employeeIds = temp.fetchEmployeeIds();

    foreach(int id, employeeIds) {
        ui->add_manager->addItem(QString::number(id));
        ui->edit_manager->addItem(QString::number(id));
    }
}



void WorkshopManagement::populateList()
{
    ui->list->setModel(temp.read());
    ui->list->resizeColumnsToContents();
    ui->list->resizeRowsToContents();

    QLayoutItem* item;
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QtCharts::QChartView* chartView = temp.stats();
    ui->verticalLayout->addWidget(chartView);
}

void WorkshopManagement::on_nextStack2_clicked()
{
    ui->stack->setCurrentWidget(ui->editPage);
}

void WorkshopManagement::on_nextStack1_clicked()
{
    ui->stack->setCurrentWidget(ui->addPage);
}

void WorkshopManagement::on_menu_clicked()
{
    menu *newWindow = new menu;
    newWindow->show();
    hide();
}

void WorkshopManagement::on_add_clicked()
{
    QString name = ui->add_name->text();
    QString desc = ui->add_description->toPlainText();
    QDateTime start = ui->add_start->dateTime();
    int maxPart = ui->add_max->text().toInt();
    int duration = ui->add_duration->text().toInt();
    int manager = ui->add_manager->currentText().toInt();

    Workshop w(NULL,name,desc,maxPart,NULL,start,duration,manager);
    bool test = w.create();

    if(test)
    {
        qDebug() << "inserted well!";
        populateList();
    }
    else
    {
        qDebug() << "error: not inserted!";
    }
}

void WorkshopManagement::on_list_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        int row = index.row();
        int id = ui->list->model()->data(ui->list->model()->index(row, 0)).toInt();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete this workshop?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (temp.Delete(id))
            {
                ui->list->model()->removeRow(row);
                populateList();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Failed to delete from the database.");
            }
        }
    }
}


void WorkshopManagement::on_edit_clicked()
{
    QString name = ui->edit_name->text();
    QString desc = ui->edit_description->toPlainText();
    QDateTime start = ui->edit_start->dateTime();
    int maxPart = ui->edit_max->text().toInt();
    int duration = ui->edit_duration->text().toInt();
    int manager = ui->edit_manager->currentText().toInt();
    int part = ui->edit_particip->text().toInt();

    Workshop w(NULL,name,desc,maxPart,part,start,duration,manager);
    bool test = w.Update(ui->id->text().toInt());

    if(test)
    {
        qDebug() << "Updated well!";
        populateList();
    }
    else
    {
        qDebug() << "error: not updated!";
    }
}


void WorkshopManagement::on_list_clicked(const QModelIndex &index)
{
    ui->stack->setCurrentWidget(ui->editPage);
    int row = index.row();
    int selectedId = ui->list->model()->data(ui->list->model()->index(row, 0)).toInt();
    QString name, description;
    int maxParticipants, numParticipants, duration, managerId;
    QDateTime startDate;

    temp.fetchWorkshopDetails(selectedId, name, description, maxParticipants, numParticipants, startDate, duration, managerId);

    ui->edit_name->setText(name);
    ui->id->setText(ui->list->model()->data(ui->list->model()->index(row, 0)).toString());
    ui->edit_particip->setText(QString::number(numParticipants));
    ui->edit_description->setText(description);
    ui->edit_max->setText(QString::number(maxParticipants));
    ui->edit_start->setDateTime(startDate);
    ui->edit_duration->setText(QString::number(duration));
    ui->edit_manager->setCurrentText(QString::number(managerId));
    
    //arduino
    QString message = name + " " + description;
    QByteArray byteArray = message.toUtf8();
    A.write_to_arduino(byteArray+'\n');

}

void WorkshopManagement::on_newest_clicked()
{
    ui->list->setModel(temp.sort_newest());
    ui->list->resizeColumnsToContents();
    ui->list->resizeRowsToContents();
}

void WorkshopManagement::on_oldest_clicked()
{
    ui->list->setModel(temp.sort_oldest());
    ui->list->resizeColumnsToContents();
    ui->list->resizeRowsToContents();
}

void WorkshopManagement::on_reset_clicked()
{
    populateList();
    ui->search_field->clear();
    ui->stack->setCurrentWidget(ui->addPage);
    ui->add_max->clear();
    ui->add_name->clear();
    ui->add_duration->clear();
    ui->add_description->clear();
    ui->edit_max->clear();
    ui->edit_name->clear();
    ui->edit_duration->clear();
    ui->edit_description->clear();

}

void WorkshopManagement::on_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document", qApp->applicationDirPath(), "*.pdf");

    if (!fileName.isEmpty()) {
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);


        temp.importer_pdf(printer);

    }
}

void WorkshopManagement::on_search_field_textChanged(const QString &arg1)
{
    ui->list->setModel(temp.search(arg1));
    ui->list->resizeColumnsToContents();
    ui->list->resizeRowsToContents();
}

void WorkshopManagement::checkWorkshopDatetime()
{
    QString test;
    test = temp.checkDate();

    if (test != "false") {
        QSystemTrayIcon *trayIcon = new QSystemTrayIcon;
        QTextToSpeech *speech = new QTextToSpeech(this);
        speech->setVolume(1.0);
        speech->setRate(0.0);
        speech->say("Workshop "+test+", has started!\nIf you are the instructor please head to the workshop room.");
        trayIcon->setIcon(QIcon(":/icon.png"));
        trayIcon->show();
        trayIcon->showMessage("Workshop Notification", "Workshop "+test+", has started!\nIf you are the instructor please head to the workshop room.", QSystemTrayIcon::Information, 5000);
    }


}


void WorkshopManagement::on_particip_clicked()
{
    QDialog dialog(this);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    QLabel *label = new QLabel("Client ID:", &dialog);
    QLabel *label2 = new QLabel("Workshop ID:", &dialog);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(label2);
    layout->addWidget(lineEdit2);

    QPushButton *okButton = new QPushButton("OK", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);
    QObject::connect(okButton, &QPushButton::clicked, &dialog, [&]() {
        int clientId = lineEdit->text().toInt();
        int workshopId = lineEdit2->text().toInt();
        bool success = temp.addClient(clientId,workshopId);

        if (success) {
            QString email;
            QString name;
            temp.fetchClientDetails(clientId,email,name);
            QString nameW, description;
            int maxParticipants, numParticipants, duration, managerId;
            QDateTime startDate;
            temp.fetchWorkshopDetails(workshopId, nameW, description, maxParticipants, numParticipants, startDate, duration, managerId);

            SmtpClient smtp("smtp.gmail.com",465,SmtpClient::SslConnection);
            smtp.setUser("");
            smtp.setPassword("");

            MimeMessage message;

            message.setSender(new EmailAddress("", "Fabritech"));
            message.addRecipient(new EmailAddress(email, name));
            message.setSubject("Workshop Participation confirmation.");
            MimeText text;
            QString messageSend;
            messageSend = "Hello, "+name+",\nThank you for participating in "+nameW+":\n"+description+"\nWe hope to see you in our future workshops.";
            text.setText(messageSend);
            message.addPart(&text);

            if (smtp.connectToHost()) {
                if(smtp.login())
                {
                    smtp.sendMail(message);
                    smtp.quit();
                }
                else
                {
                    qDebug() << "Failed to authenticate.";
                }
            } else {
                qDebug() << "Failed to connect to SMTP server.";
            }
            if (!success) {
                qDebug() << "Failed to add client";
            }
        } else {
            qDebug() << "Failed to insert record into PARTICIPATION table:";
        }
        dialog.close();
    });
    QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::close);

    dialog.exec();
    populateList();
    ui->participationTable->setModel(temp.Participation());
    ui->participationTable->resizeColumnsToContents();
    ui->participationTable->resizeRowsToContents();
}

void WorkshopManagement::on_participationTable_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        int row = index.row();
        int workshopid = ui->participationTable->model()->data(ui->participationTable->model()->index(row, 0)).toInt();
        int clientid = ui->participationTable->model()->data(ui->participationTable->model()->index(row, 1)).toInt();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete this participation?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (temp.DeleteParticip(clientid,workshopid))
            {
                ui->participationTable->model()->removeRow(row);
                ui->participationTable->setModel(temp.Participation());
                ui->participationTable->resizeColumnsToContents();
                ui->participationTable->resizeRowsToContents();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Failed to delete from the database.");
            }
        }
    }
}


