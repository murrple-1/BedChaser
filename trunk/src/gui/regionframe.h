#ifndef REGIONFRAME_H
#define REGIONFRAME_H

#include <QFrame>
#include "../core/region.h"
#include "QListWidgetItem"

namespace Ui {
    class RegionFrame;
}

class RegionFrame : public QFrame
{
    Q_OBJECT

public:
    explicit RegionFrame(LHIN::Region * const, QWidget *parent = 0);
    ~RegionFrame();
    void updateFacilityList();

private:
    Ui::RegionFrame *ui;
    LHIN::Region * r;

private slots:
    void on_waitinglist_clicked();
    void on_back_clicked();
    void on_listoffacilities_itemDoubleClicked(QListWidgetItem* item);
};

#endif // REGIONFRAME_H
