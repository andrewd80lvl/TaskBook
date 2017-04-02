#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStringListModel>
#include <QMainWindow>
#include <QDebug>
#include <QSqlTableModel>

#include "taskmodel.h"
#include "delegate_list_task.h"
#include "mousefilter.h"
#include "dbacsecc.h"


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

    //TaskModel *modelTaskBook;
    DBacsecc *connectDb;
    QSqlTableModel *modelSql;

    MouseFilter *signListView;
    MouseFilter *signStackedWidget;
    DelegateListView   *delegateTaskList;

    int index;

private slots:

   void sign_left_stacked(int x, int y);
   void sign_right_stacked(int x, int y);
   void sign_press(int x,int y);
   void sign_long_touch(int x,int y);
   void sign_right_task(int x,int y);

signals:
   void sign_press_row(int x,int y,QModelIndex*  index);
   void sign_long_touch_row(int x,int y,QModelIndex*  index);
   void sign_right_index(const QModelIndex& index);


};

#endif // MAINWINDOW_H
