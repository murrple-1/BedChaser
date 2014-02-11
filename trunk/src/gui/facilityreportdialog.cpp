#include "facilityreportdialog.h"
#include "ui_facilityreportdialog.h"
#include "facilityreportdisplay.h"

FacilityReportDialog::FacilityReportDialog(LHIN::Location * const l, std::vector<LHIN::Memento *> mems, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FacilityReportDialog)
{
    ui->setupUi(this);
    /*
THE BELOW CODE IS INTENDED FOR A PROTOTYPE, AND DOES NOT IMPLEMENT REAL LOGIC
*/
    ui->facility_combo->addItem("Pembrooke");
}

FacilityReportDialog::~FacilityReportDialog()
{
    delete ui;
}

void FacilityReportDialog::on_genreport_button_clicked()
{
    FacilityReportDisplay *d = new FacilityReportDisplay(this);
    d->exec();
    delete d;
}
