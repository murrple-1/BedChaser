#ifndef FACILITYREPORTDIALOG_H
#define FACILITYREPORTDIALOG_H

#include <QDialog>

namespace Ui {
    class FacilityReportDialog;
}

class FacilityReportDialog : public QDialog
{
    Q_OBJECT
public:
    FacilityReportDialog(QWidget *parent = 0);
    ~FacilityReportDialog();
private:
    Ui::FacilityReportDialog *ui;
private slots:
    void on_genreport_button_clicked();
};

#endif // FACILITYREPORTDIALOG_H
