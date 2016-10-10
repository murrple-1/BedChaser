#ifndef PATIENTLISTDIALOG_H
#define PATIENTLISTDIALOG_H

#include <QDialog>

namespace Ui {
    class PatientListDialog;
}

#include <QSharedPointer>

class QListWidgetItem;

class Location;

class PatientListDialog : public QDialog
{
    Q_OBJECT
public:
    PatientListDialog(const QSharedPointer<Location> &, QWidget *parent = 0);
    ~PatientListDialog();
private:
    void updatePatientList();

    Ui::PatientListDialog *ui;

    QSharedPointer<Location> location;
private slots:
    void on_addPatient_clicked();
    void on_patientList_itemDoubleClicked(QListWidgetItem *item);
};

#endif // PATIENTLISTDIALOG_H
