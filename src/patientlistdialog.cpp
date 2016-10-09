#include "patientlistdialog.h"
#include "ui_patientlistdialog.h"

#include "searchwindow.h"
#include "datamanager.h"

PatientListDialog::PatientListDialog(Location *l, QWidget *parent) :
    QDialog(parent), ui(new Ui::PatientListDialog), loc(l)
{
    ui->setupUi(this);

    updatePatientList();
}

PatientListDialog::~PatientListDialog()
{
    delete ui;
}

void PatientListDialog::updatePatientList()
{
    ui->patientList->clear();

    foreach(int patientId, loc->getPatientsInCareIds())
    {
        Patient *patient = DataManager::sharedInstance().getPatient(patientId);
        QString name = QString("%1 %2").arg(patient->getFirstName()).arg(patient->getLastName());
        ui->patientList->addItem(name);
        delete patient;
    }
}

void PatientListDialog::on_addPatient_clicked()
{
    SearchWindow sw;
    if(sw.exec() == SearchWindow::Accepted)
    {
        if(sw.getChosenObject() != NULL)
        {
            Patient *p = dynamic_cast<Patient *>(sw.getChosenObject());
            p->setCareLocationId(loc->getID());
            DataManager::sharedInstance().updatePatient(*p);
            loc->addPatientInCareId(p->getHealthCardNumber());

            updatePatientList();
        }
    }
}

void PatientListDialog::on_patientList_itemDoubleClicked(QListWidgetItem* item)
{
    int i = ui->patientList->row(item);
    loc->removePatientInCareId(i);
    DataManager::sharedInstance().updateLocation(*loc);

    updatePatientList();
}
