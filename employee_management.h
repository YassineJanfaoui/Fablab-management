#ifndef EMPLOYEE_MANAGEMENT_H
#define EMPLOYEE_MANAGEMENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Employee_management; }
QT_END_NAMESPACE

class Employee_management : public QMainWindow
{
    Q_OBJECT

public:
    Employee_management(QWidget *parent = nullptr);
    ~Employee_management();

private slots:

    void on_menu_clicked();

private:
    Ui::Employee_management *ui;
};
#endif // EMPLOYEE_MANAGEMENT_H
