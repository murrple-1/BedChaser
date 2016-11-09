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
    void waitingListClicked();
    void backButtonClicked();
    void facilityListItemDoubleClicked(QListWidgetItem* item);
signals:
    void goBack();
};

#endif // REGIONFRAME_H
