#include <qDebug>
#include "student.h"


Student::Student(QObject *parent, QString n, QString nu) :
         Person(parent, n)
{   
    setName(n);
    setNumber(nu);
    qDebug() << "\nStudent" << number << "created";
}

Student::~Student()
{
     qDebug() << "\nStudent" << number << "deleted";
}

void Student::setNumber(QString n)
{
    number = QString(n);
}

QString Student::getNumber()
{
    return number;
}
