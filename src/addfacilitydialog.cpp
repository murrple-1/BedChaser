#include "addfacilitydialog.h"
#include "ui_addfacilitydialog.h"

#include <QMessageBox>

#include <limits>

#include "datamanager.h"
#include "facility.h"
#include "region.h"

static const int RegionIdRole = Qt::UserRole + 1;

AddFacilityDialog::AddFacilityDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::AddFacilityDialog)
{
    ui->setupUi(this);

    ui->xSpinBox->setMaximum(std::numeric_limits<int>::max());
    ui->ySpinBox->setMaximum(std::numeric_limits<int>::max());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddFacilityDialog::addFacility);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddFacilityDialog::close);

    QList<QSharedPointer<Region> > regions = DataManager::sharedInstance().getRegions();
    foreach(const QSharedPointer<Region> &region, regions)
    {
        ui->regionComboBox->addItem(region->getName());
        ui->regionComboBox->setItemData(ui->regionComboBox->count() - 1, region->getID(), RegionIdRole);
    }
}

AddFacilityDialog::~AddFacilityDialog()
{
    delete ui;
}

void AddFacilityDialog::addFacility()
{
    QString name = ui->nameLineEdit->text();
    if(name.isEmpty())
    {
        QMessageBox::critical(this, "No Name", "Name required for new facility");
        return;
    }

    int regionId = ui->regionComboBox->currentData(RegionIdRole).toInt();
    Facility facility(QVariant(), name, QPoint(ui->xSpinBox->value(), ui->ySpinBox->value()), ui->acuteCareSpinBox->value(), ui->complexContinuingCareSpinBox->value(), ui->longTermCareSpinBox->value(), regionId);
    DataManager::sharedInstance().addFacility(facility);
    close();
}
