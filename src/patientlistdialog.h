#ifndef PATIENTLISTDIALOG_H
#define PATIENTLISTDIALOG_H

#include <QDialog>

namespace Ui {
class PatientListDialog;
}

#include <QSharedPointer>

#include "patient.h"

class Facility;

class PatientListDialog : public QDialog
{
    Q_OBJECT

public:
    PatientListDialog(const QSharedPointer<Facility> &facility, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~PatientListDialog();
private:
    void updatePatientsList();
    void addPatients(CareType careType);

    Ui::PatientListDialog *ui;

    QSharedPointer<Facility> facility;
private slots:
    void listItemDoubleClicked(const QModelIndex &index);
    void showAddPatientsDialog_acuteCare();
    void showAddPatientsDialog_complexContinuingCare();
    void showAddPatientsDialog_longTermCare();
};

#endif // PATIENTLISTDIALOG_H
