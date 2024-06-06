#ifndef PROJECT_H
#define PROJECT_H
#include <QString>
#include <QDate>

class project
{
public:
    project();
    project(int id, const QString& title, const QString& desc, const QDate& startDate, const QDate& endDate);
    project(const project& other);

    int getProjectid() const { return Projectid; }
    QString getPtitle() const { return Ptitle; }
    QString getPdesc() const { return Pdesc; }
    QDate getStartDate() const { return StartDate; }
    QDate getEndDate() const { return EndDate; }

    void setProjectid(int id) { Projectid = id; }
    void setPtitle(const QString& title) { Ptitle = title; }
    void setPdesc(const QString& desc) { Pdesc = desc; }
    void setStartDate(const QDate& startDate) { StartDate = startDate; }
    void setEndDate(const QDate& endDate) { EndDate = endDate; }

private:
    int Projectid;
    QString Ptitle;
    QString Pdesc;
    QDate StartDate;
    QDate EndDate;


};

#endif // PROJECT_H

