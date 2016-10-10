#include "editpatientdialog.h"
#include "ui_editpatientdialog.h"

#include "patient.h"
#include "datamanager.h"

EditPatientDialog::EditPatientDialog(const QSharedPointer<Patient> &patient, QWidget *parent) :
    QDialog(parent), ui(new Ui::EditPatientDialog)
{
    ui->setupUi(this);

    this->patient = patient;

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditPatientDialog::updatePatient);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditPatientDialog::close);

    ui->HCN->setText(QString::number(patient->getHealthCardNumber()));
    ui->firstField->setText(patient->getFirstName());
    ui->lastField->setText(patient->getLastName());

    switch(patient->getReqCareType())
    {
    case CareTypeAcuteCare:
        ui->ACRadio->setChecked(true);
        break;
    case CareTypeComplexContinuingCare:
        ui->CCCRadio->setChecked(true);
        break;
    case CareTypeLongTermCare:
        ui->LTCRadio->setChecked(true);
        break;
    default:
        break;
    }
}

EditPatientDialog::~EditPatientDialog()
{
    delete ui;
}

void EditPatientDialog::updatePatient()
{
    patient->setFirstName(ui->firstField->text());
    patient->setLastName(ui->lastField->text());

    if(ui->ACRadio->isChecked())
    {
        patient->setRequiredCareType(CareTypeAcuteCare);
    }
    else if(ui->CCCRadio->isChecked())
    {
        patient->setRequiredCareType(CareTypeComplexContinuingCare);
    }
    else if(ui->LTCRadio->isChecked())
    {
        patient->setRequiredCareType(CareTypeLongTermCare);
    }

    DataManager::sharedInstance().updatePatient(*patient);
    close();
}
