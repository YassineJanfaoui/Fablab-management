#include "employee.h"

Employee::Employee()
{

}
void Employee::setID(QString id){
    ID=id;
}
QString Employee::getID(){
    return ID;
}
void Employee::setName(QString namee){
    name=namee;
}
QString Employee::getName(){
    return name;
}
void Employee::setAddress(QString add){
   address=add;
}
QString Employee::getAddress(){
    return address;
}
void Employee::setEmail(QString Email){
    email=Email;
}
QString Employee::getEmail(){
    return email;
}
void Employee::setRole(QString Role){
    role=Role;
}
QString Employee::getRole(){
    return role;
}
void Employee::setSalary(int Salary){
    salary=Salary;
}
int Employee::getSalary(){
    return salary;
}
void Employee::setPhoneNumber(int phnum){
    phoneNumber=phnum;
}
int Employee::getPhoneNumber(){
    return phoneNumber;
}
void Employee::setHiringDate(QDate HD){
    hiring_date=HD;
}
QDate Employee::getHiringDate(){
    return hiring_date;
}
void Employee::setDateOfBirth(QDate dob){
    DOB=dob;
}
QDate Employee::getDateOfBirth(){
    return DOB;
}
