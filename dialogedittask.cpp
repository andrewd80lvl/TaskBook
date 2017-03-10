#include "dialogedittask.h"
#include "ui_dialogedittask.h"



DialogEditTask::DialogEditTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditTask)
{
    ui->setupUi(this);


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
