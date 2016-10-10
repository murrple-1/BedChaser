#include "waitinglistdialog.h"
#include "ui_waitinglistdialog.h"

#include "searchwindow.h"
#include "patient.h"
#include "region.h"
#include "datamanager.h"

WaitingListDialog::WaitingListDialog(Region *region, QWidget *parent) :
    QDialog(parent), ui(new Ui::WaitingListDialog)
{
    ui->setupUi(this);

    this->region = region;

    updateWaitingList();
}

WaitingListDialog::~WaitingListDialog()
{
    delete ui;
}

void WaitingListDialog::updateWaitingList()
{
    ui->listWidget->clear();
    foreach(int patientId, region->getWaitingListPatientIds())
    {
        Patient *patient = DataManager::sharedInstance().getPatient(patientId);
        ui->listWidget->addItem(QString("%1 %2").arg(patient->getFirstName()).arg(patient->getLastName()));
        delete patient;
    }
}

void WaitingListDialog::on_addPButton_clicked()
{
    SearchWindow sw;
    if(sw.exec() == SearchWindow::Accepted)
    {
        if(sw.getChosenObject() != NULL)
        {
            Patient *patient = qobject_cast<Patient *>(sw.getChosenObject());
            DataManager::sharedInstance().addToWaitingList(*region, *patient);
            region->addWaitingListPatientId(patient->getHealthCardNumber());

            updateWaitingList();
        }
    }
}

void WaitingListDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int i = ui->listWidget->row(item);
    int patientId = region->getWaitingListPatientIds().at(i);
    region->removeWaitingListPatientId(i);

    Patient *patient = DataManager::sharedInstance().getPatient(patientId);
    DataManager::sharedInstance().removeFromWaitingList(*region, *patient);
    delete patient;

    updateWaitingList();
}
