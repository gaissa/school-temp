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

void FileManager::setValues(QString q)
{
    personList.append(q);
}

void FileManager::printValues()
{
    for (int i = 0; i < personList.length(); i++)
    {
        qDebug() << personList[i];
    }
}
