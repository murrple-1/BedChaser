#include "editpatientdialog.h"
#include "ui_editpatientdialog.h"
#include "../core/datamanager.h"
#include "iostream"

EditPatientDialog::EditPatientDialog(LHIN::Patient * const p, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::EditPatientDialog),
        patient(p)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(updatePatient()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    ui->HCN->setText(QString::number(patient->getHealthCardNumber()));
    ui->firstField->setText(QString(patient->getFirstName().c_str()));
    ui->lastField->setText(QString(patient->getLastName().c_str()));

    switch(p->getReqCareType())
    {
    case LHIN::AC:
        ui->ACRadio->setChecked(true);
        break;
    case LHIN::CCC:
        ui->CCCRadio->setChecked(true);
        break;
    case LHIN::LTC:
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

void EditPatientDialog::updatePatient() {
    patient->setFirstName(ui->firstField->text().toStdString());
    patient->setLastName(ui->lastField->text().toStdString());

    if(ui->ACRadio->isChecked())
        patient->setReqCareType(LHIN::AC);

    else if(ui->CCCRadio->isChecked())
        patient->setReqCareType(LHIN::CCC);

    else if(ui->LTCRadio->isChecked())
        patient->setReqCareType(LHIN::LTC);

    LHIN::DataManager::getDataManager().updatePatient(*patient);
    close();
}
