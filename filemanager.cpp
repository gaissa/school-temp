#include "filemanager.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
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
               QObject::tr("Open File"), "lista.txt", QObject::tr("Text Files (*.txt)"));

    readValues();
    return loadedList;
}

QString FileManager::writeValues()
{
    QStringList nameFilter("*.txt");
    QDir directory("./");
    QStringList txtFiles = directory.entryList(nameFilter);

    if (txtFiles.length() != 0)
    {
        saveFile = txtFiles[txtFiles.length()-1];

        int a = saveFile.split("-")[0].toInt();
        a++;

        saveFile = QString::number(a);
    }
    else
    {
        saveFile = "1";
    }

    QFile file("0" + saveFile + "-list.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    for (int i = 0; i < personList.length(); i++)
    {
         out << personList[i] << endl;
    }
    file.close();

    return "0" + saveFile + "-list.txt";
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

     do {
         line = instream.readLine();
         loadedList.append(line);
     } while (!line.isNull());

    loadedList.removeAt(loadedList.length()-1);

    file.close();
}
