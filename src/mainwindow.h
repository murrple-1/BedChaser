#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class User;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCurrentUser(User *);
private:
    Ui::MainWindow *ui;

    User *currentUser;
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
