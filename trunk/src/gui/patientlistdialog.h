#ifndef PATIENTLISTDIALOG_H
#define PATIENTLISTDIALOG_H

#include <QDialog>
#include "../core/location.h"
#include "QListWidgetItem"

namespace Ui {
    class PatientListDialog;
}

class PatientListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PatientListDialog(LHIN::Location * const, QWidget *parent = 0);
    void updatePatientList();
    ~PatientListDialog();

private:
    Ui::PatientListDialog *ui;
    LHIN::Location * loc;

private slots:
    void on_addPatient_clicked();
    void on_patientList_itemDoubleClicked(QListWidgetItem* item);
};

#endif // PATIENTLISTDIALOG_H
