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
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setCurrentUser(NULL);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentUser(User *u)
{

    currUser = u;

    if(currUser == NULL)
    {
        ui->menuTools->setDisabled(true);
        ui->actionLogout->setDisabled(true);
    }
    else
    {
        ui->menuTools->setEnabled(true);
        ui->actionLogout->setEnabled(true);

        switch(currUser->getUserType())
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
    QObject *o = s.getChosenObject();
    if(o != NULL)
    {
        Region *r = dynamic_cast<Region *>(o);
        if(r != NULL)
        {
            QWidget *oldCentralWidget = centralWidget();
            if(oldCentralWidget != NULL)
            {
                oldCentralWidget->deleteLater();
            }

            RegionFrame *regF = new RegionFrame(r);
            setCentralWidget(regF);
        }
        Location *l = dynamic_cast<Location *>(o);
        if(l != NULL)
        {
            EditFacilityDialog editFac(l, this);
            editFac.exec();
        }
        Patient * p = dynamic_cast<Patient *>(o);
        if(p != NULL)
        {
            EditPatientDialog editPat(p, this);
            editPat.exec();
        }
        User * u = dynamic_cast<User *>(o);
        if(u != NULL)
        {
            EditUserDialog editUser(u, this);
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

    LoginFrame * lf = new LoginFrame();
    setCentralWidget(lf);
}

void MainWindow::on_actionChange_Password_triggered()
{
    ChangePasswordDialog chP(currUser, this);
    chP.exec();
}
