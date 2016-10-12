#include "patientlistdialog.h"
#include "ui_patientlistdialog.h"

#include "searchwindow.h"
#include "datamanager.h"

PatientListDialog::PatientListDialog(const QSharedPointer<Facility> &facility, QWidget *parent) :
    QDialog(parent), ui(new Ui::PatientListDialog)
{
    ui->setupUi(this);

    this->facility = facility;

    updatePatientList();
}

PatientListDialog::~PatientListDialog()
{
    delete ui;
}

void PatientListDialog::updatePatientList()
{
    ui->patientList->clear();

    foreach(int patientId, facility->getPatientsInCareIds())
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
            patient->setCareFacilityId(facility->getID());
            DataManager::sharedInstance().updatePatient(*patient);
            facility->addPatientInCareId(patient->getHealthCardNumber());

            updatePatientList();
        }
    }
}

void PatientListDialog::on_patientList_itemDoubleClicked(QListWidgetItem *item)
{
    int i = ui->patientList->row(item);
    facility->removePatientInCareId(i);
    DataManager::sharedInstance().updateFacility(*facility);

    updatePatientList();
}
