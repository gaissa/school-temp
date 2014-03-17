#ifndef LECTURER_H
#define LECTURER_H

#include <person.h>


class Lecturer : public Person
{
    Q_OBJECT

public:
    Lecturer(QObject *parent, QString n, int s);
    ~Lecturer();
    
    int getSalary();
    void setSalary(int s);

private:
    int salary;
};

#endif // LECTURER_H
