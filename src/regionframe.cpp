#include "regionframe.h"
#include "ui_regionframe.h"

#include "datamanager.h"
#include "editfacilitydialog.h"
#include "waitinglistdialog.h"

RegionFrame::RegionFrame(const QSharedPointer<Region> &region, QWidget *parent) :
    QFrame(parent), ui(new Ui::RegionFrame)
{
    ui->setupUi(this);

    this->region = region;

    QPixmap p;
    p.load("images/Map_Banner.jpg");
    ui->logoLabel->setPixmap(p);
    setFixedWidth(p.width());

    // TODO load pixmap
    QPixmap q;
    ui->mapLabel->setPixmap(q);
    ui->mapLabel->setFixedSize(q.size());

    updateFacilityList();
}

RegionFrame::~RegionFrame()
{
    delete ui;
}

void RegionFrame::on_back_clicked()
{
    emit backButtonPressed();
}

void RegionFrame::updateFacilityList()
{
    QPixmap f;
    f.load("images/FacilityLogo.jpg");

    // TODO foreach facility in region, add a little label to the map
}

void RegionFrame::on_listoffacilities_itemDoubleClicked(QListWidgetItem *item)
{
    int i = ui->facilitiesListListWidget->row(item);

    QSharedPointer<Facility> facility = DataManager::sharedInstance().getFacility(i);

    EditFacilityDialog ef(facility, this);
    ef.exec();
}

void RegionFrame::on_waitinglist_clicked()
{
    WaitingListDialog wf(region, this);
    wf.exec();
}
