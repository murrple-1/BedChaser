#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addfacilitydialog.h"
#include "addpatientdialog.h"
#include "adduserdialog.h"
#include "editfacilitydialog.h"
#include "editpatientdialog.h"
#include "edituserdialog.h"
#include "facilityreportdialog.h"
#include "patientreportdialog.h"
#include "changepassworddialog.h"
#include "searchwindow.h"
#include "graphicsthread.h"
#include "loginframe.h"
#include "regionframe.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setCurrentUser(NULL);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentUser(LHIN::User * const u) {

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
        case(LHIN::STAFF):
            ui->actionAdd_User->setEnabled(false);
            ui->menuReports->setEnabled(false);
            ui->actionAdd_Facility->setEnabled(false);
            break;
        case(LHIN::ADMIN):
            ui->actionAdd_User->setEnabled(false);
            ui->menuReports->setEnabled(true);
            ui->actionAdd_Facility->setEnabled(false);
            break;
        case(LHIN::SYSADMIN):
            ui->actionAdd_User->setEnabled(true);
            ui->menuReports->setEnabled(true);
            ui->actionAdd_Facility->setEnabled(true);
            break;
        default:
            break;
        }
    }
}

//Actions to open the tools menus
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
    FacilityReportDialog fr(NULL, std::vector<LHIN::Memento*>(), this);
    fr.exec();
}

void MainWindow::on_actionPatient_Report_triggered()
{
    PatientReportDialog pr(this);
    pr.exec();
}

void MainWindow::on_actionSearch_triggered()
{
    std::list<LHIN::DataManager::OBJECTS> ls;

    switch(currUser->getUserType())
    {
    case(LHIN::STAFF):
        ls.push_back(LHIN::DataManager::REGION);
        ls.push_back(LHIN::DataManager::LOCATION);
        ls.push_back(LHIN::DataManager::PATIENT);
        break;
    case(LHIN::ADMIN):
        ls.push_back(LHIN::DataManager::REGION);
        ls.push_back(LHIN::DataManager::LOCATION);
        ls.push_back(LHIN::DataManager::PATIENT);
        break;
    case(LHIN::SYSADMIN):
        ls.push_back(LHIN::DataManager::REGION);
        ls.push_back(LHIN::DataManager::LOCATION);
        ls.push_back(LHIN::DataManager::PATIENT);
        ls.push_back(LHIN::DataManager::USER);
        break;
    default:
        break;
    }

    SearchWindow s(ls, this);
    s.exec();
    LHIN::Object * o = s.getChosenObject();
    if(o != NULL)
    {
        LHIN::Region * r = dynamic_cast<LHIN::Region *>(o);
        if(r != NULL)
        {
            delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
            RegionFrame * regF = new RegionFrame(r);
            LHIN::GraphicsThread::setCurrentWindowView(regF);
        }
        LHIN::Location * l = dynamic_cast<LHIN::Location *>(o);
        if(l != NULL)
        {
            EditFacilityDialog editFac(l, this);
            editFac.exec();
        }
        LHIN::Patient * p = dynamic_cast<LHIN::Patient *>(o);
        if(p != NULL)
        {
            EditPatientDialog editPat(p, this);
            editPat.exec();
        }
        LHIN::User * u = dynamic_cast<LHIN::User *>(o);
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
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    LoginFrame * lf = new LoginFrame();
    LHIN::GraphicsThread::setCurrentWindowView(lf);
}

void MainWindow::on_actionChange_Password_triggered()
{
    ChangePasswordDialog chP(currUser, this);
    chP.exec();
}
