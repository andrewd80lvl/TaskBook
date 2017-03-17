#include "dialog_edit_task.h"
#include "ui_dialogedittask.h"
#include "unistd.h"

#include <QDebug>



DialogEditTask::DialogEditTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditTask)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModal);
    setAttribute(Qt :: WA_DeleteOnClose);

    connect(ui->pushButton,SIGNAL(pressed()),this,SLOT(pushSaveButton()));
}

DialogEditTask::~DialogEditTask()
{
    delete ui;
}

void DialogEditTask::setData(QString data)
{

    ui->plainTextEdit->setPlainText(data);
}

QString DialogEditTask::getData()
{
    return ui->plainTextEdit->toPlainText();
}


void DialogEditTask::pushSaveButton()
{
    qDebug() << "pushSaveButton";

    done(0);
}


void DialogEditTask::leaveEvent(QEvent *event)
{
      qDebug() << "lost focus:" << event->type();

      //done(0);
}







