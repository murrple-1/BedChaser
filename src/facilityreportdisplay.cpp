#include "facilityreportdisplay.h"
#include "ui_facilityreportdisplay.h"

FacilityReportDisplay::FacilityReportDisplay(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::FacilityReportDisplay)
{
    ui->setupUi(this);
}

FacilityReportDisplay::~FacilityReportDisplay()
{
    delete ui;
}
