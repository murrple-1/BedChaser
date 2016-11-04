#ifndef EDITPATIENTDIALOG_H
#define EDITPATIENTDIALOG_H

#include <QDialog>

namespace Ui {
    class EditPatientDialog;
}

#include <QSharedPointer>

class Patient;

class EditPatientDialog : public QDialog
{
    Q_OBJECT
public:
    EditPatientDialog(const QSharedPointer<Patient> &, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~EditPatientDialog();
private:
    Ui::EditPatientDialog *ui;

    QSharedPointer<Patient> patient;
private slots:
    void updatePatient();
};

#endif // EDITPATIENTDIALOG_H
