#include "equipment.h"

Equipment::Equipment()
{

}

void Equipment::setequipment_id(int id)
{
    equipment_id = id;
}

int Equipment::getequipment_id()
{
    return equipment_id;
}

void Equipment::setName(QString Name)
{
    name = Name;
}

QString Equipment::getName()
{
    return name;
}

void Equipment::settype(QString type) //mdeclari nafes lesm hedheka 3lh 7atitha this
{
    this->type = type;
}

QString Equipment::gettype()
{
    return type;
}

void Equipment::set_purchase_price(int price)
{
    purchase_price = price;
}

int Equipment::getpurchase_price()
{
    return purchase_price;
}

void Equipment::set_status(QString status)
{
    this->status = status;
}

QString Equipment::getstatus()
{
    return status;
}

void Equipment::set_purchase_date(QDate date)
{
    purchase_date = date;
}

QDate Equipment::pruchase_date()
{
    return purchase_date;
}
