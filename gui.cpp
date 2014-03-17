#include <qDebug>
#include "gui.h"
#include "ui_gui.h"


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
    QString sname = ui->studentNameEdit->text();
    QString snumb = ui->studentNumberEdit->text();

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
    QString lname = ui->lecturerNameEdit->text();
    int lsala = ui->lecturerSalaryEdit->text().toInt(&ok, 10);

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
    QString temp2 = s.split(',')[1].trimmed();
    QString temp3 = s.split(',')[2].trimmed();

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
            QString sname = ui->studentNameEdit->text();
            QString snumb = ui->studentNumberEdit->text();

            Student *s = new Student(this, sname + ",", snumb);

            list[listIndex].s->setName(sname);
            list[listIndex].s->setNumber(snumb);

            QString q = "STUDENT, " +
                        s->getName() +
                        " " +
                        s->getNumber();

            delete listWidget->takeItem(listIndex);
            listWidget->insertItem(listIndex, q);
         }
         if (temp == "LECTURER")
         {
             QString lname = ui->lecturerNameEdit->text();
             int lsala = ui->lecturerSalaryEdit->text().toInt(&ok, 10);

             Lecturer *l = new Lecturer(this, lname + ",", lsala);

             list[listIndex].l->setName(lname);
             list[listIndex].l->setSalary(lsala);

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
