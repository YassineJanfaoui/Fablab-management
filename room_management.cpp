#include "room_management.h"
#include "ui_room_management.h"
#include "menu.h"
#include "room.h"

room_management::room_management(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::room_management)
{
    ui->setupUi(this);
}

room_management::~room_management()
{
    delete ui;
}


void room_management::on_pushButton_10_clicked()
{
   menu *newWindow = new menu;
   newWindow->show();
   hide();
}
