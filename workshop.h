#ifndef WORKSHOP_H
#define WORKSHOP_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QPrinter>
#include <QTextDocumentWriter>
#include <QTextDocument>
#include <QFont>
#include <QTextCursor>
#include <QtCharts>
#include "arduino.h"

class Workshop
{
public:
    Workshop();
    Workshop(int id, QString name, QString desc, int max, int num, QDateTime start, int duration,int manager);

    //GETTERS
    int getIDWorkshop() { return IDWorkshop; }
    QString getNameWorkshop() { return NameWorkshop; }
    QString getDescWorkshop() { return DescWorkshop; }
    int getMaxParticip() { return MaxParticip; }
    int getNbrParticip() { return NbrParticip; }
    QDateTime getStartDate() { return StartDate; }
    int getDuration() { return Duration; }
    int getManager(){return manager_id;}

    //SETTERS
    void setIDWorkshop(int id) { IDWorkshop = id; }
    void setNameWorkshop(QString& name) { NameWorkshop = name; }
    void setDescWorkshop(QString& desc) { DescWorkshop = desc; }
    void setMaxParticip(int maxParticip) { MaxParticip = maxParticip; }
    void setNbrParticip(int nbrParticip) { NbrParticip = nbrParticip; }
    void setStartDate(QDateTime& startDate) { StartDate = startDate; }
    void setDuration(int duration) { Duration = duration; }
    void setManager(int manager){manager_id = manager;}

    //CRUD
    bool create();
    QSqlQueryModel* read();
    bool Delete(int);
    bool Update(int);
    QSqlQueryModel* sort_newest();
    QSqlQueryModel* sort_oldest();
    QSqlQueryModel* search(QString);
    bool importer_pdf(QPrinter &printer);
    QtCharts::QChartView* stats();
    QSqlQueryModel* Participation();
    bool DeleteParticip(int Clientid,int workshopid);
    QString checkDate();
    bool addClient(int clientId,int workshopId);
    void fetchWorkshopDetails(int workshopId, QString &name, QString &description, int &maxParticipants, int &numParticipants, QDateTime &startDate, int &duration, int &managerId);
    void fetchClientDetails(int clientId, QString &email, QString &name);
    QList<int> fetchEmployeeIds();

private:
    int IDWorkshop;
    QString NameWorkshop;
    QString DescWorkshop;
    int MaxParticip;
    int NbrParticip;
    QDateTime StartDate;
    int Duration;
    int manager_id;


};

#endif // WORKSHOP_H
