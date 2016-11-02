#ifndef REGION_H
#define REGION_H

#include <QObject>

#include <QList>
#include <QVariant>

class Region : public QObject
{
    Q_OBJECT
public:
    Region(const QVariant &id, const QString &name, int x, int y, QObject *parent = 0);

    int getID(bool *ok = 0) const;
    const QString & getName() const;
    int getX() const;
    int getY() const;
private:
    QVariant id;
    QString name;
    int x;
    int y;
};

#endif // REGION_H
