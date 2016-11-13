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

    ui->acuteCareSpinBox->setValue(facility->getNumberOfAcuteCareBeds());
    ui->complexContinuingCareSpinBox->setValue(facility->getNumberOfComplexContinuingCareBeds());
    ui->longTermCareSpinBox->setValue(facility->getNumberOfLongTermCareBeds());
    ui->nameValueLabel->setText(facility->getName());
    ui->xValueLabel->setNum(facility->getMapOffset().x());
    ui->yValueLabel->setNum(facility->getMapOffset().y());
}

EditFacilityDialog::~EditFacilityDialog()
{
    delete ui;
}

void EditFacilityDialog::updateFacility()
{
    facility->setNumberOfAcuteCareBeds(ui->acuteCareSpinBox->value());
    facility->setNumberOfComplexContinuingCareBeds(ui->complexContinuingCareSpinBox->value());
    facility->setNumberOfLongTermCareBeds(ui->longTermCareSpinBox->value());
    facility->setName(ui->nameValueLabel->text());\
    facility->setMapOffset(QPoint(ui->xValueLabel->text().toInt(), ui->yValueLabel->text().toInt()));

    DataManager::sharedInstance().updateFacility(*facility);

    close();
}
