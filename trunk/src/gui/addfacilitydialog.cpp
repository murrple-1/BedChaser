#include "addfacilitydialog.h"
#include "ui_addfacilitydialog.h"
#include "../core/datamanager.h"
#include "../core/locationobject.h"
#include "../utils/hasher.h"
#include "qerrormessage.h"

AddFacilityDialog::AddFacilityDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::AddFacilityDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(addFacility()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

AddFacilityDialog::~AddFacilityDialog()
{
    delete ui;
}

void AddFacilityDialog::addFacility() {
    LHIN::LocationObject l(LHIN::hash(ui->nameField->text().toStdString()), ui->nameField->text().toStdString(), ui->xSpin->value(), ui->ySpin->value(), ui->ACSpin->value(), ui->CCCSpin->value(), ui->LTCSpin->value());
    l.setRegion(LHIN::DataManager::getDataManager().getRegion(ui->regiobox->currentIndex()));
    try {
        LHIN::DataManager::getDataManager().addLocation(l);
        close();
    }
    catch(LHIN::Exception & e) {
        QErrorMessage error(this);
        error.showMessage("Wouldn't it be cool to duplicate facilities...");
        error.exec();
    }
}
