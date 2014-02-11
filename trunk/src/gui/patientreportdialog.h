#ifndef PATIENTREPORTDIALOG_H
#define PATIENTREPORTDIALOG_H

#include <QDialog>

namespace Ui {
    class PatientReportDialog;
}

class PatientReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PatientReportDialog(QWidget *parent = 0);
    ~PatientReportDialog();

private:
    Ui::PatientReportDialog *ui;
};

#endif // PATIENTREPORTDIALOG_H
