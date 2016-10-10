#ifndef REGIONFRAME_H
#define REGIONFRAME_H

#include <QFrame>

namespace Ui {
    class RegionFrame;
}

#include <QSharedPointer>

class QListWidgetItem;

class Region;

class RegionFrame : public QFrame
{
    Q_OBJECT
public:
    RegionFrame(const QSharedPointer<Region> &, QWidget *parent = 0);
    ~RegionFrame();
private:
    void updateFacilityList();

    Ui::RegionFrame *ui;

    QSharedPointer<Region> region;
private slots:
    void on_waitinglist_clicked();
    void on_back_clicked();
    void on_listoffacilities_itemDoubleClicked(QListWidgetItem* item);
signals:
    void backButtonPressed();
};

#endif // REGIONFRAME_H
