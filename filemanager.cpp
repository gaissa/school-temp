#include "filemanager.h"
#include <QDebug>


FileManager::FileManager()
{
    qDebug() << "FILEMANAGER created";
}

FileManager::~FileManager()
{
    qDebug() << "FILEMANAGER deleted";
}

void FileManager::saveValues(QString q)
{
    personList.append(q);
}

QString FileManager::loadValues()
{
    QString temp;
    return temp;
}

void FileManager::writeValues()
{
    for (int i = 0; i < personList.length(); i++)
    {
        qDebug() << personList[i];
    }
}

void FileManager::readValues()
{

}
