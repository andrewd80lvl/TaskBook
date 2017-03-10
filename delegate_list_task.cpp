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

QWidget *DelegateListView::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  DialogEditTask *dialog_et = new DialogEditTask(parent);

  dialog_et->show();

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

