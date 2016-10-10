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
    Region *region = DataManager::sharedInstance().getRegion(0);
    emit regionClicked(*region);
    delete region;
}

void MapFrame::on_Lanark_clicked()
{
    Region *region = DataManager::sharedInstance().getRegion(1);
    emit regionClicked(*region);
    delete region;
}

void MapFrame::on_o_west_clicked()
{
    Region *region = DataManager::sharedInstance().getRegion(2);
    emit regionClicked(*region);
    delete region;
}

void MapFrame::on_grenville_clicked()
{
    Region *region = DataManager::sharedInstance().getRegion(3);
    emit regionClicked(*region);
    delete region;
}

void MapFrame::on_o_east_clicked()
{
    Region *region = DataManager::sharedInstance().getRegion(4);
    emit regionClicked(*region);
    delete region;
}

void MapFrame::on_easternc_clicked()
{
    Region *region = DataManager::sharedInstance().getRegion(5);
    emit regionClicked(*region);
    delete region;
}

void MapFrame::on_o_centre_clicked()
{
    Region *region = DataManager::sharedInstance().getRegion(6);
    emit regionClicked(*region);
    delete region;
}

