#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <QFrame>

class Region;

class MapFrame : public QFrame
{
    Q_OBJECT
public:
    MapFrame(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
private:
    QPixmap bannerPixmap;
    QPixmap mapPixmap;
private slots:
    void regionButtonClicked();
signals:
    void regionSelected(const Region &);
};

#endif // MAPFRAME_H
