#ifndef EDITPATIENTDIALOG_H
#define EDITPATIENTDIALOG_H

#include <QDialog>

namespace Ui {
    class EditPatientDialog;
}

class Patient;

class EditPatientDialog : public QDialog
{
    Q_OBJECT
public:
    EditPatientDialog(Patient *, QWidget *parent = 0);
    ~EditPatientDialog();
private:
    Ui::EditPatientDialog *ui;

    Patient *patient;
public slots:
    void updatePatient();
};

#endif // EDITPATIENTDIALOG_H
