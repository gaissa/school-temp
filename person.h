#ifndef PERSON_H
#define PERSON_H

#include <QObject>


class Person : public QObject
{
    Q_OBJECT

public:
    Person(QObject *parent, QString n);
    ~Person();

    QString getName();
    void setName(QString n);

private:
    QString name;

signals:

public slots:
};

#endif // PERSON_H