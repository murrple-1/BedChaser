#include "waitinglistdialog.h"
#include "ui_waitinglistdialog.h"

#include <QMessageBox>
#include <QDebug>

#include "patient.h"
#include "region.h"
#include "datamanager.h"
#include "addpatientsdialog.h"

static const int PatientIdRole = Qt::UserRole + 1;

WaitingListDialog::WaitingListDialog(const QSharedPointer<Region> &region, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::WaitingListDialog),
    region(region)
{
    ui->setupUi(this);

    connect(ui->patientsListWidget, &QListWidget::doubleClicked, this, &WaitingListDialog::listItemDoubleClicked);
    connect(ui->addPatientsPushButton, &QPushButton::clicked, this, &WaitingListDialog::showAddPatientsDialog);

    updateWaitingList();
}

WaitingListDialog::~WaitingListDialog()
{
    delete ui;
}

void WaitingListDialog::updateWaitingList()
{
    ui->patientsListWidget->clear();

    QMap<QString, QVariant> whereParams;
    whereParams.insert(":regions_id", region->getID());
    QList<QSharedPointer<WaitingListEntry> > waitingListEntries = DataManager::sharedInstance().getWaitingListEntries("`regions_id` = :regions_id", whereParams);
    foreach(const QSharedPointer<WaitingListEntry> &waitingListEntry, waitingListEntries)
    {
        QMap<QString, QVariant> _whereParams;
        _whereParams.insert(":id", waitingListEntry->getPatientId());
        QSharedPointer<Patient> patient = DataManager::sharedInstance().getPatients("`id` = :id", _whereParams, QString(), 1).first();
        QListWidgetItem *item = new QListWidgetItem(QString("%1 - %2").arg(patient->getHealthCareNumber()).arg(patient->getName()));
        item->setData(PatientIdRole, patient->getID());
        ui->patientsListWidget->addItem(item);
    }
}

void WaitingListDialog::listItemDoubleClicked(const QModelIndex &index)
{
    int response = QMessageBox::question(this, "Remove Patient?", "Would you like to remove this patient from the waiting list?", QMessageBox::Yes, QMessageBox::No);
    switch(response)
    {
    case QMessageBox::Yes:
    {
        QMap<QString, QVariant> whereParams;
        whereParams.insert(":regions_id", region->getID());
        whereParams.insert(":patients_id", index.data(PatientIdRole));
        QSharedPointer<WaitingListEntry> waitingListEntry = DataManager::sharedInstance().getWaitingListEntries("`regions_id` = :regions_id AND `patients_id` = :patients_id", whereParams, QString(), 1).first();
        DataManager::sharedInstance().deleteWaitingListEntry(*waitingListEntry);

        updateWaitingList();
    }
        break;
    case QMessageBox::No:
        break;
    default:
        qWarning() << "Unknown response to question message box";
        break;
    }

    updateWaitingList();
}

void WaitingListDialog::showAddPatientsDialog()
{
    QMap<QString, QVariant> whereParams;
    whereParams.insert(":regions_id", region->getID());
    QList<QSharedPointer<WaitingListEntry> > waitingListEntries = DataManager::sharedInstance().getWaitingListEntries("`regions_id` = :regions_id", whereParams);

    QList<QSharedPointer<Patient> > patients;
    foreach(const QSharedPointer<WaitingListEntry> &waitingListEntry, waitingListEntries)
    {
        QMap<QString, QVariant> _whereParams;
        _whereParams.insert(":id", waitingListEntry->getPatientId());
        QSharedPointer<Patient> patient = DataManager::sharedInstance().getPatients("`id` = :id", _whereParams, QString(), 1).first();
        patients.append(patient);
    }

    AddPatientsDialog addPatientsDialog(patients);
    int result = addPatientsDialog.exec();
    switch(result)
    {
    case AddPatientsDialog::Accepted:
    {
        QDateTime now = QDateTime::currentDateTimeUtc();
        QList<QSharedPointer<Patient> > patients = addPatientsDialog.selectedPatients();
        foreach(const QSharedPointer<Patient> &patient, patients)
        {
            WaitingListEntry waitingListEntry(region->getID(), patient->getID(), now);

            DataManager::sharedInstance().addWaitingListEntry(waitingListEntry);
        }

        updateWaitingList();
    }
        break;
    case AddPatientsDialog::Rejected:
        break;
    default:
        qWarning() << "Unknown response to Add Patients Dialog";
        break;
    }
}
