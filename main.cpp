#include "WorkshopManagement.h"
#include "menu.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    bool test = c.createconnect();
    menu w;

    QIcon icon;
    QString message;

    if (test)
    {
        icon = QIcon(":/new/prefix1/icon.png");
        message = "Database connection successful.";
        w.show();
    }
    else
    {
        icon = QIcon(":/new/prefix1/error.png");
        message = "Database connection Unsuccessful!";
    }

    QSystemTrayIcon trayIcon(icon, &a);
    trayIcon.show();
    trayIcon.showMessage("FabriTech", message, QSystemTrayIcon::Information, 1000);


    return a.exec();
}
