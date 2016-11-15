#include "patientlistdialog.h"
#include "ui_patientlistdialog.h"

#include <QMessageBox>
#include <QDebug>

#include "datamanager.h"
#include "addpatientsdialog.h"

static const int PatientIdRole = Qt::UserRole + 1;

PatientListDialog::PatientListDialog(const QSharedPointer<Facility> &facility, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::PatientListDialog),
    facility(facility)
{
    ui->setupUi(this);

    connect(ui->patientsListWidget, &QListWidget::doubleClicked, this, &PatientListDialog::listItemDoubleClicked);
    connect(ui->addAcuteCarePatientsPushButton, &QPushButton::clicked, this, &PatientListDialog::showAddPatientsDialog_acuteCare);
    connect(ui->addComplexContinuingCarePatientsPushButton, &QPushButton::clicked, this, &PatientListDialog::showAddPatientsDialog_complexContinuingCare);
    connect(ui->addLongTermCarePatientsPushButton, &QPushButton::clicked, this, &PatientListDialog::showAddPatientsDialog_longTermCare);

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

        updatePatientsList();
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

void PatientListDialog::addPatients(CareType careType)
{
    QMap<QString, QVariant> whereParams;
    whereParams.insert(":receiving_care_facilities_id", facility->getID());
    QList<QSharedPointer<Patient> > patients = DataManager::sharedInstance().getPatients("`receiving_care_facilities_id` = :receiving_care_facilities_id", whereParams);

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
            patient->setReceivingCareType(careType);
            patient->setReceivingCareFacilityId(facility->getID());
            patient->setDateAdmitted(now);

            DataManager::sharedInstance().updatePatient(*patient);
        }

        updatePatientsList();
    }
        break;
    case AddPatientsDialog::Rejected:
        break;
    default:
        qWarning() << "Unknown response to Add Patients Dialog";
        break;
    }
}

void PatientListDialog::showAddPatientsDialog_acuteCare()
{
    addPatients(CareTypeAcuteCare);
}

void PatientListDialog::showAddPatientsDialog_complexContinuingCare()
{
    addPatients(CareTypeComplexContinuingCare);
}

void PatientListDialog::showAddPatientsDialog_longTermCare()
{
    addPatients(CareTypeLongTermCare);
}
