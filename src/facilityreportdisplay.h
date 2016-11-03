#ifndef FACILITYREPORTDISPLAY_H
#define FACILITYREPORTDISPLAY_H

#include <QDialog>

namespace Ui {
    class FacilityReportDisplay;
}

class FacilityReportDisplay : public QDialog
{
    Q_OBJECT
public:
    FacilityReportDisplay(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~FacilityReportDisplay();
private:
    Ui::FacilityReportDisplay *ui;
};

#endif // FACILITYREPORTDISPLAY_H
