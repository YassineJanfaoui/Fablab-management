#ifndef ROOM_MANAGEMENT_H
#define ROOM_MANAGEMENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class room_management; }
QT_END_NAMESPACE

class room_management : public QMainWindow
{
    Q_OBJECT

public:
    room_management(QWidget *parent = nullptr);
    ~room_management();

private slots:
    void on_pushButton_10_clicked();

private:
    Ui::room_management *ui;
};
#endif // ROOM_MANAGEMENT_H
