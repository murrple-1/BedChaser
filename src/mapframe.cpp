#include "mapframe.h"
#include "ui_mapframe.h"

#include <QPainter>
#include <QPushButton>
#include <QGridLayout>

#include "datamanager.h"

MapFrame::MapFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MapFrame)
{
    ui->setupUi(this);

    QPixmap bannerPixmap;
    bannerPixmap.load("images/Map_Banner.jpg");
    ui->bannerLabel->setPixmap(bannerPixmap);
    ui->bannerLabel->setAlignment(Qt::AlignCenter);

    QPixmap mapPixmap;
    mapPixmap.load("images/map.jpg");

    QGraphicsScene *scene = new QGraphicsScene(this);

    scene->setSceneRect(QRectF(mapPixmap.rect()));
    scene->addPixmap(mapPixmap);

    ui->mapGraphicsView->setScene(scene);

    // TODO add the regions?

//    int xOffset = 0;
//    int yOffset = bannerPixmap.height();

//    QList<QSharedPointer<Region> > regions = DataManager::sharedInstance().getRegions();
//    foreach(const QSharedPointer<Region> &region, regions)
//    {
//        QPushButton *button = new QPushButton(region->getName(), this);
//        button->setProperty("regionId", region->getID());
//        connect(button, &QPushButton::clicked, this, &MapFrame::regionButtonClicked);
//        const QPoint &mapOffset = region->getMapOffset();
//        button->move(xOffset + mapOffset.x(), yOffset + mapOffset.y());
//    }
}

void MapFrame::regionButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(QObject::sender());
    QMap<QString, QVariant> whereParams;
    whereParams.insert(":id", button->property("regionId"));
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionSelected(region);
}

