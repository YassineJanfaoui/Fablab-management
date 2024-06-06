#include "equipment_managment.h"
#include "ui_equipment_managment.h"
#include "menu.h"

equipment_managment::equipment_managment(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::equipment_managment)
{
    ui->setupUi(this);
}

equipment_managment::~equipment_managment()
{
    delete ui;
}


void equipment_managment::on_menu_clicked()
{
    menu *newWindow = new menu;
    newWindow->show();
    hide();
}
