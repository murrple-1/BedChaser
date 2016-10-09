#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <QFrame>

namespace Ui {
    class MapFrame;
}

class Region;

class MapFrame : public QFrame
{
    Q_OBJECT
public:
    MapFrame(QWidget *parent = 0);
    ~MapFrame();
private:
    Ui::MapFrame *ui;

    QPixmap p;
private slots:
    void on_o_centre_clicked();
    void on_easternc_clicked();
    void on_o_east_clicked();
    void on_grenville_clicked();
    void on_o_west_clicked();
    void on_Lanark_clicked();
    void on_renfrew_clicked();
signals:
    void regionClicked(const Region &);
};

#endif // MAPFRAME_H
