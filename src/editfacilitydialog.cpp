#include "editfacilitydialog.h"
#include "ui_editfacilitydialog.h"

#include <limits>

#include "facility.h"
#include "datamanager.h"
#include "patientlistdialog.h"

EditFacilityDialog::EditFacilityDialog(const QSharedPointer<Facility> &facility, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::EditFacilityDialog),
    facility(facility)
{
    ui->setupUi(this);

    ui->xSpinBox->setMaximum(std::numeric_limits<int>::max());
    ui->ySpinBox->setMaximum(std::numeric_limits<int>::max());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditFacilityDialog::updateFacility);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditFacilityDialog::close);
    connect(ui->patientListButton, &QPushButton::clicked, this, &EditFacilityDialog::showPatientList);

    ui->acuteCareSpinBox->setValue(facility->getNumberOfAcuteCareBeds());
    ui->complexContinuingCareSpinBox->setValue(facility->getNumberOfComplexContinuingCareBeds());
    ui->longTermCareSpinBox->setValue(facility->getNumberOfLongTermCareBeds());
    ui->nameLineEdit->setText(facility->getName());
    const QPoint &mapOffset = facility->getMapOffset();
    ui->xSpinBox->setValue(mapOffset.x());
    ui->ySpinBox->setValue(mapOffset.y());
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
    facility->setName(ui->nameLineEdit->text());\
    facility->setMapOffset(QPoint(ui->xSpinBox->value(), ui->ySpinBox->value()));

    DataManager::sharedInstance().updateFacility(*facility);

    close();
}

void EditFacilityDialog::showPatientList()
{
    PatientListDialog patientListDialog(facility, this);
    patientListDialog.exec();
}
