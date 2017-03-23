#include "delegate_list_task.h"

#include <QPainter>
#include <QApplication>
#include <QLinearGradient>
#include <QItemDelegate>
#include <QBrush>

#include "mousefilter.h"


DelegateListView::DelegateListView(QObject* pobj = 0)
    : QStyledItemDelegate(pobj)
{

    obj_view = dynamic_cast<QListView*>( pobj );
    task_press_row = -1;
    task_sign_left = -1;

}

void DelegateListView::paint(QPainter* pPainter,
           const QStyleOptionViewItem& option,
           const QModelIndex&          index
           ) const
{

    QRect  rect = option.rect;

    QPen  pen;

    pen.setWidth(1);

    QColor color;

    if(index.data(Qt::UserRole).toInt() != 1)
        color =  Qt::white;
    else
        color =  Qt::lightGray;


    if(index.row() == task_sign_left )
    {
       color = Qt::green;
       
    }

    if(index.row() == task_press_row )
    {
        color = Qt::gray;
        //pen.setColor(Qt::red);


    }else{

        //pen.setColor(Qt::black);
    }


    pPainter->setPen(pen);

    pPainter->fillRect(rect,color);
    
    pPainter->drawRect(rect);

}

QWidget *DelegateListView::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  DialogEditTask *dialog_et = new DialogEditTask(parent);

  return dialog_et;
}

void DelegateListView::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    DialogEditTask *dialog_et = static_cast< DialogEditTask*>(editor);

    if(index.isValid())
        dialog_et->setData(index.data().toString());

}

void DelegateListView::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    qDebug() << "setModelData";

    DialogEditTask *dialog_et = static_cast< DialogEditTask*>(editor);

    model->setData(index,dialog_et->getData());

}

void DelegateListView::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void DelegateListView::sign_press_row(int x, int y,QModelIndex*  index)
{
    qDebug() << "sign_touch_row:" << index->row() ;

    if(index->isValid()){

        int row_was_pressed = task_press_row;

        task_press_row = index->row();
        obj_view->update(*index);

        QModelIndex  index_was = index->model()->index(row_was_pressed,0);

        if(index_was.isValid())
           obj_view->update(index_was);
    }
}

void DelegateListView::sign_long_touch_row(int x, int y,QModelIndex*  index)
{
    qDebug() << "sign_long_touch_row:" << index->row() ;

    if(index->isValid())
      obj_view->edit(*index);
}

void DelegateListView::sign_right_task(int x, int y)
{
    qDebug() << "sign_left_task";

    QModelIndex indx_task = obj_view->indexAt(QPoint(x,y));

    if(indx_task.isValid())
    {
        int was_row = task_sign_left;

        task_sign_left = indx_task.row();
        obj_view->update(indx_task);

        QModelIndex  index_was = indx_task.model()->index(was_row,0);

        if(index_was.isValid())
           obj_view->update(index_was);
    }

}
