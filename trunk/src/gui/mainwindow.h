#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../core/user.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setCurrentUser(LHIN::User * const);

private:
    Ui::MainWindow *ui;
    LHIN::User * currUser;
private slots:
    void on_actionChange_Password_triggered();
    void on_actionSearch_triggered();
    void on_actionPatient_Report_triggered();
    void on_actionFacility_Report_triggered();
    void on_actionAdd_Patient_triggered();
    void on_actionAdd_Facility_triggered();
    void on_actionAdd_User_triggered();
    void on_actionExit_triggered();
    void on_actionLogout_triggered();
};

#endif // MAINWINDOW_H
