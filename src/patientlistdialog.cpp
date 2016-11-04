#include "patientlistdialog.h"
#include "ui_patientlistdialog.h"

#include "datamanager.h"

PatientListDialog::PatientListDialog(const QSharedPointer<Facility> &facility, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::PatientListDialog)
{
    ui->setupUi(this);

    this->facility = facility;

    updatePatientList();
}

PatientListDialog::~PatientListDialog()
{
    delete ui;
}

void PatientListDialog::updatePatientList()
{
    ui->patientList->clear();

    // TODO
}

void PatientListDialog::patientListItemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    // TODO

    updatePatientList();
}
