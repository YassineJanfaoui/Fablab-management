#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menu.h"
#include "connection.h"
#include "workshop.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QTextDocument>
#include <QtCharts>
#include <QTextToSpeech>
#include <QVoice>
#include "arduino.h"



QT_BEGIN_NAMESPACE
namespace Ui { class WorkshopManagement; }
QT_END_NAMESPACE

class WorkshopManagement : public QMainWindow
{
    Q_OBJECT

public:
    WorkshopManagement(QWidget *parent = nullptr);
    ~WorkshopManagement();
    void populateComboBox();
    void populateList();
    void checkWorkshopDatetime();


private slots:

    void on_nextStack2_clicked();

    void on_nextStack1_clicked();

    void on_menu_clicked();

    void on_add_clicked();

    void on_list_doubleClicked(const QModelIndex &index);

    void on_edit_clicked();

    void on_list_clicked(const QModelIndex &index);

    void on_newest_clicked();

    void on_oldest_clicked();

    void on_reset_clicked();

    void on_pdf_clicked();

    void on_search_field_textChanged(const QString &arg1);


    void on_particip_clicked();

    void on_participationTable_doubleClicked(const QModelIndex &index);


private:
    Ui::WorkshopManagement *ui;
    Workshop temp;
    QTimer timer;
    Arduino A;

};
#endif // MAINWINDOW_H
