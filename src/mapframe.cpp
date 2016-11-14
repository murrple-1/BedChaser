#include "mapframe.h"
#include "ui_mapframe.h"

#include <QPainter>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsProxyWidget>

#include "datamanager.h"

MapFrame::MapFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MapFrame)
{
    ui->setupUi(this);

    QPixmap bannerPixmap;
    bannerPixmap.load("images/Banner.jpg");
    ui->bannerLabel->setPixmap(bannerPixmap);
    ui->bannerLabel->setAlignment(Qt::AlignCenter);

    QPixmap mapPixmap;
    mapPixmap.load("images/map.jpg");

    QGraphicsScene *scene = new QGraphicsScene(this);

    scene->addPixmap(mapPixmap);
    scene->setSceneRect(QRectF(mapPixmap.rect()));

    QList<QSharedPointer<Region> > regions = DataManager::sharedInstance().getRegions();
    foreach(const QSharedPointer<Region> &region, regions)
    {
        QPushButton *button = new QPushButton(region->getName());
        button->setProperty("regionId", region->getID());
        connect(button, &QPushButton::clicked, this, &MapFrame::showRegionDialog);
        const QPoint &mapOffset = region->getMapOffset();
        QGraphicsProxyWidget *proxyWidget = scene->addWidget(button);
        proxyWidget->setPos(QPointF(mapOffset));
    }

    ui->mapGraphicsView->setScene(scene);
}

void MapFrame::showRegionDialog()
{
    QPushButton *button = qobject_cast<QPushButton *>(QObject::sender());
    QMap<QString, QVariant> whereParams;
    whereParams.insert(":id", button->property("regionId"));
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1).first();
    emit regionSelected(region);
}

