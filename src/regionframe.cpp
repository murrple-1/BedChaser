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

    foreach(int facilityId, region->getFacilityIds())
    {
        QSharedPointer<Facility> facility = DataManager::sharedInstance().getFacility(facilityId);
        ui->facilitiesListListWidget->addItem(facility->getName());

        QLabel *newlogo = new QLabel(this);
        QLabel *newlogoname = new QLabel(this);

        float xPer = facility->getX() / 100.0f;
        float yPer = facility->getY() / 100.0f;

        int X = (xPer * ui->mapLabel->width()) + ui->mapLabel->x();
        int Y = (yPer * ui->mapLabel->height()) + ui->mapLabel->y();

        newlogo->setGeometry(X, Y, 60, 17);
        newlogo->setPixmap(f);
        newlogoname->setGeometry(X + 15, Y, 170, 17);
        newlogoname->setText(facility->getName());
    }
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
