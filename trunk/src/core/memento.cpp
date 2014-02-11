#include "memento.h"
#include "../utils/stringbuilder.h"

NS_START

        Memento::Memento(const QDateTime & dt, const Map & m):
        timestamp(dt), view(m)
{}

Memento::Memento(const QDateTime & dt, const std::string & data):
        timestamp(dt)
{
    parse(data);
}

Memento::~Memento()
{}

std::string Memento::toString() const
{
    StringBuilder sb;
    sb.append(std::string("Memento: "));
    sb.append(std::string("timestamp=")).append(timestamp.toString().toStdString()).append(' ');
    return sb.toString();
}

std::string Memento::toUIString() const
{
    return "Memento: " + timestamp.toString().toStdString();
}

void Memento::validate() const throw(Exception)
{

}

const Map & Memento::getMap() const {
    return view;
}

QDateTime Memento::getTimeStamp() const {
    return timestamp;
}

std::string Memento::getData() const {
    return std::string();
}

void Memento::parse(const std::string & data) {

}

NS_END
