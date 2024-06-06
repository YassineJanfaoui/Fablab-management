#include "menu.h"
#include "ui_menu.h"
#include "WorkshopManagement.h"
#include "employee_management.h"
#include "clientmanagement.h"
#include "equipment_managment.h"
#include "room_management.h"
#include "projectsmanagement.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_workshops_clicked()
{
    WorkshopManagement *newWindow = new WorkshopManagement;
       newWindow->show();
       hide();
}

void menu::on_employees_clicked()
{
    Employee_management *newWindow = new Employee_management;
       newWindow->show();
       hide();
}

void menu::on_clients_clicked()
{
    ClientManagement *newWindow = new ClientManagement;
       newWindow->show();
       hide();
}


void menu::on_equipment_clicked()
{
    equipment_managment *newWindow = new equipment_managment;
       newWindow->show();
       hide();
}

void menu::on_rooms_clicked()
{
    room_management *newWindow = new room_management;
       newWindow->show();
       hide();
}

void menu::on_projects_clicked()
{
    ProjectsManagement *newWindow = new ProjectsManagement;
       newWindow->show();
       hide();
}
