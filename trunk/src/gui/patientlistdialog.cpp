#include "patientlistdialog.h"
#include "ui_patientlistdialog.h"
#include "searchwindow.h"
#include "../core/patientobject.h"
#include "../core/patientproxy.h"

PatientListDialog::PatientListDialog(LHIN::Location * const l, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::PatientListDialog),
        loc(l)
{
    ui->setupUi(this);
    updatePatientList();
}

PatientListDialog::~PatientListDialog()
{
    delete ui;
}

void PatientListDialog::updatePatientList()
{
    ui->patientList->clear();
    for(int i = 0; i < loc->getPatientList().size(); i++) {
        ui->patientList->addItem(QString(loc->getPatientList().at(i)->toUIString().c_str()));
    }
}

void PatientListDialog::on_addPatient_clicked()
{
    LHIN::DataManager & dm = LHIN::DataManager::getDataManager();
    std::list<LHIN::DataManager::OBJECTS> patientList;
    patientList.push_back(LHIN::DataManager::PATIENT);
    SearchWindow * sw = new SearchWindow(patientList, this);
    sw->exec();
    if(sw->getChosenObject() != NULL) {
        LHIN::Patient * p = dynamic_cast<LHIN::Patient *> (sw->getChosenObject());
        p->setCareLocation(dm.getDataManager().getLocation(loc->getID()));
        dm.updatePatient(*p);
        loc->addPatient(dm.getPatient(p->getHealthCardNumber()));
    }
    updatePatientList();
    delete sw;
}

void PatientListDialog::on_patientList_itemDoubleClicked(QListWidgetItem* item)
{
    int i = ui->patientList->row(item);
    LHIN::Patient * p = loc->getPatientList().at(i);
    loc->removePatient(p->getHealthCardNumber());
    p->setCareLocation(NULL);
    LHIN::DataManager::getDataManager().updateLocation(*loc);
    LHIN::DataManager::getDataManager().updatePatient(*p);
    updatePatientList();
}
