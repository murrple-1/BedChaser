#include "mapframe.h"
#include "ui_mapframe.h"

#include "datamanager.h"

MapFrame::MapFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MapFrame)
{
    ui->setupUi(this);

    QPixmap bannerPixmap;
    bannerPixmap.load("images/Map_Banner.jpg");
    ui->logoLabel->setPixmap(bannerPixmap);
    setFixedWidth(bannerPixmap.width());

    QPixmap mapPixmap;
    mapPixmap.load("images/map.jpg");
    ui->mapLabel->setPixmap(bannerPixmap);
    ui->mapLabel->setFixedSize(bannerPixmap.size());
}

MapFrame::~MapFrame()
{
    delete ui;
}

void MapFrame::on_renfrew_clicked()
{
    QMap<QString, QString> whereParams;
    whereParams.insert(":id", "0");
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionClicked(*region);
}

void MapFrame::on_Lanark_clicked()
{
    QMap<QString, QString> whereParams;
    whereParams.insert(":id", "1");
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionClicked(*region);
}

void MapFrame::on_o_west_clicked()
{
    QMap<QString, QString> whereParams;
    whereParams.insert(":id", "2");
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionClicked(*region);
}

void MapFrame::on_grenville_clicked()
{
    QMap<QString, QString> whereParams;
    whereParams.insert(":id", "3");
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionClicked(*region);
}

void MapFrame::on_o_east_clicked()
{
    QMap<QString, QString> whereParams;
    whereParams.insert(":id", "4");
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionClicked(*region);
}

void MapFrame::on_easternc_clicked()
{
    QMap<QString, QString> whereParams;
    whereParams.insert(":id", "5");
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionClicked(*region);
}

void MapFrame::on_o_centre_clicked()
{
    QMap<QString, QString> whereParams;
    whereParams.insert(":id", "6");
    QSharedPointer<Region> region = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1, 0).first();
    emit regionClicked(*region);
}

