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

    connect(ui->changePasswordAction, &QAction::triggered, this, &MainWindow::showChangePasswordDialog);
    connect(ui->searchAction, &QAction::triggered, this, &MainWindow::showSearchDialog);
    connect(ui->patientReportAction, &QAction::triggered, this, &MainWindow::showPatientReportDialog);
    connect(ui->facilityReportAction, &QAction::triggered, this, &MainWindow::showFacilityReportDialog);
    connect(ui->addPatientAction, &QAction::triggered, this, &MainWindow::showAddPatientDialog);
    connect(ui->addFacilityAction, &QAction::triggered, this, &MainWindow::showAddFacilityDialog);
    connect(ui->addUserAction, &QAction::triggered, this, &MainWindow::showAddUserDialog);
    connect(ui->logoutAction, &QAction::triggered, this, &MainWindow::logout);

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
        ui->toolsMenu->setDisabled(true);
        ui->logoutAction->setDisabled(true);
    }
    else
    {
        ui->toolsMenu->setEnabled(true);
        ui->logoutAction->setEnabled(true);

        UserType userType = currentUser->getType();

        ui->addUserAction->setEnabled(userType >= UserTypeSystemAdmin);
        ui->reportsMenu->setEnabled(userType >= UserTypeAdmin);
        ui->addFacilityAction->setEnabled(userType >= UserTypeSystemAdmin);
    }
}

void MainWindow::loginSuccess(const QSharedPointer<User> &user)
{
    goToMap();
    setCurrentUser(user);
}

void MainWindow::goToMap()
{
    QWidget *prevCentralWidget = centralWidget();
    if(prevCentralWidget != NULL)
    {
        prevCentralWidget->deleteLater();
    }

    MapFrame *mapFrame = new MapFrame(this);
    connect(mapFrame, &MapFrame::regionSelected, this, &MainWindow::regionSelected);
    setCentralWidget(mapFrame);
}

void MainWindow::showAddFacilityDialog()
{
    AddFacilityDialog addFacilityDialog(this);
    addFacilityDialog.exec();
}

void MainWindow::showAddPatientDialog()
{
    AddPatientDialog addPatientDialog(this);
    addPatientDialog.exec();
}

void MainWindow::showAddUserDialog()
{
    AddUserDialog addUserDialog(this);
    addUserDialog.exec();
}

void MainWindow::showFacilityReportDialog()
{
    FacilityReportDialog facilityReportDialog(this);
    facilityReportDialog.exec();
}

void MainWindow::showPatientReportDialog()
{
    PatientReportDialog patientReportDialog(this);
    patientReportDialog.exec();
}

void MainWindow::showSearchDialog()
{
    SearchWindow searchWindow(currentUser->getType(), this);
    searchWindow.exec();

    const QSharedPointer<QObject> &chosenObject = searchWindow.getChosenObject();
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

            RegionFrame *regionFrame = new RegionFrame(region, this);
            setCentralWidget(regionFrame);
            return;
        }

        QSharedPointer<Facility> facility = chosenObject.dynamicCast<Facility>();
        if(!facility.isNull())
        {
            EditFacilityDialog editFacilityDialog(facility, this);
            editFacilityDialog.exec();
            return;
        }

        QSharedPointer<Patient> patient = chosenObject.dynamicCast<Patient>();
        if(!patient.isNull())
        {
            EditPatientDialog editPatientDialog(patient, this);
            editPatientDialog.exec();
            return;
        }

        QSharedPointer<User> user = chosenObject.dynamicCast<User>();
        if(!user.isNull())
        {
            EditUserDialog editUserDialog(user, this);
            editUserDialog.exec();
            return;
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
    connect(loginFrame, &LoginFrame::loginSuccess, this, &MainWindow::loginSuccess);
    setCentralWidget(loginFrame);
}

void MainWindow::showChangePasswordDialog()
{
    ChangePasswordDialog changePasswordDialog(currentUser, this);
    changePasswordDialog.exec();
}

void MainWindow::regionSelected(const QSharedPointer<Region> &region)
{
    QWidget *oldCentralWidget = centralWidget();
    if(oldCentralWidget != NULL)
    {
        oldCentralWidget->deleteLater();
    }

    RegionFrame *regionFrame = new RegionFrame(region, this);
    connect(regionFrame, &RegionFrame::goBack, this, &MainWindow::goToMap);
    setCentralWidget(regionFrame);
}
