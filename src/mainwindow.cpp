#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "user.h"
#include "patient.h"
#include "location.h"
#include "region.h"
#include "addfacilitydialog.h"
#include "addpatientdialog.h"
#include "adduserdialog.h"
#include "facilityreportdialog.h"
#include "patientreportdialog.h"
#include "searchwindow.h"
#include "editfacilitydialog.h"
#include "editpatientdialog.h"
#include "edituserdialog.h"
#include "changepassworddialog.h"
#include "loginframe.h"
#include "regionframe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), currentUser(NULL)
{
    ui->setupUi(this);

    LoginFrame *loginFrame = new LoginFrame(this);
    setCentralWidget(loginFrame);

    setCurrentUser(NULL);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentUser(User *user)
{
    currentUser = user;

    if(currentUser == NULL)
    {
        ui->menuTools->setDisabled(true);
        ui->actionLogout->setDisabled(true);
    }
    else
    {
        ui->menuTools->setEnabled(true);
        ui->actionLogout->setEnabled(true);

        switch(currentUser->getUserType())
        {
        case(STAFF):
            ui->actionAdd_User->setEnabled(false);
            ui->menuReports->setEnabled(false);
            ui->actionAdd_Facility->setEnabled(false);
            break;
        case(ADMIN):
            ui->actionAdd_User->setEnabled(false);
            ui->menuReports->setEnabled(true);
            ui->actionAdd_Facility->setEnabled(false);
            break;
        case(SYSADMIN):
            ui->actionAdd_User->setEnabled(true);
            ui->menuReports->setEnabled(true);
            ui->actionAdd_Facility->setEnabled(true);
            break;
        default:
            break;
        }
    }
}

void MainWindow::on_actionAdd_Facility_triggered()
{
    AddFacilityDialog f(this);
    f.exec();
}

void MainWindow::on_actionAdd_Patient_triggered()
{
    AddPatientDialog p(this);
    p.exec();
}

void MainWindow::on_actionAdd_User_triggered()
{
    AddUserDialog u(this);
    u.exec();
}

void MainWindow::on_actionFacility_Report_triggered()
{
    FacilityReportDialog fr(this);
    fr.exec();
}

void MainWindow::on_actionPatient_Report_triggered()
{
    PatientReportDialog pr(this);
    pr.exec();
}

void MainWindow::on_actionSearch_triggered()
{
    SearchWindow s(this);
    s.exec();
    QObject *chosenObject = s.getChosenObject();
    if(chosenObject != NULL)
    {
        Region *region = dynamic_cast<Region *>(chosenObject);
        if(region != NULL)
        {
            QWidget *oldCentralWidget = centralWidget();
            if(oldCentralWidget != NULL)
            {
                oldCentralWidget->deleteLater();
            }

            RegionFrame *regF = new RegionFrame(region);
            setCentralWidget(regF);
        }
        Location *location = dynamic_cast<Location *>(chosenObject);
        if(location != NULL)
        {
            EditFacilityDialog editFac(location, this);
            editFac.exec();
        }
        Patient *patient = dynamic_cast<Patient *>(chosenObject);
        if(patient != NULL)
        {
            EditPatientDialog editPat(patient, this);
            editPat.exec();
        }
        User *user = dynamic_cast<User *>(chosenObject);
        if(user != NULL)
        {
            EditUserDialog editUser(user, this);
            editUser.exec();
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionLogout_triggered()
{
    MainWindow::setCurrentUser(NULL);
    QWidget *oldCentralWidget = centralWidget();
    if(oldCentralWidget != NULL)
    {
        oldCentralWidget->deleteLater();
    }

    LoginFrame *loginFrame = new LoginFrame(this);
    setCentralWidget(loginFrame);
}

void MainWindow::on_actionChange_Password_triggered()
{
    ChangePasswordDialog chP(currentUser, this);
    chP.exec();
}
