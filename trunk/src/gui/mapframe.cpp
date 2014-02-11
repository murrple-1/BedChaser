#include "mapframe.h"
#include "ui_mapframe.h"
#include "graphicsthread.h"
#include "../core/datamanager.h"
#include "regionframe.h"

MapFrame::MapFrame(QWidget *parent) :
        QFrame(parent),
        ui(new Ui::MapFrame)
{
    ui->setupUi(this);
    p.load("../deplib/Map_Banner.jpg");
    ui->logoLabel->setPixmap(p);
    setFixedWidth(p.width());

    p.load("../deplib/map.jpg");
    ui->mapLabel->setPixmap(p);
    ui->mapLabel->setFixedSize(p.size());
}

MapFrame::~MapFrame()
{
    delete ui;
}

void MapFrame::on_renfrew_clicked()
{
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    RegionFrame * r = new RegionFrame(LHIN::DataManager::getDataManager().getRegion(0));
    LHIN::GraphicsThread::setCurrentWindowView(r);
}

void MapFrame::on_Lanark_clicked()
{
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    RegionFrame * r = new RegionFrame(LHIN::DataManager::getDataManager().getRegion(1));
    LHIN::GraphicsThread::setCurrentWindowView(r);
}

void MapFrame::on_o_west_clicked()
{
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    RegionFrame * r = new RegionFrame(LHIN::DataManager::getDataManager().getRegion(2));
    LHIN::GraphicsThread::setCurrentWindowView(r);
}

void MapFrame::on_grenville_clicked()
{
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    RegionFrame * r = new RegionFrame(LHIN::DataManager::getDataManager().getRegion(1));
    LHIN::GraphicsThread::setCurrentWindowView(r);
}

void MapFrame::on_o_east_clicked()
{
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    RegionFrame * r = new RegionFrame(LHIN::DataManager::getDataManager().getRegion(4));
    LHIN::GraphicsThread::setCurrentWindowView(r);
}

void MapFrame::on_easternc_clicked()
{
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    RegionFrame * r = new RegionFrame(LHIN::DataManager::getDataManager().getRegion(5));
    LHIN::GraphicsThread::setCurrentWindowView(r);
}

void MapFrame::on_o_centre_clicked()
{
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    RegionFrame * r = new RegionFrame(LHIN::DataManager::getDataManager().getRegion(3));
    LHIN::GraphicsThread::setCurrentWindowView(r);
}

