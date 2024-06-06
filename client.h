#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QObject>
#include "Client.h"
#include <QPrinter>
#include <QPainter>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QtCharts>
#include <QSqlRecord>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QCoreApplication>


class Client
{
public:
    Client();
    Client(int id, QString name, QString gender, QString phoneNumber, QDate membershipDate, QString email);
    Client(const Client& other);

    // Getters
    int getID() const { return id; }
    QString getName() const { return name; }
    QString getGender() const { return gender; }
    QString getPhoneNumber() const { return phoneNumber; }
    QDate getMembershipDate() const { return membershipDate; }
    QString getEmail() const { return email; }

    // Setters
    void setID(int id) { this->id = id; }
    void setName(QString name) { this->name = name; }
    void setGender(QString gender) { this->gender = gender; }
    void setPhoneNumber(QString phoneNumber) { this->phoneNumber = phoneNumber; }
    void setMembershipDate(QDate membershipDate) { this->membershipDate = membershipDate; }
    void setEmail(QString email) { this->email = email; }

    // CRUD
        bool addClient();
        bool updateClient(int, QString, QString, QString, QDate, QString);
        bool deleteClient(int);
        QSqlQueryModel* getAllClients();
        QSqlQueryModel * sortMembershipAsc();
        QSqlQueryModel * sortMembershipDesc();
        QSqlQueryModel * searchName(QString);
        void exportClientDetails_toPDF(int id, QString name, QString gender, QString phoneNumber, QDate membershipDate, QString email, QString filePath);
        int NbreservationClient(int id);
        int Nbparticipation(int id);

private:
    int id;
    QString name;
    QString gender;
    QString phoneNumber;
    QDate membershipDate;
    QString email;
};

#endif // CLIENT_H
