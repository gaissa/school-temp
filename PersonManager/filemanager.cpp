#include "filemanager.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>


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

QString FileManager::writeValues()
{
    loadFile = QFileDialog::getSaveFileName(this,
                       QObject::tr("SAVE"),
                       "",
                       QObject::tr("PersonalManager Files (*.pmf)"));

    QFile file(loadFile);
    file.open(QIODevice::WriteOnly);

    QTextStream out(&file);

    for (int i = 0; i < personList.length(); i++)
    {
         out << personList[i] << endl;
    }
    file.close();

    return loadFile;
}

QStringList FileManager::loadValues()
{
    loadFile = QFileDialog::getOpenFileName(this,
               QObject::tr("LOAD"),
               "list",
               QObject::tr("PersonalManager Files (*.pmf)"));

    readValues();
    return loadedList;
}

void FileManager::readValues()
{
    QFile file(loadFile);
    QString line;

    if(!file.open(QIODevice::ReadOnly))
    {
       qDebug() << "error opening file: " << file.error();
    }

    QTextStream inStream(&file);

     do
     {
         line = inStream.readLine();
         loadedList.append(line);
     }
     while (!line.isNull());

    loadedList.removeAt(loadedList.length()-1);

    file.close();
}

QString FileManager::getFileName()
{
    return loadFile;
}
