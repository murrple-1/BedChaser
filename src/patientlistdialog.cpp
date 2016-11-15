#include "patientlistdialog.h"
#include "ui_patientlistdialog.h"

#include <QMessageBox>
#include <QDebug>

#include "patient.h"
#include "datamanager.h"

static const int PatientIdRole = Qt::UserRole + 1;

PatientListDialog::PatientListDialog(const QSharedPointer<Facility> &facility, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::PatientListDialog),
    facility(facility)
{
    ui->setupUi(this);

    connect(ui->patientsListWidget, &QListWidget::doubleClicked, this, &PatientListDialog::listItemDoubleClicked);
    connect(ui->addPatientsPushButton, &QPushButton::clicked, this, &PatientListDialog::showAddPatientsDialog);

    updatePatientsList();
}

PatientListDialog::~PatientListDialog()
{
    delete ui;
}

void PatientListDialog::updatePatientsList()
{
    ui->patientsListWidget->clear();

    QMap<QString, QVariant> whereParams;
    whereParams.insert(":receiving_care_facilities_id", facility->getID());
    QList<QSharedPointer<Patient> > patients = DataManager::sharedInstance().getPatients("`receiving_care_facilities_id` = :receiving_care_facilities_id", whereParams);
    foreach(const QSharedPointer<Patient> &patient, patients)
    {
        QListWidgetItem *item = new QListWidgetItem(QString("%1 - %2").arg(patient->getHealthCareNumber()).arg(patient->getName()));
        item->setData(PatientIdRole, patient->getID());
        ui->patientsListWidget->addItem(item);
    }
}

void PatientListDialog::listItemDoubleClicked(const QModelIndex &index)
{
    int response = QMessageBox::question(this, "Remove Patient?", "Would you like to remove this patient from the patient list?", QMessageBox::Yes, QMessageBox::No);
    switch(response)
    {
    case QMessageBox::Yes:
    {
        QMap<QString, QVariant> whereParams;
        whereParams.insert(":receiving_care_facilities_id", facility->getID());
        whereParams.insert(":patients_id", index.data(PatientIdRole));
        QSharedPointer<Patient> patient = DataManager::sharedInstance().getPatients("`receiving_care_facilities_id` = :receiving_care_facilities_id AND `patients_id` = :patients_id", whereParams, QString(), 1).first();

        patient->setReceivingCareType(CareTypeNone);
        patient->setReceivingCareFacilityId(QVariant());
        patient->setDateAdmitted(QDateTime());

        DataManager::sharedInstance().updatePatient(*patient);
    }
        break;
    case QMessageBox::No:
        break;
    default:
        qWarning() << "Unknown response to question message box";
        break;
    }

    updatePatientsList();
}

void PatientListDialog::showAddPatientsDialog()
{
    // TODO
}
