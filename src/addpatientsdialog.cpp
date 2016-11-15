#include "addpatientsdialog.h"
#include "ui_addpatientsdialog.h"

#include "datamanager.h"
#include "patient.h"

static const int PatientIdRole = Qt::UserRole + 1;

AddPatientsDialog::AddPatientsDialog(const QList<QSharedPointer<Patient> > &ignoredPatients, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::AddPatientsDialog),
    ignoredPatients(ignoredPatients)
{
    ui->setupUi(this);

    connect(ui->searchLineEdit, &QLineEdit::returnPressed, this, &AddPatientsDialog::searchLineEditReturnPressed);
    connect(ui->okPushButton, &QPushButton::clicked, this, &AddPatientsDialog::accept);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &AddPatientsDialog::reject);

    updatePatientList(QString());
}

AddPatientsDialog::~AddPatientsDialog()
{
    delete ui;
}

void AddPatientsDialog::updatePatientList(const QString &searchText)
{
    ui->patientListWidget->clear();

    QStringList whereClauseParts;

    QMap<QString, QVariant> whereParams;

    if(!searchText.isEmpty())
    {
        QString sqlSearchText = QString("%%1%").arg(searchText);
        whereClauseParts.append("`name` LIKE :name");
        whereParams.insert(":name", sqlSearchText);
    }

    if(!ignoredPatients.isEmpty())
    {
        QStringList ignoredPatientIds;
        for(int i = 0; i < ignoredPatients.count(); i++)
        {
            QString identifier = QString(":id_%1").arg(i);
            const QSharedPointer<Patient> &patient = ignoredPatients.at(i);
            ignoredPatientIds.append(identifier);
            whereParams.insert(identifier, patient->getID());
        }

        whereClauseParts.append(QString("`id` NOT IN (%1)").arg(ignoredPatientIds.join(',')));
    }

    QString whereClause = whereClauseParts.join(" AND ");

    QList<QSharedPointer<Patient> > patients = DataManager::sharedInstance().getPatients(whereClause, whereParams);
    foreach(const QSharedPointer<Patient> &patient, patients)
    {
        QListWidgetItem *item = new QListWidgetItem(QString("%1 - %2").arg(patient->getHealthCareNumber()).arg(patient->getName()));
        item->setData(PatientIdRole, patient->getID());
        ui->patientListWidget->addItem(item);
    }
}

QList<QSharedPointer<Patient> > AddPatientsDialog::selectedPatients() const
{
    QList<QListWidgetItem *> selectedItems = ui->patientListWidget->selectedItems();

    QList<int> patientIds;
    foreach(QListWidgetItem * const item, selectedItems)
    {
        int patientId = item->data(PatientIdRole).toInt();
        patientIds.append(patientId);
    }

    QStringList patientIdIdentifiers;
    QMap<QString, QVariant> whereParams;
    for(int i = 0; i < patientIds.count(); i++)
    {
        QString identifier = QString(":id_%1").arg(i);
        patientIdIdentifiers.append(identifier);
        whereParams.insert(identifier, patientIds.at(i));
    }

    QString whereClause = QString("`id` IN (%1)").arg(patientIdIdentifiers.join(','));

    QList<QSharedPointer<Patient> > patients = DataManager::sharedInstance().getPatients(whereClause, whereParams);
    return patients;
}

void AddPatientsDialog::searchLineEditReturnPressed()
{
    updatePatientList(ui->searchLineEdit->text());
}
