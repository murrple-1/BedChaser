#include "addfacilitydialog.h"
#include "ui_addfacilitydialog.h"

#include "datamanager.h"
#include "facility.h"

AddFacilityDialog::AddFacilityDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::AddFacilityDialog)
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
    Facility facility(QVariant(), ui->nameField->text(), QPoint(ui->xSpinBox->value(), ui->ySpinBox->value()), ui->acuteCareSpinBox->value(), ui->complexContinuingCareSpinBox->value(), ui->longTermCareSpinBox->value(), ui->regionComboBox->currentIndex());
    DataManager::sharedInstance().addFacility(facility);
    close();
}
