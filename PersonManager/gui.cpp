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
}

void Gui::on_addStudentButton_clicked()
{
    sname = ui->studentNameEdit->text().replace(",", "");;
    snumb = ui->studentNumberEdit->text().replace(",", "");;

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
    lname = ui->lecturerNameEdit->text().replace(",", "");
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
        q = "STUDENT, " + h.s->getName() + " " + h.s->getNumber();

        new QListWidgetItem(QString(q), listWidget);
    }
    else
    {
        q = "LECTURER, " + h.l->getName() + " " +
            QString::number(h.l->getSalary());

        new QListWidgetItem(QString(q), listWidget);
    }
}

void Gui::on_listWidget_clicked(const QModelIndex &index)
{
    listIndex = index.row();

    const QString& s = ui->listWidget->currentItem()->text();
    temp  = s.split(',')[0].trimmed();
    temp2 = s.split(',')[1].trimmed();
    temp3 = s.split(',')[2].trimmed();

    if (temp == "LECTURER")
    {
        ui->lecturerNameEdit->setText(temp2.replace(",", ""));
        ui->lecturerSalaryEdit->setText(temp3);
    }
    if (temp == "STUDENT")
    {
        ui->studentNameEdit->setText(temp2.replace(",", ""));
        ui->studentNumberEdit->setText(temp3.replace(",", ""));
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

            q = "STUDENT, " + s->getName() + " " + s->getNumber();

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

             q = "LECTURER, " + l->getName() + " " +
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

    this->setWindowTitle(f->writeValues());
    delete f;
    this->setWindowState(Qt::WindowActive);
}

void Gui::on_actionLoad_triggered()
{
    listWidget->clear();

    for (int i = 0; i < list.length(); i++)
    {
        delete &list.at(i);
    }

    list.clear();

    FileManager *f = new FileManager();
    QStringList qq = f->loadValues();

    for (int i = 0; i < qq.length(); i++)
    {
        temp  = qq[i].split(",")[0];
        temp2 = qq[i].split(",")[1];
        temp3 = qq[i].split(",")[2];

        if (temp == "STUDENT")
        {
            h.s = new Student(this, temp2 + ",", temp3);
            list.append(h);
        }
        if (temp == "LECTURER")
        {
            h.l = new Lecturer(this, temp2 + ",", temp3.toInt());
            list.append(h);
        }
        new QListWidgetItem(qq[i], listWidget);
    }

    this->setWindowTitle(f->getFileName());
    delete f;
    this->setWindowState(Qt::WindowActive);
}
