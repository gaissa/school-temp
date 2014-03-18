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

QStringList FileManager::loadValues()
{
    loadFile = QFileDialog::getOpenFileName(this,
               QObject::tr("LOAD"),
               "list",
               QObject::tr("Text Files (*.txt)"));

    readValues();
    return loadedList;
}

QString FileManager::getFileName()
{
    return loadFile;
}

QString FileManager::writeValues()
{
    QString filename = QFileDialog::getSaveFileName(this,
                       QObject::tr("SAVE"),
                       "",
                       QObject::tr("Text Files (*.txt)"));

    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QTextStream out(&file);

    for (int i = 0; i < personList.length(); i++)
    {
         out << personList[i] << endl;
    }
    file.close();

    return filename;
}

void FileManager::readValues()
{
    QFile file(loadFile);
    QString line;

    if(!file.open(QIODevice::ReadOnly))
    {
       qDebug() << "error opening file: " << file.error();
    }

    QTextStream instream(&file);

     do
     {
         line = instream.readLine();
         loadedList.append(line);
     }
     while (!line.isNull());

    loadedList.removeAt(loadedList.length()-1);

    file.close();
}
