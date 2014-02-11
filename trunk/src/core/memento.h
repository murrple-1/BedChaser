#ifndef MEMENTO_H
#define MEMENTO_H

#include <QDateTime>

#include "object.h"
#include "map.h"

NS_START

class Memento : public Object
{
public:
    Memento(const QDateTime &, const Map &);
    Memento(const QDateTime &, const std::string &);
    virtual ~Memento();
    virtual std::string toString() const;
    virtual std::string toUIString() const;
    virtual void validate() const throw(Exception);
    const Map & getMap() const;
    std::string getData() const;
    QDateTime getTimeStamp() const;
private:
    void parse(const std::string &);

    QDateTime timestamp;
    Map view;
};

NS_END

#endif // MEMENTO_H
