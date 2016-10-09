#include "waitinglistdialog.h"
#include "ui_waitinglistdialog.h"

#include "searchwindow.h"
#include "patient.h"
#include "region.h"
#include "datamanager.h"

WaitingListDialog::WaitingListDialog(Region * r, QWidget *parent) :
    QDialog(parent), ui(new Ui::WaitingListDialog), reg(r)
{
    ui->setupUi(this);

    updateWaitingList();
}

WaitingListDialog::~WaitingListDialog()
{
    delete ui;
}

void WaitingListDialog::updateWaitingList()
{
    ui->listWidget->clear();
    foreach(int patientId, reg->getWaitingListPatientIds())
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
            Patient *p = qobject_cast<Patient *>(sw.getChosenObject());
            DataManager::sharedInstance().addToWaitingList(*reg, *p);
            reg->addWaitingListPatientId(p->getHealthCardNumber());

            updateWaitingList();
        }
    }
}

void WaitingListDialog::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    int i = ui->listWidget->row(item);
    int patientId = reg->getWaitingListPatientIds().at(i);
    reg->removeWaitingListPatientId(i);

    Patient *patient = DataManager::sharedInstance().getPatient(patientId);
    DataManager::sharedInstance().removeFromWaitingList(*reg, *patient);
    delete patient;

    updateWaitingList();
}
