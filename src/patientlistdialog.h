#ifndef PATIENTLISTDIALOG_H
#define PATIENTLISTDIALOG_H

#include <QDialog>

namespace Ui {
class PatientListDialog;
}

#include <QSharedPointer>

class Facility;

class PatientListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PatientListDialog(const QSharedPointer<Facility> &facility, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~PatientListDialog();
private:
    void updatePatientsList();

    Ui::PatientListDialog *ui;

    QSharedPointer<Facility> facility;
private slots:
    void listItemDoubleClicked(const QModelIndex &index);
    void showAddPatientsDialog();
};

#endif // PATIENTLISTDIALOG_H
