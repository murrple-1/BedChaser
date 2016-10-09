#include "patientreportdialog.h"
#include "ui_patientreportdialog.h"

PatientReportDialog::PatientReportDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::PatientReportDialog)
{
    ui->setupUi(this);

    // THE BELOW CODE IS INTENDED FOR A PROTOTYPE, AND DOES NOT IMPLEMENT REAL LOGIC

    QString str = "Health Care Number: 4759360274\n"
                  "Patient Name: John Doe\n"
                  "Date Added to Waiting List: April 6, 2011\n"
                  "Date Admit To Facility: April 14, 2011\n"
                  "In Facility: Pembrooke\n"
                  "Days On Waiting List: 8\n"
                  "Required Care Type: AC\n"
                  "Received Care Type: CCC\n"
                  "MISMATCH CARE FOUND\n"
                  "Additional Details:\n"
                  "N/A";
    ui->reportText->setText(str);
}

PatientReportDialog::~PatientReportDialog()
{
    delete ui;
}
