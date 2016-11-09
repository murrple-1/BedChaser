#include "regionframe.h"
#include "ui_regionframe.h"

#include <QDebug>

#include "datamanager.h"
#include "editfacilitydialog.h"
#include "waitinglistdialog.h"

RegionFrame::RegionFrame(const QSharedPointer<Region> &region, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RegionFrame),
    region(region)
{
    ui->setupUi(this);

    connect(ui->backPushButton, &QPushButton::clicked, this, &RegionFrame::backButtonClicked);
    connect(ui->waitingListPushButton, &QPushButton::clicked, this, &RegionFrame::waitingListClicked);

    QPixmap bannerPixmap;
    bannerPixmap.load("images/Map_Banner.jpg");
    ui->logoLabel->setPixmap(bannerPixmap);
    setFixedWidth(bannerPixmap.width());

    QPixmap subMapPixmap;
    bool success = subMapPixmap.load(region->getSubMapFileInfo().filePath());
    if(success)
    {
        ui->mapGraphicsView->scene()->addPixmap(subMapPixmap);
    }
    else
    {
        qWarning() << "Unable to load region map image";
    }

    updateFacilityList();
}

RegionFrame::~RegionFrame()
{
    delete ui;
}

void RegionFrame::backButtonClicked()
{
    emit goBack();
}

void RegionFrame::updateFacilityList()
{
    QPixmap f;
    f.load("images/FacilityLogo.jpg");

    QMap<QString, QVariant> whereParams;
    whereParams.insert(":regions_id", region->getID());
    QList<QSharedPointer<Facility> > facilities = DataManager::sharedInstance().getFacilities("`regions_id` = :regions_id", whereParams);
    foreach(const QSharedPointer<Facility> &facility, facilities)
    {
        Q_UNUSED(facility)
    }

    // TODO foreach facility in region, add a little label to the map
}

void RegionFrame::facilityListItemDoubleClicked(QListWidgetItem *item)
{
    int i = ui->facilitiesListListWidget->row(item);

    QMap<QString, QVariant> whereParams;
    whereParams.insert(":id", QString::number(i));
    QSharedPointer<Facility> facility = DataManager::sharedInstance().getFacilities("`id` = :id", whereParams, QString(), 1, 0).first();

    EditFacilityDialog ef(facility, this);
    ef.exec();
}

void RegionFrame::waitingListClicked()
{
    WaitingListDialog wf(region, this);
    wf.exec();
}
