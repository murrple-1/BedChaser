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
    PatientReportDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~PatientReportDialog();
private:
    Ui::PatientReportDialog *ui;
};

#endif // PATIENTREPORTDIALOG_H
