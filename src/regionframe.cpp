#include "regionframe.h"
#include "ui_regionframe.h"

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QListWidgetItem>

#include "datamanager.h"
#include "editfacilitydialog.h"
#include "waitinglistdialog.h"

static const int RegionIdRole = Qt::UserRole + 1;

RegionFrame::RegionFrame(const QSharedPointer<Region> &region, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RegionFrame),
    region(region)
{
    ui->setupUi(this);

    connect(ui->backPushButton, &QPushButton::clicked, this, &RegionFrame::backButtonClicked);
    connect(ui->waitingListPushButton, &QPushButton::clicked, this, &RegionFrame::waitingListClicked);
    connect(ui->facilitiesListListWidget, &QListWidget::doubleClicked, this, &RegionFrame::facilityListItemDoubleClicked);

    QPixmap bannerPixmap;
    bannerPixmap.load("images/Banner.jpg");
    ui->logoLabel->setPixmap(bannerPixmap);
    ui->logoLabel->setAlignment(Qt::AlignCenter);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->mapGraphicsView->setScene(scene);

    QPixmap subMapPixmap;
    bool success = subMapPixmap.load(region->getSubMapFileInfo().filePath());
    if(success)
    {
        scene->addPixmap(subMapPixmap);
        scene->setSceneRect(QRectF(subMapPixmap.rect()));
    }
    else
    {
        qWarning() << "Unable to load region map image";
    }

    updateFacilities();
}

RegionFrame::~RegionFrame()
{
    delete ui;
}

void RegionFrame::backButtonClicked()
{
    emit goBack();
}

void RegionFrame::facilityListItemDoubleClicked(const QModelIndex &index)
{
    int facilityId = index.data(RegionIdRole).toInt();

    QMap<QString, QVariant> whereParams;
    whereParams.insert(":id", QString::number(facilityId));
    QSharedPointer<Facility> facility = DataManager::sharedInstance().getFacilities("`id` = :id", whereParams, QString(), 1, 0).first();

    EditFacilityDialog ef(facility, this);
    ef.exec();

    updateFacilities();
}

void RegionFrame::waitingListClicked()
{
    WaitingListDialog waitingListDialog(region, this);
    waitingListDialog.exec();
}

void RegionFrame::updateFacilities()
{
    QGraphicsScene *scene = ui->mapGraphicsView->scene();

    foreach(QGraphicsItem * const facilityIcon, facilityIcons)
    {
        scene->removeItem(facilityIcon);
        delete facilityIcon;
    }
    facilityIcons.clear();

    ui->facilitiesListListWidget->clear();

    QPixmap facilityIcon;
    facilityIcon.load("images/FacilityIcon.jpg");

    QMap<QString, QVariant> whereParams;
    whereParams.insert(":regions_id", region->getID());
    QList<QSharedPointer<Facility> > facilities = DataManager::sharedInstance().getFacilities("`regions_id` = :regions_id", whereParams);
    foreach(const QSharedPointer<Facility> &facility, facilities)
    {
        QGraphicsPixmapItem *item = scene->addPixmap(facilityIcon);
        const QPoint &mapOffset = facility->getMapOffset();
        item->setPos(QPointF(mapOffset));
        facilityIcons.append(item);
    }

    foreach(const QSharedPointer<Facility> &facility, facilities)
    {
        QListWidgetItem *listItem = new QListWidgetItem(facility->getName());
        listItem->setData(RegionIdRole, facility->getID());
        ui->facilitiesListListWidget->addItem(listItem);
    }
}
