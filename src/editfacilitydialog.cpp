#include "editfacilitydialog.h"
#include "ui_editfacilitydialog.h"

#include "patientlistdialog.h"
#include "location.h"
#include "datamanager.h"
#include "exception.h"

EditFacilityDialog::EditFacilityDialog(Location *location, QWidget *parent) :
    QDialog(parent), ui(new Ui::EditFacilityDialog)
{
    ui->setupUi(this);

    this->location = location;

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditFacilityDialog::updateFacility);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditFacilityDialog::close);

    ui->ACSpin->setValue(location->getACBeds());
    ui->LTCSpin->setValue(location->getLTCBeds());
    ui->CCCSpin->setValue(location->getCCCBeds());
    ui->name->setText(location->getName());
    ui->x->setNum(location->getX());
    ui->y->setNum(location->getY());
}

EditFacilityDialog::~EditFacilityDialog()
{
    delete ui;
}

void EditFacilityDialog::updateFacility()
{
    try
    {
        location->setACBeds(ui->ACSpin->value());
        location->setCCCBeds(ui->CCCSpin->value());
        location->setLTCBeds(ui->LTCSpin->value());
        location->setName(ui->name->text());
        location->setX(ui->x->text().toInt());
        location->setY(ui->y->text().toInt());

        DataManager::sharedInstance().updateLocation(*location);
    }
    catch(Exception &e)
    {
        // TODO
    }

    close();
}

void EditFacilityDialog::on_patientlist_clicked()
{
    PatientListDialog wf(location, this);
    wf.exec();
}
