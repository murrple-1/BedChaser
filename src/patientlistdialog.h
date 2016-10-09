#ifndef PATIENTLISTDIALOG_H
#define PATIENTLISTDIALOG_H

#include <QDialog>

namespace Ui {
    class PatientListDialog;
}

class QListWidgetItem;

class Location;

class PatientListDialog : public QDialog
{
    Q_OBJECT

public:
    PatientListDialog(Location *, QWidget *parent = 0);
    ~PatientListDialog();

    void updatePatientList();
private:
    Ui::PatientListDialog *ui;

    Location *loc;
private slots:
    void on_addPatient_clicked();
    void on_patientList_itemDoubleClicked(QListWidgetItem *item);
};

#endif // PATIENTLISTDIALOG_H
