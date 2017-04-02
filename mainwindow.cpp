#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbacsecc.h"
#include <QScroller>
#include <QScrollArea>
#include <QScrollBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    signStackedWidget = new MouseFilter(ui->stackedWidget);
    ui->stackedWidget->installEventFilter(signStackedWidget);

    signListView = new MouseFilter(ui->listView);
    ui->listView->viewport()->installEventFilter(signListView);

    connectDb = new DBacsecc();
    connectDb->connectDB("123");

    modelSql = new QSqlTableModel(this,*(connectDb->getSqlDatabase()));
    modelSql->setTable("my_task");
    modelSql->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelSql->select();

    //modelTaskBook = new TaskModel(this);
    //ui->listView->setModel(modelTaskBook);

    ui->listView->setModel(modelSql);
    ui->listView->setModelColumn(1);


    delegateTaskList = new DelegateListView(ui->listView);
    ui->listView->setItemDelegate(delegateTaskList);


    QScroller::grabGesture(ui->listView->viewport(), QScroller::LeftMouseButtonGesture);

    index = ui->stackedWidget->currentIndex();

    ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listView->verticalScrollBar()->setSingleStep(5);


    connect(signStackedWidget,SIGNAL(sign_left(int,int)),SLOT(sign_left_stacked(int,int)));
    connect(signStackedWidget,SIGNAL(sign_right(int,int)),SLOT(sign_right_stacked(int,int)));

    connect(signListView,SIGNAL(sign_press(int,int)),SLOT(sign_press(int,int)));
    connect(signListView,SIGNAL(sign_long_touch(int,int)),SLOT(sign_long_touch(int,int)));


    connect(this,SIGNAL(sign_press_row(int,int,QModelIndex *)),delegateTaskList,SLOT(sign_press_row(int,int,QModelIndex *)));
    connect(this,SIGNAL(sign_long_touch_row(int,int,QModelIndex *)),delegateTaskList,SLOT(sign_long_touch_row(int,int,QModelIndex *)));
    connect(this,SIGNAL(sign_long_touch_row(int,int,QModelIndex *)),delegateTaskList,SLOT(sign_long_touch_row(int,int,QModelIndex *)));


    connect(signListView,SIGNAL(sign_right(int,int)),SLOT(sign_right_task(int,int)));

    //connect(model(), SIGNAL(needUpdate(QModelIndex)), this, SLOT(update(const QModelIndex &)));
    //connect(ui->listView, SIGNAL(needUpdate(QModelIndex)), itemDelegate(), SIGNAL(sizeHintChanged(QModelIndex)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sign_right_task(int x,int y)
{
    qDebug() << "sign_right_task";
    QModelIndex m_index = ui->listView->indexAt(QPoint(x,y));

    if(m_index.isValid()){

        if(m_index.data(Qt::UserRole).toInt() != 1)
            //modelTaskBook->removeRow(m_index.row(),m_index);
            modelSql->removeRow(m_index.row());
            connectDb->getSqlDatabase()->commit();

            modelSql->select();
    }

}

void MainWindow::sign_press(int x, int y)
{
    qDebug() << "sign_press";
    QModelIndex m_index = ui->listView->indexAt(QPoint(x,y));

    if(m_index.isValid()){
        emit sign_press_row(x,y,&m_index);
    }



   //m_index.model()->set

   // ui->listView->reset();

}

void MainWindow::sign_long_touch(int x, int y)
{
    qDebug() << "touch_long_press";
    QModelIndex m_index = ui->listView->indexAt(QPoint(x,y));

    if(m_index.isValid()){
        emit sign_long_touch_row(x,y,&m_index);


    }




}


void MainWindow::sign_left_stacked(int x, int y)
{
    index--;

    qDebug() << "indexL:" <<  index ;

    if(index < 0)
       index = 1;


    qDebug() << "indexL:" <<  index ;
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::sign_right_stacked(int x, int y)
{

    index++;

    if(index > 1)
       index = 0;

    qDebug() << "indexR:" <<  index ;
    ui->stackedWidget->setCurrentIndex(index);
}


