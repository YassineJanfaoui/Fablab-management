#ifndef CLIENTMANAGEMENT_H
#define CLIENTMANAGEMENT_H

#include <QMainWindow>
#include <QMainWindow>
#include "menu.h"
#include "connection.h"
#include "client.h"
#include <QDebug>
#include <QMessageBox>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientManagement; }
QT_END_NAMESPACE

class ClientManagement : public QMainWindow
{
    Q_OBJECT

public:
    ClientManagement(QWidget *parent = nullptr);
    ~ClientManagement();
    void populateList();
    void ControlInput();
    void setupChart();
    void removePieChartFrame(QFrame* frame);

private slots:
    void on_pushButton_10_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_edit_client_clicked();

    void on_add_client_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_reset_client_clicked();

    void on_Newest_clicked();

    void on_Oldest_clicked();

    void on_Refresh_clicked();

    void on_Search_clicked();

    void on_PDF_clicked();


    void on_Chart_clicked();

private:
    Ui::ClientManagement *ui;
    Client temp;
    Arduino A, ard;
};
#endif // CLIENTMANAGEMENT_H
