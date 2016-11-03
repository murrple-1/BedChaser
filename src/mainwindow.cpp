#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "user.h"
#include "patient.h"
#include "facility.h"
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
#include "mapframe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LoginFrame *loginFrame = new LoginFrame(this);
    connect(loginFrame, &LoginFrame::loginSuccess, this, &MainWindow::loginSuccess);
    setCentralWidget(loginFrame);

    setCurrentUser(QSharedPointer<User>());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentUser(const QSharedPointer<User> &user)
{
    currentUser = user;

    if(currentUser.isNull())
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
        case(UserTypeStaff):
            ui->actionAdd_User->setEnabled(false);
            ui->menuReports->setEnabled(false);
            ui->actionAdd_Facility->setEnabled(false);
            break;
        case(UserTypeAdmin):
            ui->actionAdd_User->setEnabled(false);
            ui->menuReports->setEnabled(true);
            ui->actionAdd_Facility->setEnabled(false);
            break;
        case(UserTypeSystemAdmin):
            ui->actionAdd_User->setEnabled(true);
            ui->menuReports->setEnabled(true);
            ui->actionAdd_Facility->setEnabled(true);
            break;
        default:
            break;
        }
    }
}

void MainWindow::loginSuccess(const QSharedPointer<User> &user)
{
    centralWidget()->deleteLater();

    MapFrame *mapFrame = new MapFrame(this);
    setCentralWidget(mapFrame);

    setCurrentUser(user);
}

void MainWindow::addFacility()
{
    AddFacilityDialog f(this);
    f.exec();
}

void MainWindow::addPatient()
{
    AddPatientDialog p(this);
    p.exec();
}

void MainWindow::addUser()
{
    AddUserDialog u(this);
    u.exec();
}

void MainWindow::facilityReport()
{
    FacilityReportDialog fr(this);
    fr.exec();
}

void MainWindow::patientReport()
{
    PatientReportDialog pr(this);
    pr.exec();
}

void MainWindow::search()
{
    SearchWindow s(this);
    s.exec();
    const QSharedPointer<QObject> &chosenObject = s.getChosenObject();
    if(!chosenObject.isNull())
    {
        QSharedPointer<Region> region = chosenObject.dynamicCast<Region>();
        if(!region.isNull())
        {
            QWidget *oldCentralWidget = centralWidget();
            if(oldCentralWidget != NULL)
            {
                oldCentralWidget->deleteLater();
            }

            RegionFrame *regF = new RegionFrame(region, this);
            setCentralWidget(regF);
        }
        QSharedPointer<Facility> facility = chosenObject.dynamicCast<Facility>();
        if(!facility.isNull())
        {
            EditFacilityDialog editFac(facility, this);
            editFac.exec();
        }
        QSharedPointer<Patient> patient = chosenObject.dynamicCast<Patient>();
        if(!patient.isNull())
        {
            EditPatientDialog editPat(patient, this);
            editPat.exec();
        }
        QSharedPointer<User> user = chosenObject.dynamicCast<User>();
        if(!user.isNull())
        {
            EditUserDialog editUser(user, this);
            editUser.exec();
        }
    }
}

void MainWindow::logout()
{
    MainWindow::setCurrentUser(QSharedPointer<User>());
    QWidget *oldCentralWidget = centralWidget();
    if(oldCentralWidget != NULL)
    {
        oldCentralWidget->deleteLater();
    }

    LoginFrame *loginFrame = new LoginFrame(this);
    setCentralWidget(loginFrame);
}

void MainWindow::changePassword()
{
    ChangePasswordDialog chP(currentUser, this);
    chP.exec();
}
