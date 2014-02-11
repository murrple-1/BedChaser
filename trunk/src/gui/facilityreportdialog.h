#ifndef FACILITYREPORTDIALOG_H
#define FACILITYREPORTDIALOG_H

#include <QDialog>
#include <vector>
#include "../core/location.h"
#include "../core/memento.h"

namespace Ui {
    class FacilityReportDialog;
}

class FacilityReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FacilityReportDialog(LHIN::Location * const, std::vector<LHIN::Memento *>, QWidget *parent = 0);
    ~FacilityReportDialog();

private:
    Ui::FacilityReportDialog *ui;

private slots:
    void on_genreport_button_clicked();
};

#endif // FACILITYREPORTDIALOG_H
