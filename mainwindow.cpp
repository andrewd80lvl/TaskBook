#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    model = new TaskModel (this);
    ui->listView->setModel(model);

    delegateTaskList = new DelegateListView(ui->listView);
    ui->listView->setItemDelegate(delegateTaskList);
    //ui->listView->viewport()->setAttribute(Qt::WA_Hover);

    ui->listView->show();

    QScroller::grabGesture(ui->listView->viewport(), QScroller::LeftMouseButtonGesture);

    index = ui->stackedWidget->currentIndex();

    ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listView->verticalScrollBar()->setSingleStep(2);

    connect(signListView,SIGNAL(sign_touch(int,int)),SLOT(sign_left(int,int)));
    connect(signStackedWidget,SIGNAL(sign_left(int,int)),SLOT(sign_left_stacked(int,int)));
    connect(signStackedWidget,SIGNAL(sign_right(int,int)),SLOT(sign_right_stacked(int,int)));

    connect(signListView,SIGNAL(touch_press(int,int)),SLOT(touch_press(int,int)));
    connect(signListView,SIGNAL(touch_realese(int,int)),delegateTaskList,SLOT(touch_realese(int,int)));

    connect(this,SIGNAL(touch_press_row(int,int,QModelIndex *)),delegateTaskList,SLOT(touch_press_row(int,int,QModelIndex *)));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::touch_press(int x, int y)
{
    QModelIndex b = ui->listView->indexAt(QPoint(x,y));

    if(b.isValid()){
        emit touch_press_row(x,y,&b);
        //ui->listView->update(b);
    }




}

void MainWindow::sign_left(int x, int y)
{
    qDebug() << x << ":" << y;

    QModelIndex b = ui->listView->indexAt(QPoint(x,y));

    qDebug() << b.isValid();
    qDebug() << b.data();
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


