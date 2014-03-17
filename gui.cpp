#include <qDebug>
#include "gui.h"
#include "ui_gui.h"
#include "filemanager.h"


Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    listWidget = ui->listWidget;
    listIndex = -1;
}

Gui::~Gui()
{
    qDebug() << "\nGUI deleted";
    delete ui;

    for (int i = 0; i < list.length(); i++)
    {
        qDebug() << list[i].s->getName();
    }
}

void Gui::on_addStudentButton_clicked()
{
    sname = ui->studentNameEdit->text();
    snumb = ui->studentNumberEdit->text();

    if (sname != "" && snumb != "")
    {
        h.s = new Student(this, sname + ",", snumb);

        list.append(h);
        updateList(list.last(), true);

        ui->studentNameEdit->setText("");
        ui->studentNumberEdit->setText("");
    }
}

void Gui::on_addLecturerButton_clicked()
{
    lname = ui->lecturerNameEdit->text();
    lsala = ui->lecturerSalaryEdit->text().toInt(&ok, 10);

    if (lname != "" && QString(lsala) != "")
    {
        h.l = new Lecturer(this, lname + ",", lsala);

        list.append(h);
        updateList(list.last(), false);

        ui->lecturerNameEdit->setText("");
        ui->lecturerSalaryEdit->setText("");
    }
}

void Gui::updateList(holder h, bool check)
{
    if (check == true)
    {
        QString q = "STUDENT, " +
                    h.s->getName() +
                    " " +
                    h.s->getNumber();

        new QListWidgetItem(QString(q), listWidget);
    }
    else
    {
        QString q = "LECTURER, " +
                    h.l->getName() +
                    " " +
                    QString::number(h.l->getSalary());

        new QListWidgetItem(QString(q), listWidget);
    }
}

void Gui::on_listWidget_clicked(const QModelIndex &index)
{
    listIndex = index.row();

    const QString& s = ui->listWidget->currentItem()->text();
    temp = s.split(',')[0].trimmed();
    temp2 = s.split(',')[1].trimmed();
    temp3 = s.split(',')[2].trimmed();

    if (temp == "LECTURER")
    {
        ui->lecturerNameEdit->setText(temp2);
        ui->lecturerSalaryEdit->setText(temp3);
    }
    if (temp == "STUDENT")
    {
        ui->studentNameEdit->setText(temp2);
        ui->studentNumberEdit->setText(temp3);
    }
}

void Gui::on_deleteButton_clicked()
{
    if (listIndex != -1)
    {
        delete listWidget->takeItem(listIndex);

        if (temp == "LECTURER")
        {
            delete list[listIndex].l;
            list.removeAt(listIndex);
        }
        if (temp == "STUDENT")
        {
            delete list[listIndex].s;
            list.removeAt(listIndex);
        }       
        listIndex = -1;
    }
}

void Gui::on_modifyButton_clicked()
{
    if (listIndex != -1)
    {
        if (temp == "STUDENT")
        {
            sname = ui->studentNameEdit->text();
            snumb = ui->studentNumberEdit->text();

            Student *s = new Student(this, sname + ",", snumb);

            delete list[listIndex].s;
            list[listIndex].s = s;

            QString q = "STUDENT, " +
                        s->getName() +
                        " " +
                        s->getNumber();

            delete listWidget->takeItem(listIndex);
            listWidget->insertItem(listIndex, q);
         }
         if (temp == "LECTURER")
         {
             lname = ui->lecturerNameEdit->text();
             lsala = ui->lecturerSalaryEdit->text().toInt(&ok, 10);

             Lecturer *l = new Lecturer(this, lname + ",", lsala);

             delete list[listIndex].l;
             list[listIndex].l = l;

             QString q = "LECTURER, " +
                         l->getName() +
                         " " +
                         QString::number(l->getSalary());

             delete listWidget->takeItem(listIndex);
             listWidget->insertItem(listIndex, q);
         }
         listIndex = -1;
    }
}

void Gui::on_actionSave_triggered()
{
    FileManager *f = new FileManager();

    for(int i = 0; i < listWidget->count(); ++i)
    {
         f->saveValues(listWidget->item(i)->text());
    }

    f->writeValues();
    delete f;
}

void Gui::on_actionLoad_triggered()
{
    FileManager *f = new FileManager();
    delete f;
}
