#ifndef PROJECTSMANAGEMENT_H
#define PROJECTSMANAGEMENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ProjectsManagement; }
QT_END_NAMESPACE

class ProjectsManagement : public QMainWindow
{
    Q_OBJECT

public:
    ProjectsManagement(QWidget *parent = nullptr);
    ~ProjectsManagement();

private slots:

    void on_menu_clicked();

private:
    Ui::ProjectsManagement *ui;
};

#endif // PROJECTSMANAGEMENT_H
