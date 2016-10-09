#include "editpatientdialog.h"
#include "ui_editpatientdialog.h"

#include "patient.h"
#include "datamanager.h"

EditPatientDialog::EditPatientDialog(Patient *p, QWidget *parent) :
    QDialog(parent), ui(new Ui::EditPatientDialog), patient(p)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditPatientDialog::updatePatient);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditPatientDialog::close);

    ui->HCN->setText(QString::number(patient->getHealthCardNumber()));
    ui->firstField->setText(patient->getFirstName());
    ui->lastField->setText(patient->getLastName());

    switch(p->getReqCareType())
    {
    case AC:
        ui->ACRadio->setChecked(true);
        break;
    case CCC:
        ui->CCCRadio->setChecked(true);
        break;
    case LTC:
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
        patient->setRequiredCareType(AC);
    }
    else if(ui->CCCRadio->isChecked())
    {
        patient->setRequiredCareType(CCC);
    }
    else if(ui->LTCRadio->isChecked())
    {
        patient->setRequiredCareType(LTC);
    }

    DataManager::sharedInstance().updatePatient(*patient);
    close();
}
