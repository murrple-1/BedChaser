#include "regionframe.h"
#include "ui_regionframe.h"

#include "datamanager.h"
#include "editfacilitydialog.h"
#include "waitinglistdialog.h"

RegionFrame::RegionFrame(Region *region, QWidget *parent) :
    QFrame(parent), ui(new Ui::RegionFrame)
{
    ui->setupUi(this);

    this->r = region;

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

    foreach(int locationId, r->getLocationIds())
    {
        Location *location = DataManager::sharedInstance().getLocation(locationId);
        ui->listoffacilities->addItem(location->getName());

        QLabel *newlogo = new QLabel(this);
        QLabel *newlogoname = new QLabel(this);

        float xPer = location->getX() / 100.0f;
        float yPer = location->getY() / 100.0f;

        int X = (xPer * ui->mapLabel->width()) + ui->mapLabel->x();
        int Y = (yPer * ui->mapLabel->height()) + ui->mapLabel->y();

        newlogo->setGeometry(X, Y, 60, 17);
        newlogo->setPixmap(f);
        newlogoname->setGeometry(X + 15, Y, 170, 17);
        newlogoname->setText(location->getName());

        delete location;
    }
}

void RegionFrame::on_listoffacilities_itemDoubleClicked(QListWidgetItem *item)
{
    int i = ui->listoffacilities->row(item);

    Location *location = DataManager::sharedInstance().getLocation(i);

    EditFacilityDialog ef(location, this);
    ef.exec();
}

void RegionFrame::on_waitinglist_clicked()
{
    WaitingListDialog wf(r, this);
    wf.exec();
}
