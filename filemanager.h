#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QList>


class FileManager
{

public:
    FileManager();
    ~FileManager();

    void saveValues(QString q);
    QString loadValues();

    void writeValues();
    void readValues();

private:
    QList<QString> personList;

};

#endif // FILEMANAGER_H
