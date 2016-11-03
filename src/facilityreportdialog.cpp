#include "facilityreportdialog.h"
#include "ui_facilityreportdialog.h"

#include "facilityreportdisplay.h"

FacilityReportDialog::FacilityReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FacilityReportDialog)
{
    ui->setupUi(this);

    ui->facility_combo->addItem("Pembrooke");
}

FacilityReportDialog::~FacilityReportDialog()
{
    delete ui;
}

void FacilityReportDialog::generateReport()
{
    FacilityReportDisplay d(this);
    d.exec();
}
