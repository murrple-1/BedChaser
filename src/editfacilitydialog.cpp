#include "editfacilitydialog.h"
#include "ui_editfacilitydialog.h"

#include "facility.h"
#include "datamanager.h"

EditFacilityDialog::EditFacilityDialog(const QSharedPointer<Facility> &facility, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::EditFacilityDialog),
    facility(facility)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditFacilityDialog::updateFacility);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditFacilityDialog::close);

    ui->ACSpin->setValue(facility->getNumberOfAcuteCareBeds());
    ui->LTCSpin->setValue(facility->getNumberOfLongTermCareBeds());
    ui->CCCSpin->setValue(facility->getNumberOfComplexContinuingCareBeds());
    ui->name->setText(facility->getName());
    ui->x->setNum(facility->getMapOffset().x());
    ui->y->setNum(facility->getMapOffset().y());
}

EditFacilityDialog::~EditFacilityDialog()
{
    delete ui;
}

void EditFacilityDialog::updateFacility()
{
    facility->setNumberOfAcuteCareBeds(ui->ACSpin->value());
    facility->setNumberOfComplexContinuingCareBeds(ui->CCCSpin->value());
    facility->setNumberOfLongTermCareBeds(ui->LTCSpin->value());
    facility->setName(ui->name->text());\
    facility->setMapOffset(QPoint(ui->x->text().toInt(), ui->y->text().toInt()));

    DataManager::sharedInstance().updateFacility(*facility);

    close();
}
