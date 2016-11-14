#ifndef MAPFRAME_H
#define MAPFRAME_H

namespace Ui {
class MapFrame;
}

#include <QFrame>

#include <QSharedPointer>

class Region;

class MapFrame : public QFrame
{
    Q_OBJECT
public:
    MapFrame(QWidget *parent = 0);
private:
    Ui::MapFrame *ui;
private slots:
    void showRegionDialog();
signals:
    void regionSelected(const QSharedPointer<Region> &);
};

#endif // MAPFRAME_H
