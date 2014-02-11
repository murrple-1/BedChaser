#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"
#include "../core/datamanager.h"
#include "../core/patientobject.h"
#include "QErrorMessage"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::AddPatientDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(addPatient()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

AddPatientDialog::~AddPatientDialog()
{
    delete ui;
}

void AddPatientDialog::addPatient() {

    LHIN::DataManager & dm = LHIN::DataManager::getDataManager();
    QList<QListWidgetItem *> items = ui->waitinglist->selectedItems();

    LHIN::PatientObject * p = new LHIN::PatientObject(ui->hcnField->text().toInt(),ui->firstField->text().toStdString(),ui->lastField->text().toStdString(),LHIN::NONE);

    if(ui->ACRadio->isChecked())
    {
        p->setReqCareType(LHIN::AC);
    }
    else if(ui->CCCRadio->isChecked())
    {
        p->setReqCareType(LHIN::CCC);
    }
    else if(ui->LTCRadio->isChecked())
    {
        p->setReqCareType(LHIN::LTC);
    }

    try {
        LHIN::DataManager::getDataManager().addPatient(*p);
        for(int i=0; i < items.size(); i++) {
            LHIN::Region * r = LHIN::DataManager::getDataManager().getRegion(ui->waitinglist->row(items.at(i)));
            p->addRegion(r);
            dm.addToWaitingList(*r, *p);
        }
        close();
    }
    catch(LHIN::Exception &) {
        QErrorMessage error(this);
        error.showMessage("Cloning people is illegal!");
        error.exec();
    }

    delete p;
}
