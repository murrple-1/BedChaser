#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

#include "datamanager.h"
#include "patient.h"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AddPatientDialog)
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
    QList<QListWidgetItem *> items = ui->waitingListListWidget->selectedItems();

    Patient p(ui->healthCareNumberLineEdit->text().toInt(), ui->firstNameLineEdit->text(),ui->lastNameLineEdit->text(), CareTypeNone);

    if(ui->acuteCareRadioButton->isChecked())
    {
        p.setRequiredCareType(CareTypeAcuteCare);
    }
    else if(ui->complexContinuingCareRadioButton->isChecked())
    {
        p.setRequiredCareType(CareTypeComplexContinuingCare);
    }
    else if(ui->longTermCareRadioButton->isChecked())
    {
        p.setRequiredCareType(CareTypeLongTermCare);
    }

    DataManager::sharedInstance().addPatient(p);
    for(int i = 0; i < items.size(); i++)
    {
        Region *region = DataManager::sharedInstance().getRegion(ui->waitingListListWidget->row(items.at(i)));
        p.addWaitingRegionId(region->getID());
        DataManager::sharedInstance().addToWaitingList(*region, p);
    }
    close();
}
