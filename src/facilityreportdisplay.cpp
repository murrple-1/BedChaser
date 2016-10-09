#include "facilityreportdisplay.h"
#include "ui_facilityreportdisplay.h"

FacilityReportDisplay::FacilityReportDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FacilityReportDisplay)
{
    ui->setupUi(this);
}

FacilityReportDisplay::~FacilityReportDisplay()
{
    delete ui;
}
