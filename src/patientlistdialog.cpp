#include "patientlistdialog.h"
#include "ui_patientlistdialog.h"

#include "searchwindow.h"
#include "datamanager.h"

PatientListDialog::PatientListDialog(const QSharedPointer<Facility> &facility, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientListDialog)
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

    // TODO
}

void PatientListDialog::on_addPatient_clicked()
{
    SearchWindow sw;
    if(sw.exec() == SearchWindow::Accepted)
    {
        if(!sw.getChosenObject().isNull())
        {
            QSharedPointer<Patient> patient = sw.getChosenObject().dynamicCast<Patient>();
            patient->setReceivingCareFacilityId(facility->getID());
            DataManager::sharedInstance().updatePatient(*patient);

            updatePatientList();
        }
    }
}

void PatientListDialog::on_patientList_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    // TODO

    updatePatientList();
}
