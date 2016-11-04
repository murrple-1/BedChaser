#ifndef PATIENTLISTDIALOG_H
#define PATIENTLISTDIALOG_H

#include <QDialog>

namespace Ui {
    class PatientListDialog;
}

#include <QSharedPointer>

class QListWidgetItem;

class Facility;

class PatientListDialog : public QDialog
{
    Q_OBJECT
public:
    PatientListDialog(const QSharedPointer<Facility> &, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~PatientListDialog();
private:
    void updatePatientList();

    Ui::PatientListDialog *ui;

    QSharedPointer<Facility> facility;
private slots:
    void patientListItemDoubleClicked(QListWidgetItem *item);
};

#endif // PATIENTLISTDIALOG_H
