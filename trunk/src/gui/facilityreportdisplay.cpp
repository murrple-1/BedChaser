#include "facilityreportdisplay.h"
#include "ui_facilityreportdisplay.h"

#include "KDChartWidget"
#include "KDChartBarDiagram"
#include "KDChartPosition"
#include "KDChartLegend"
#include "KDChartLineDiagram"

FacilityReportDisplay::FacilityReportDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FacilityReportDisplay)
{
    ui->setupUi(this);

    /*
THE BELOW CODE IS INTENDED FOR A PROTOTYPE, AND DOES NOT IMPLEMENT REAL LOGIC
*/
    ui->facName->setText("Pembrooke");
    ui->sDate->setText("January 1, 2007");
    ui->eDate->setText("January 1, 2009");

    KDChart::Widget * avaChart = new KDChart::Widget();
    QVector<double> avaAC, avaCCC, avaLTC;
    avaAC << 5;
    avaCCC << 7;
    avaLTC << 4;
    avaChart->setDataset(0, avaAC, "AC");
    avaChart->setDataset(1, avaCCC, "CCC");
    avaChart->setDataset(2, avaLTC, "LTC");
    avaChart->setType(KDChart::Widget::Bar);
    KDChart::Legend * avaLeg = new KDChart::Legend();
    avaLeg->setPosition(KDChart::Position::North);
    avaLeg->setTitleText("Available Beds");
    avaLeg->setOrientation(Qt::Horizontal);
    avaLeg->setText(0, "AC");
    avaLeg->setText(0, "CCC");
    avaLeg->setText(0, "LTC");
    avaChart->addLegend(avaLeg);
    KDChart::CartesianAxis * avaYAxis = new KDChart::CartesianAxis(avaChart->barDiagram());
    avaYAxis->setPosition(KDChart::CartesianAxis::Left);
    avaYAxis->setTitleText("Beds Available");
    avaChart->barDiagram()->addAxis(avaYAxis);
    ui->avaLayout->addWidget(avaChart);

    KDChart::Widget * occChart = new KDChart::Widget();
    QVector<double> occAC, occCCC, occLTC;
    occAC << 2;
    occCCC << 7;
    occLTC << 1;
    occChart->setDataset(0, occAC, "AC");
    occChart->setDataset(1, occCCC, "CCC");
    occChart->setDataset(2, occLTC, "LTC");
    occChart->setType(KDChart::Widget::Pie);
    KDChart::Legend * occLeg = new KDChart::Legend();
    occLeg->setPosition(KDChart::Position::North);
    occLeg->setTitleText("Occupied Beds");
    occLeg->setOrientation(Qt::Horizontal);
    occLeg->setText(0, "AC");
    occLeg->setText(0, "CCC");
    occLeg->setText(0, "LTC");
    occChart->addLegend(occLeg);
    ui->occLayout->addWidget(occChart);
}

FacilityReportDisplay::~FacilityReportDisplay()
{
    delete ui;
}
