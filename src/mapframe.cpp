#include "mapframe.h"

#include <QPainter>
#include <QPushButton>
#include <QGridLayout>

#include "datamanager.h"

MapFrame::MapFrame(QWidget *parent) :
    QFrame(parent)
{
    bannerPixmap.load("images/Map_Banner.jpg");
    mapPixmap.load("images/map.jpg");

    int xOffset = 0;
    int yOffset = bannerPixmap.height();

    QList<QSharedPointer<Region> > regions = DataManager::sharedInstance().getRegions();
    foreach(const QSharedPointer<Region> &region, regions)
    {
        QPushButton *button = new QPushButton(region->getName(), this);
        button->setProperty("regionId", region->getID());
        connect(button, &QPushButton::clicked, this, &MapFrame::regionButtonClicked);
        const QPoint &mapOffset = region->getMapOffset();
        button->move(xOffset + mapOffset.x(), yOffset + mapOffset.y());
    }
}

void MapFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);

    painter.drawPixmap(0, 0, bannerPixmap.width(), bannerPixmap.height(), bannerPixmap);
    painter.drawPixmap(0, bannerPixmap.height(), mapPixmap.width(), mapPixmap.height(), mapPixmap);
}

void MapFrame::regionButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(QObject::sender());
    QMap<QString, QVariant> whereParams;
    whereParams.insert(":id", button->property("regionId"));
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionSelected(*region);
}

