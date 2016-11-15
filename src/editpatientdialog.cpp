#include "editpatientdialog.h"
#include "ui_editpatientdialog.h"

#include "patient.h"
#include "datamanager.h"

static const int RegionIdRole = Qt::UserRole + 1;

EditPatientDialog::EditPatientDialog(const QSharedPointer<Patient> &patient, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::EditPatientDialog),
    patient(patient)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditPatientDialog::updatePatient);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditPatientDialog::close);

    ui->healthCareNumberValueLabel->setText(QString::number(patient->getHealthCareNumber()));
    ui->nameLineEdit->setText(patient->getName());

    switch(patient->getRequiredCareType())
    {
    case CareTypeAcuteCare:
        ui->acuteCareRadioButton->setChecked(true);
        break;
    case CareTypeComplexContinuingCare:
        ui->complexContinuingCareRadioButton->setChecked(true);
        break;
    case CareTypeLongTermCare:
        ui->longTermCareRadioButton->setChecked(true);
        break;
    default:
        break;
    }

    QList<QSharedPointer<Region> > regions = DataManager::sharedInstance().getRegions();

    QMap<QString, QVariant> waitingListEntriesWhereParams;
    waitingListEntriesWhereParams.insert(":patients_id", patient->getID());
    QList<QSharedPointer<WaitingListEntry> > waitingListEntries = DataManager::sharedInstance().getWaitingListEntries("`patients_id` = :patients_id", waitingListEntriesWhereParams);

    foreach(const QSharedPointer<Region> &region, regions)
    {
        QListWidgetItem *item = new QListWidgetItem(region->getName());
        item->setData(RegionIdRole, region->getID());

        bool onWaitingList = false;
        foreach(const QSharedPointer<WaitingListEntry> &waitingListEntry, waitingListEntries)
        {
            if(waitingListEntry->getRegionId() == region->getID())
            {
                onWaitingList = true;
                break;
            }
        }
        ui->waitingListListWidget->addItem(item);

        item->setSelected(onWaitingList);
    }
}

EditPatientDialog::~EditPatientDialog()
{
    delete ui;
}

void EditPatientDialog::updatePatient()
{
    patient->setName(ui->nameLineEdit->text());

    if(ui->acuteCareRadioButton->isChecked())
    {
        patient->setRequiredCareType(CareTypeAcuteCare);
    }
    else if(ui->complexContinuingCareRadioButton->isChecked())
    {
        patient->setRequiredCareType(CareTypeComplexContinuingCare);
    }
    else if(ui->longTermCareRadioButton->isChecked())
    {
        patient->setRequiredCareType(CareTypeLongTermCare);
    }

    DataManager::sharedInstance().updatePatient(*patient);

    QList<QListWidgetItem *> selectedItems = ui->waitingListListWidget->selectedItems();

    QList<int> regionIds;
    foreach(QListWidgetItem * const selectedItem, selectedItems)
    {
        int regionId = selectedItem->data(RegionIdRole).toInt();
        regionIds.append(regionId);
    }

    foreach(int regionId, regionIds)
    {
        QMap<QString, QVariant> whereParams;
        whereParams.insert(":patients_id", patient->getID());
        whereParams.insert(":regions_id", regionId);
        QList<QSharedPointer<WaitingListEntry> > oldWaitingListEntries = DataManager::sharedInstance().getWaitingListEntries("`patients_id` = :patients_id AND `regions_id` = :regions_id", whereParams);
        if(oldWaitingListEntries.isEmpty())
        {
            WaitingListEntry waitingListEntry(regionId, patient->getID(), QDateTime::currentDateTimeUtc());
            DataManager::sharedInstance().addWaitingListEntry(waitingListEntry);
        }
    }

    QStringList regionIdIdentifiers;
    QMap<QString, QVariant> whereParams;
    for(int i = 0; i < regionIds.count(); i++)
    {
        QString identifier = QString(":regions_id_%1").arg(i);
        regionIdIdentifiers.append(identifier);
        whereParams.insert(identifier, regionIds.at(i));
    }

    whereParams.insert(":patients_id", patient->getID());

    QString whereClause = QString("`patients_id` = :patients_id AND `regions_id` NOT IN (%1)").arg(regionIdIdentifiers.join(','));
    QList<QSharedPointer<WaitingListEntry> > toDeleteWaitingListEntries = DataManager::sharedInstance().getWaitingListEntries(whereClause, whereParams);
    foreach(const QSharedPointer<WaitingListEntry> &waitingListEntry, toDeleteWaitingListEntries)
    {
        DataManager::sharedInstance().deleteWaitingListEntry(*waitingListEntry);
    }

    close();
}
