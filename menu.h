#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class menu; }
QT_END_NAMESPACE

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_workshops_clicked();

    void on_employees_clicked();

    void on_clients_clicked();

    void on_equipment_clicked();

    void on_rooms_clicked();

    void on_projects_clicked();

private:
    Ui::menu *ui;
};

#endif // MENU_H
