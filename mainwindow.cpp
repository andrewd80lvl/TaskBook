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

    signListView = new MouseFilter(ui->listView);
    ui->listView->viewport()->installEventFilter(signListView);

    signDataLabel = new MouseFilter(ui->label);
    ui->label->installEventFilter(signDataLabel);

    connectDb = new DBacsecc();
    connectDb->connectDB("123");

    index_date = new QDate();

    QDate current_date = QDate::currentDate();
    index_date->setDate(current_date.year(),current_date.month(),current_date.day());

    QString date = index_date->toString("dd.MM.yyyy");
    ui->label->setText(date);

    QString filter_date = QString("date='%1'").arg(date);

    qDebug() << filter_date;


    modelSql = new QSqlTableModel(this,*(connectDb->getSqlDatabase()));
    modelSql->setTable("my_task");
    modelSql->setEditStrategy(QSqlTableModel::OnRowChange);
    modelSql->setFilter(filter_date);
    modelSql->select();

    ui->listView->setModel(modelSql);
    ui->listView->setModelColumn(1);

    delegateTaskList = new DelegateListView(ui->listView);
    ui->listView->setItemDelegate(delegateTaskList);

    QScroller::grabGesture(ui->listView->viewport(), QScroller::LeftMouseButtonGesture);

    ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listView->verticalScrollBar()->setSingleStep(5);


    m_buttonAdd = new ButtonAboveWindow(this);
    signAddTask = new MouseFilter(m_buttonAdd);
    m_buttonAdd->installEventFilter(signAddTask);



    connect(this,SIGNAL(resize_main_window()),m_buttonAdd,SLOT(resizeMainWindow()));

    connect(signDataLabel,SIGNAL(sign_left(int,int)),SLOT(sign_left_date(int,int)));
    connect(signDataLabel,SIGNAL(sign_right(int,int)),SLOT(sign_right_date(int,int)));

    connect(signListView,SIGNAL(sign_press(int,int)),SLOT(sign_press(int,int)));
    connect(signListView,SIGNAL(sign_long_touch(int,int)),SLOT(sign_long_touch(int,int)));

    connect(signAddTask,SIGNAL(sign_touch(int,int)),delegateTaskList,SLOT(sign_touch_add_task()));


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

            modelSql->removeRow(m_index.row());
           // connectDb->getSqlDatabase()->commit();

            modelSql->select();
    }

}



void MainWindow::resizeEvent(QResizeEvent *)
{
  emit resize_main_window();
}

void MainWindow::sign_press(int x, int y)
{
    qDebug() << "sign_press";
    QModelIndex m_index = ui->listView->indexAt(QPoint(x,y));

    if(m_index.isValid()){
        emit sign_press_row(x,y,&m_index);
    }

   //  m_index.model()->set;
   //  ui->listView->reset();
}

void MainWindow::sign_long_touch(int x, int y)
{
    qDebug() << "touch_long_press";
    QModelIndex m_index = ui->listView->indexAt(QPoint(x,y));

    if(m_index.isValid()){
        emit sign_long_touch_row(x,y,&m_index);
    }
}


void MainWindow::sign_left_date(int x, int y)
{
    qDebug() << "indexL:";

    QDate current_date = index_date->addDays(1);
    index_date->setDate(current_date.year(),current_date.month(),current_date.day());

    QString date = index_date->toString("dd.MM.yyyy");
    ui->label->setText(date);

    QString filter_date = QString("date='%1'").arg(date);

        modelSql->setFilter(filter_date);
    modelSql->select();
}

void MainWindow::sign_right_date(int x, int y)
{

    QDate current_date = index_date->addDays(-1);
    index_date->setDate(current_date.year(),current_date.month(),current_date.day());

    QString date = index_date->toString("dd.MM.yyyy");

    ui->label->setText(date);

    QString filter_date = QString("date='%1'").arg(date);

    modelSql->setFilter(filter_date);
    modelSql->select();
}


