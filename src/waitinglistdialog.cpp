#include "waitinglistdialog.h"
#include "ui_waitinglistdialog.h"

#include "searchwindow.h"
#include "patient.h"
#include "region.h"
#include "datamanager.h"

WaitingListDialog::WaitingListDialog(const QSharedPointer<Region> &region, QWidget *parent) :
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
        QSharedPointer<Patient> patient = DataManager::sharedInstance().getPatient(patientId);
        ui->listWidget->addItem(QString("%1 %2").arg(patient->getFirstName()).arg(patient->getLastName()));
    }
}

void WaitingListDialog::on_addPButton_clicked()
{
    SearchWindow sw;
    if(sw.exec() == SearchWindow::Accepted)
    {
        if(!sw.getChosenObject().isNull())
        {
            QSharedPointer<Patient> patient = sw.getChosenObject().dynamicCast<Patient>();
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

    QSharedPointer<Patient> patient = DataManager::sharedInstance().getPatient(patientId);
    DataManager::sharedInstance().removeFromWaitingList(*region, *patient);

    updateWaitingList();
}
