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

    ui->healthCardNumberValueLabel->setText(QString::number(patient->getHealthCardNumber()));
    ui->nameField->setText(patient->getName());

    switch(patient->getRequiredCareType())
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
    patient->setName(ui->nameField->text());

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
