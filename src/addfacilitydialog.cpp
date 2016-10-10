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
    Location location(ui->nameField->text(), ui->nameField->text(), ui->xSpinBox->value(), ui->ySpinBox->value(), ui->acuteCareSpinBox->value(), ui->complexContinuingCareSpinBox->value(), ui->longTermCareSpinBox->value());
    location.setRegionId(ui->regionComboBox->currentIndex());

    DataManager::sharedInstance().addLocation(location);
    close();
}
