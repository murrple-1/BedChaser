#include "editfacilitydialog.h"
#include "ui_editfacilitydialog.h"
#include "../core/datamanager.h"
#include "iostream"
#include "patientlistdialog.h"

EditFacilityDialog::EditFacilityDialog(LHIN::Location * const l, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::EditFacilityDialog),
        location(l)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateFacility()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    ui->ACSpin->setValue(location->getACBeds());
    ui->LTCSpin->setValue(location->getLTCBeds());
    ui->CCCSpin->setValue(location->getCCCBeds());
    ui->name->setText(QString(location->getName().c_str()));
    ui->x->setNum(location->getX());
    ui->y->setNum(location->getY());
}

EditFacilityDialog::~EditFacilityDialog()
{
    delete ui;
}

void EditFacilityDialog::updateFacility() {

    try {
        location->setACBeds(ui->ACSpin->value());
        location->setCCCBeds(ui->CCCSpin->value());
        location->setLTCBeds(ui->LTCSpin->value());
        location->setName(ui->name->text().toStdString());
        location->setX(ui->x->text().toInt());
        location->setY(ui->y->text().toInt());

        LHIN::DataManager::getDataManager().updateLocation(*location);
    }
    catch(LHIN::Exception & e) {
        std::cout << "Message: " << e.getMessage() << "Cause: " << e.getCause();
    }

    close();
}

void EditFacilityDialog::on_patientlist_clicked()
{
    PatientListDialog * wf = new PatientListDialog(location, this);
    wf->exec();
    delete wf;
}
