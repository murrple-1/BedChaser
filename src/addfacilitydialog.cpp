#include "addfacilitydialog.h"
#include "ui_addfacilitydialog.h"

#include "datamanager.h"
#include "location.h"

AddFacilityDialog::AddFacilityDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AddFacilityDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddFacilityDialog::addFacility);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddFacilityDialog::close);
}

AddFacilityDialog::~AddFacilityDialog()
{
    delete ui;
}

void AddFacilityDialog::addFacility()
{
    Location l(ui->nameField->text(), ui->nameField->text(), ui->xSpin->value(), ui->ySpin->value(), ui->ACSpin->value(), ui->CCCSpin->value(), ui->LTCSpin->value());
    l.setRegionId(ui->regiobox->currentIndex());

    DataManager::sharedInstance().addLocation(l);
    close();
}
