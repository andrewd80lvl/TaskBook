#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStringListModel>
#include <QMainWindow>
#include <QDebug>

#include "taskmodel.h"
#include "delegate_list_task.h"
#include "mousefilter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    TaskModel *model;
    MouseFilter *signListView;
    MouseFilter *signStackedWidget;
    DelegateListView   *delegateTaskList;

private slots:
   void sign_left(int x, int y);
   void sign_left_stacked(int x, int y);
   void touch_press(int x,int y);

signals:
   void touch_press_row(int x,int y,QModelIndex*  index);


};

#endif // MAINWINDOW_H
