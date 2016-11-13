#include "editpatientdialog.h"
#include "ui_editpatientdialog.h"

#include "patient.h"
#include "datamanager.h"

EditPatientDialog::EditPatientDialog(const QSharedPointer<Patient> &patient, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::EditPatientDialog)
{
    ui->setupUi(this);

    this->patient = patient;

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditPatientDialog::updatePatient);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditPatientDialog::close);

    ui->healthCardNumberValueLabel->setText(QString::number(patient->getHealthCardNumber()));
    ui->nameLineEdit->setText(patient->getName());

    switch(patient->getRequiredCareType())
    {
    case CareTypeAcuteCare:
        ui->acuteCareRadioButton->setChecked(true);
        break;
    case CareTypeComplexContinuingCare:
        ui->complexContinuingCareRadioButton->setChecked(true);
        break;
    case CareTypeLongTermCare:
        ui->longTermCareRadioButton->setChecked(true);
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
    patient->setName(ui->nameLineEdit->text());

    if(ui->acuteCareRadioButton->isChecked())
    {
        patient->setRequiredCareType(CareTypeAcuteCare);
    }
    else if(ui->complexContinuingCareRadioButton->isChecked())
    {
        patient->setRequiredCareType(CareTypeComplexContinuingCare);
    }
    else if(ui->longTermCareRadioButton->isChecked())
    {
        patient->setRequiredCareType(CareTypeLongTermCare);
    }

    DataManager::sharedInstance().updatePatient(*patient);
    close();
}
