#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStringListModel>
#include <QMainWindow>
#include <QDebug>
#include <QSqlTableModel>
#include <QDate>

#include "taskmodel.h"
#include "delegate_list_task.h"
#include "mousefilter.h"
#include "dbacsecc.h"
#include "buttonabovewindow.h"


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

    QDate *index_date; // Текущая (выбранная) дата

    DBacsecc *connectDb;
    QSqlTableModel *modelSql;

    MouseFilter *signListView;
    MouseFilter *signDataLabel;
    MouseFilter *signAddTask;

    DelegateListView   *delegateTaskList;

    ButtonAboveWindow *m_buttonAdd;

private slots:

   void sign_left_date(int x, int y);
   void sign_right_date(int x, int y);
   void sign_press(int x,int y);
   void sign_long_touch(int x,int y);
   void sign_right_task(int x,int y);


signals:
   void sign_press_row(int x,int y,QModelIndex*  index);
   void sign_long_touch_row(int x,int y,QModelIndex*  index);
   void sign_right_index(const QModelIndex& index);
   void resize_main_window();

protected:
    void resizeEvent( QResizeEvent* );

};

#endif // MAINWINDOW_H
