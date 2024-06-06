#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{
    bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_project2A");
    db.setUserName("YassineJ");
    db.setPassword("root");

    if (db.open())
        test=true;

    return  test;
}
void connection::closeconnect(){db.close();}
