#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "gui.h"
#include <QList>


class FileManager : public Gui
{
public:

    FileManager();
    ~FileManager();

    void saveValues(QString q);
    void writeValues();

private:
    QList<QString> personList;

};

#endif // FILEMANAGER_H
