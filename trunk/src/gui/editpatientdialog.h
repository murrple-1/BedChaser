#ifndef EDITPATIENTDIALOG_H
#define EDITPATIENTDIALOG_H

#include <QDialog>
#include "../core/patient.h"

namespace Ui {
    class EditPatientDialog;
}

class EditPatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPatientDialog(LHIN::Patient * const, QWidget *parent = 0);
    ~EditPatientDialog();

public slots:
    void updatePatient();

private:
    Ui::EditPatientDialog *ui;
    LHIN::Patient * patient;
};

#endif // EDITPATIENTDIALOG_H
