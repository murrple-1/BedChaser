#include "patientlistdialog.h"
#include "ui_patientlistdialog.h"

#include "searchwindow.h"
#include "datamanager.h"

PatientListDialog::PatientListDialog(const QSharedPointer<Location> &location, QWidget *parent) :
    QDialog(parent), ui(new Ui::PatientListDialog)
{
    ui->setupUi(this);

    this->location = location;

    updatePatientList();
}

PatientListDialog::~PatientListDialog()
{
    delete ui;
}

void PatientListDialog::updatePatientList()
{
    ui->patientList->clear();

    foreach(int patientId, location->getPatientsInCareIds())
    {
        QSharedPointer<Patient> patient = DataManager::sharedInstance().getPatient(patientId);
        QString name = QString("%1 %2").arg(patient->getFirstName()).arg(patient->getLastName());
        ui->patientList->addItem(name);
    }
}

void PatientListDialog::on_addPatient_clicked()
{
    SearchWindow sw;
    if(sw.exec() == SearchWindow::Accepted)
    {
        if(!sw.getChosenObject().isNull())
        {
            QSharedPointer<Patient> patient = sw.getChosenObject().dynamicCast<Patient>();
            patient->setCareLocationId(location->getID());
            DataManager::sharedInstance().updatePatient(*patient);
            location->addPatientInCareId(patient->getHealthCardNumber());

            updatePatientList();
        }
    }
}

void PatientListDialog::on_patientList_itemDoubleClicked(QListWidgetItem *item)
{
    int i = ui->patientList->row(item);
    location->removePatientInCareId(i);
    DataManager::sharedInstance().updateLocation(*location);

    updatePatientList();
}
