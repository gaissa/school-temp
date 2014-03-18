#include <qDebug>
#include "lecturer.h"


Lecturer::Lecturer(QObject *parent,  QString n, int s) :
          Person(parent, n)
{
    setName(n);
    setSalary(s);
    qDebug() << "\nLecturer" << "created";
}

Lecturer::~Lecturer()
{
     qDebug() << "\nLecturer" << "deleted";
}

void Lecturer::setSalary(int s)
{
   salary = s;
}

int Lecturer::getSalary()
{
    return salary;
}
