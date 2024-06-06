#ifndef EQUIPMENT_MANAGMENT_H
#define EQUIPMENT_MANAGMENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class equipment_managment; }
QT_END_NAMESPACE

class equipment_managment : public QMainWindow
{
    Q_OBJECT

public:
    equipment_managment(QWidget *parent = nullptr);
    ~equipment_managment();

private slots:
    void on_menu_clicked();

private:
    Ui::equipment_managment *ui;
};
#endif // EQUIPMENT_MANAGMENT_H

