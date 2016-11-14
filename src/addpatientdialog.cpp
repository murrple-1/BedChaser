#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

#include <QDebug>
#include <QMessageBox>

#include "datamanager.h"
#include "patient.h"
#include "facility.h"
#include "waitinglistentry.h"

static const int RegionIdRole = Qt::UserRole + 1;

AddPatientDialog::AddPatientDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::AddPatientDialog)
{
    ui->setupUi(this);

    ui->acuteCareRadioButton->setChecked(true);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddPatientDialog::addPatient);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddPatientDialog::close);

    QList<QSharedPointer<Region> > regions = DataManager::sharedInstance().getRegions();
    foreach(const QSharedPointer<Region> &region, regions)
    {
        QListWidgetItem *item = new QListWidgetItem(region->getName());
        item->setData(RegionIdRole, region->getID());
        ui->waitingListListWidget->addItem(item);
    }
}

AddPatientDialog::~AddPatientDialog()
{
    delete ui;
}

void AddPatientDialog::addPatient()
{
    CareType requiredCare = CareTypeNone;
    if(ui->acuteCareRadioButton->isChecked())
    {
        requiredCare = CareTypeAcuteCare;
    }
    else if(ui->complexContinuingCareRadioButton->isChecked())
    {
        requiredCare = CareTypeComplexContinuingCare;
    }
    else if(ui->longTermCareRadioButton->isChecked())
    {
        requiredCare = CareTypeLongTermCare;
    }

    Patient patient(QVariant(), ui->healthCareNumberLineEdit->text().toInt(), ui->nameLineEdit->text(), requiredCare, CareTypeNone, QVariant(), QDateTime());

    QVariant _patientId = DataManager::sharedInstance().addPatient(patient);
    bool success;
    int patientId = _patientId.toInt(&success);
    if(success)
    {
        QList<QListWidgetItem *> items = ui->waitingListListWidget->selectedItems();
        foreach(QListWidgetItem * const item, items)
        {
            int regionId = item->data(RegionIdRole).toInt();
            WaitingListEntry waitingListEntry(regionId, patientId, QDateTime::currentDateTimeUtc());
            DataManager::sharedInstance().addWaitingListEntry(waitingListEntry);
        }
        close();
    }
    else
    {
        qWarning() << "Newly inserted patient id not known";
        QMessageBox::critical(this, "Error", "Unable to fully insert patient");
    }
}
