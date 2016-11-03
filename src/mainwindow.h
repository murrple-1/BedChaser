#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

#include <QSharedPointer>

class User;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCurrentUser(const QSharedPointer<User> &);
private:
    Ui::MainWindow *ui;

    QSharedPointer<User> currentUser;
private slots:
    void changePassword();
    void search();
    void patientReport();
    void facilityReport();
    void addPatient();
    void addFacility();
    void addUser();
    void logout();

    void loginSuccess(const QSharedPointer<User> &);
};

#endif // MAINWINDOW_H
