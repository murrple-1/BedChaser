#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H

#include <QDialog>
#include "QListWidgetItem"

namespace Ui {
    class AddPatientDialog;
}

class AddPatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatientDialog(QWidget *parent = 0);
    ~AddPatientDialog();
public slots:
    void addPatient();

private:
    Ui::AddPatientDialog *ui;
    std::vector<int> regionIDs;
};

#endif // ADDPATIENTDIALOG_H
