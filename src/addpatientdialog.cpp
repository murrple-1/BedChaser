#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

#include "datamanager.h"
#include "patient.h"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatientDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddPatientDialog::addPatient);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddPatientDialog::close);
}

AddPatientDialog::~AddPatientDialog()
{
    delete ui;
}

void AddPatientDialog::addPatient()
{
    CareType requiredCare = CareTypeNone;
    if(ui->acuteCareRadioButton->isChecked())
    {
        requiredCare = CareTypeAcuteCare;
    }
    else if(ui->complexContinuingCareRadioButton->isChecked())
    {
        requiredCare = CareTypeComplexContinuingCare;
    }
    else if(ui->longTermCareRadioButton->isChecked())
    {
        requiredCare = CareTypeLongTermCare;
    }

    Patient p(QVariant(), ui->healthCareNumberLineEdit->text().toInt(), ui->nameLineEdit->text(), requiredCare, CareTypeNone, QVariant(), QDateTime());

    DataManager::sharedInstance().addPatient(p);

    QList<QListWidgetItem *> items = ui->waitingListListWidget->selectedItems();
    // TODO add patient to region waiting lists
    close();
}
