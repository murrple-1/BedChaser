#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

#include "datamanager.h"
#include "patient.h"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AddPatientDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(addPatient()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

AddPatientDialog::~AddPatientDialog()
{
    delete ui;
}

void AddPatientDialog::addPatient()
{
    QList<QListWidgetItem *> items = ui->waitinglist->selectedItems();

    Patient p(ui->hcnField->text().toInt(), ui->firstField->text(),ui->lastField->text(), NONE);

    if(ui->ACRadio->isChecked())
    {
        p.setRequiredCareType(AC);
    }
    else if(ui->CCCRadio->isChecked())
    {
        p.setRequiredCareType(CCC);
    }
    else if(ui->LTCRadio->isChecked())
    {
        p.setRequiredCareType(LTC);
    }

    DataManager::sharedInstance().addPatient(p);
    for(int i = 0; i < items.size(); i++)
    {
        Region *r = DataManager::sharedInstance().getRegion(ui->waitinglist->row(items.at(i)));
        p.addWaitingRegionId(r->getID());
        DataManager::sharedInstance().addToWaitingList(*r, p);
    }
    close();
}
