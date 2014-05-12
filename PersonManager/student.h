#ifndef STUDENT_H
#define STUDENT_H

#include <person.h>

class Student : public Person
{
    Q_OBJECT

public:
    Student(QObject *parent, QString n, QString nu);
    ~Student();
    
    QString getNumber();
    void setNumber(QString n);

private:
    QString number;
};

#endif // STUDENT_H
