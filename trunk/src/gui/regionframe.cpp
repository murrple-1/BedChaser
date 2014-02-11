#include "regionframe.h"
#include "ui_regionframe.h"
#include "graphicsthread.h"
#include "mapframe.h"
#include "../core/datamanager.h"
#include "editfacilitydialog.h"
#include "waitinglistdialog.h"
#include "QListWidget"
#include "QsLog.h"

RegionFrame::RegionFrame(LHIN::Region * const lr, QWidget *parent) :
        QFrame(parent),
        ui(new Ui::RegionFrame),
        r(lr)
{
    ui->setupUi(this);
    QPixmap p;
    p.load("../deplib/Map_Banner.jpg");
    ui->logoLabel->setPixmap(p);
    setFixedWidth(p.width());

    QPixmap * q = LHIN::DataManager::getDataManager().getRegionImage(r->getID());
    ui->mapLabel->setPixmap(*q);
    ui->mapLabel->setFixedSize(q->size());
    delete q;
    updateFacilityList();
}

RegionFrame::~RegionFrame()
{
    delete ui;
}

void RegionFrame::on_back_clicked()
{
    delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
    MapFrame * mf = new MapFrame();
    LHIN::GraphicsThread::setCurrentWindowView(mf);
}

void RegionFrame::updateFacilityList()
{

    QPixmap * f = new QPixmap("../deplib/FacilityLogo.jpg");

    for(int i = 0; i < r->getLocations().size(); i++) {
        ui->listoffacilities->addItem(QString(r->getLocations().at(i)->getName().c_str()));

        QLabel * newlogo = new QLabel(this);
        QLabel * newlogoname = new QLabel(this);

        float xPer = r->getLocations().at(i)->getX() / 100.0f;
        float yPer = r->getLocations().at(i)->getY() / 100.0f;

        int X = (xPer * ui->mapLabel->width()) + ui->mapLabel->x();
        int Y = (yPer * ui->mapLabel->height()) + ui->mapLabel->y();

        newlogo->setGeometry(X, Y, 60, 17);
        newlogo->setPixmap(*f);
        newlogoname->setGeometry(X + 15, Y, 170, 17);
        newlogoname->setText(r->getLocations().at(i)->getName().c_str());
    }
}

void RegionFrame::on_listoffacilities_itemDoubleClicked(QListWidgetItem* item)
{
    int i = ui->listoffacilities->row(item);
    EditFacilityDialog * ef = new EditFacilityDialog(r->getLocations().at(i), this);
    ef->exec();
    delete ef;
}

void RegionFrame::on_waitinglist_clicked()
{
    WaitingListDialog * wf = new WaitingListDialog(r, this);
    wf->exec();
    delete wf;
}
