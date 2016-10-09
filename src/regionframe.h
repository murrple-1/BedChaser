#ifndef REGIONFRAME_H
#define REGIONFRAME_H

#include <QFrame>

namespace Ui {
    class RegionFrame;
}

class QListWidgetItem;

class Region;

class RegionFrame : public QFrame
{
    Q_OBJECT
public:
    RegionFrame(Region *, QWidget *parent = 0);
    ~RegionFrame();

    void updateFacilityList();
private:
    Ui::RegionFrame *ui;

    Region * r;
private slots:
    void on_waitinglist_clicked();
    void on_back_clicked();
    void on_listoffacilities_itemDoubleClicked(QListWidgetItem* item);
signals:
    void backButtonPressed();
};

#endif // REGIONFRAME_H
