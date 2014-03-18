#include <QApplication>
#include <QString>
#include <qDebug>
#include "person.h"
#include "student.h"
#include "lecturer.h"
#include "gui.h"


// Application where you can
// manage persons// (lecturers and students).
// You can add, delete and modify a person.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Gui g;  
    g.setWindowTitle(" ");
    g.show();

    return a.exec();
}
