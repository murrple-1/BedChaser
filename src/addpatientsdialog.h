#ifndef ADDPATIENTSDIALOG_H
#define ADDPATIENTSDIALOG_H

#include <QDialog>

namespace Ui {
class AddPatientsDialog;
}

#include <QList>
#include <QSharedPointer>

class Patient;

class AddPatientsDialog : public QDialog
{
    Q_OBJECT

public:
    AddPatientsDialog(const QList<QSharedPointer<Patient> > &ignoredPatients, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~AddPatientsDialog();

    QList<QSharedPointer<Patient> > selectedPatients() const;
private:
    void updatePatientList(const QString &searchText);

    Ui::AddPatientsDialog *ui;

    QList<QSharedPointer<Patient> > ignoredPatients;
private slots:
    void searchLineEditReturnPressed();
};

#endif // ADDPATIENTSDIALOG_H
