#include "person.h"
#include <QString>
#include <qDebug>


Person::Person(QObject *parent, QString n) : QObject(parent)
{
    name = n;
    qDebug() << "\nPerson" << name << "created";
}

Person::~Person()
{
    qDebug() << "\nPerson" << name << "deleted";
}

void Person::setName(QString n)
{
    name = QString(n);
}

QString Person::getName()
{
    return name;
}