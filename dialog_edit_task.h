#ifndef DIALOGEDITTASK_H
#define DIALOGEDITTASK_H

#include <QDialog>
#include <QEvent>

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


public slots:
    void pushSaveButton();

private:
    Ui::DialogEditTask *ui;


protected:
     virtual void leaveEvent(QEvent * event);

};

#endif // DIALOGEDITTASK_H
