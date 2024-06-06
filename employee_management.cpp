#include "employee_management.h"
#include "ui_employee_management.h"
#include "menu.h"
Employee_management::Employee_management(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Employee_management)
{
    ui->setupUi(this);
}

Employee_management::~Employee_management()
{
    delete ui;
}




void Employee_management::on_menu_clicked()
{
    menu *newWindow = new menu;
   newWindow->show();
   hide();
}
