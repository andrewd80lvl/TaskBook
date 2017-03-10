#ifndef DIALOGEDITTASK_H
#define DIALOGEDITTASK_H

#include <QDialog>

namespace Ui {
class DialogEditTask;
}

class DialogEditTask : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditTask(QWidget *parent = 0);
    ~DialogEditTask();

    void setData(QString data);
    QString getData();


private:
    Ui::DialogEditTask *ui;
};

#endif // DIALOGEDITTASK_H
