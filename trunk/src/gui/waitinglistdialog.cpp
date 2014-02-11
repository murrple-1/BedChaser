#include "waitinglistdialog.h"
#include "ui_waitinglistdialog.h"
#include "searchwindow.h"
#include "QErrorMessage"

WaitingListDialog::WaitingListDialog(LHIN::Region * const r, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::WaitingListDialog),
        reg(r)
{
    ui->setupUi(this);
    updateWaitingList();
}

WaitingListDialog::~WaitingListDialog()
{
    delete ui;
}

void WaitingListDialog::updateWaitingList()
{
    ui->listWidget->clear();
    for(int i = 0; i < reg->getPatients().size(); i++)
    {
        ui->listWidget->addItem(QString(reg->getPatients().at(i)->toUIString().c_str()));
    }
}

void WaitingListDialog::on_addPButton_clicked()
{
    try {
        LHIN::DataManager & dm = LHIN::DataManager::getDataManager();
        std::list<LHIN::DataManager::OBJECTS> patientList;
        patientList.push_back(LHIN::DataManager::PATIENT);
        SearchWindow * sw = new SearchWindow(patientList, this);
        sw->exec();
        if(sw->getChosenObject() != NULL) {
            LHIN::Patient * p = dynamic_cast<LHIN::Patient *> (sw->getChosenObject());
            dm.addToWaitingList(*reg, *p);
            reg->addPatient(dm.getPatient(p->getHealthCardNumber()));
        }
        updateWaitingList();
        delete sw;
    }
    catch(LHIN::Exception & e) {
        QErrorMessage error(this);
        error.showMessage("One illness at a time...The patient is already in a list");
        error.exec();
    }
}

void WaitingListDialog::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    int i = ui->listWidget->row(item);
    LHIN::Patient * p = reg->getPatients().at(i);
    reg->removePatient(p->getHealthCardNumber());
    LHIN::DataManager::getDataManager().removeFromWaitingList(*reg, *p);
    updateWaitingList();
}
