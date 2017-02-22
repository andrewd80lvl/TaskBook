#include "delegate_list_task.h"

#include <QPainter>
#include <QApplication>
#include <QDate>
#include <QLinearGradient>
#include <QItemDelegate>
#include <QBrush>



DelegateListView::DelegateListView(QObject* pobj = 0)
    : QStyledItemDelegate(pobj)
{

    obj_view = dynamic_cast<QListView*>( pobj );
    task_edit_row = -1;

}

void DelegateListView::paint(QPainter* pPainter,
           const QStyleOptionViewItem& option,
           const QModelIndex&          index
           ) const
{
    QRect  rect = option.rect;

    QPen  pen;
    QColor color(Qt::lightGray);

    pen.setWidth(2);

    if(index.row() == task_edit_row )
    {
        color = Qt::gray;
        pen.setColor(Qt::red);

    }else{

        pen.setColor(Qt::black);
    }


    pPainter->setPen(pen);

    pPainter->fillRect(rect,color);
    pPainter->drawRect(rect);


    QStyledItemDelegate::paint(pPainter, option, index);
}

void DelegateListView::touch_press_row(int x, int y,QModelIndex*  index)
{

    qDebug() << "PRESS:" << index->row() ;

    obj_view->update(index->model()->index(task_edit_row,0));

    task_edit_row = index->row();

    if(index->isValid())
     obj_view->update(*index);

}

void DelegateListView::touch_realese(int x, int y)
{
    //press_row = -1;
    qDebug() << "REALESE";
}

