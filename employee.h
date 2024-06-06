#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QDate>

class Employee
{
public:
    Employee();
    void setID(QString);
    QString getID();
    void setName(QString);
    QString getName();
    void setAddress(QString);
    QString getAddress();
    void setEmail(QString);
    QString getEmail();
    void setRole(QString);
    QString getRole();
    void setSalary(int);
    int getSalary();
    void setPhoneNumber(int);
    int getPhoneNumber();
    void setHiringDate(QDate);
    QDate getHiringDate();
    void setDateOfBirth(QDate);
    QDate getDateOfBirth();


private:
    QString name,ID,address,email,role;
    int salary;
    int phoneNumber;
    QDate hiring_date, DOB;
};

#endif // EMPLOYEE_H
