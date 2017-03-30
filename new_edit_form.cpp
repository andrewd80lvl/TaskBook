#include "new_edit_form.h"
#include "ui_new_edit_form.h"

newEditForm::newEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::new_edit_form)
{
    ui->setupUi(this);
}

newEditForm::~newEditForm()
{
    delete ui;
}

void newEditForm::setData(QString task)
{
   ui->plainTextEdit->setPlainText(task);
}

QString newEditForm::getData()
{
    return ui->plainTextEdit->toPlainText();
}
