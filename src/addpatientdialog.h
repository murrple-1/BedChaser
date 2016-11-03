#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H

#include <QDialog>

namespace Ui {
    class AddPatientDialog;
}

class AddPatientDialog : public QDialog
{
    Q_OBJECT
public:
    AddPatientDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~AddPatientDialog();
private:
    Ui::AddPatientDialog *ui;
public slots:
    void addPatient();
};

#endif // ADDPATIENTDIALOG_H
