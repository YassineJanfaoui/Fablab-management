#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <QString>
#include <QDate>

class Equipment
{
public:
    Equipment();
    void setequipment_id(int);
    int getequipment_id();
    void setName(QString) ;
    QString getName();
    void settype(QString) ;
    QString gettype();
    void set_purchase_price(int) ;
    int getpurchase_price();
    void set_status(QString) ;
    QString getstatus();
    void set_purchase_date(QDate) ;
    QDate pruchase_date() ;
private:
    int equipment_id;
    QString name,type,status;
    int purchase_price;
    QDate purchase_date;
};

#endif // EQUIPMENT_H


