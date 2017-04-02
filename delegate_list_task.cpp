#include "delegate_list_task.h"

#include <QPainter>
#include <QApplication>
#include <QLinearGradient>
#include <QItemDelegate>
#include <QBrush>

#include "mousefilter.h"

#define STRIPE_WIDTH 30

DelegateListView::DelegateListView(QObject* pobj = 0)
    : QStyledItemDelegate(pobj)
{

    obj_view = dynamic_cast<QListView*>( pobj );
    task_press_row = -1;
    task_sign_left = -1;

}

void DelegateListView::drawItemBackground( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{

    painter->save();

    painter->setClipRect(option.rect);
    painter->setOpacity(0.2);
/*
    QColor baseColor;
    if(
        (index.flags() & Qt::ItemFlag(QvAbstractListItem::DownloadedNeedRestart))
        || (index.flags() & Qt::ItemFlag(QvAbstractListItem::UpdatedNeedRestart))
        )
        baseColor = QColor(0x4C, 0xBB,0x17);

    if(
        (index.flags() & Qt::ItemFlag(QvAbstractListItem::EnabledNeedRestart))
        || (index.flags() & Qt::ItemFlag(QvAbstractListItem::DisabledNeedRestart))
        || (index.flags() & Qt::ItemFlag(QvAbstractListItem::RemovedNeedRestart))
        )
 */
   QColor baseColor;
   baseColor = QColor(0xBa, 0xA4,0x16);



    baseColor.setAlpha(200);
    painter->setBrush(baseColor);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->translate(option.rect.topLeft());
    painter->save();
    painter->translate(0, -STRIPE_WIDTH);
    int count = option.rect.width() / (STRIPE_WIDTH *2)  + 2;

    for(int i =0; i < count; ++i)
    {
        painter->save();
        painter->rotate(30);
        painter->drawRect(0,0, STRIPE_WIDTH *.8, 1.5 * option.rect.height());
        painter->restore();
        painter->translate(STRIPE_WIDTH*2, 0);
    }
    painter->restore();

    QRect r = option.rect;
    r.moveTo(0,0);
    painter->setOpacity(1);
    QLinearGradient grad(QPointF(0, r.height()/5), QPointF(0, r.height()/5 * 3));
    QLinearGradient rgrad(grad);
    grad.setColorAt(0, QColor(0xFF, 0xFF, 0xFF, 60));
    grad.setColorAt(1, QColor(Qt::white));

    painter->fillRect(r, QBrush(grad));
    painter->restore();
}

void DelegateListView::paintHeader( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{

    QPainter &p = *painter;
    p.save();
    p.setClipRect(option.rect);
    p.setPen(QColor(77, 77, 77));

    // рисуем текст
    QRect tr;
    QString name = index.data(Qt::DisplayRole).toString();

    QFont f = option.font;
    f.setPointSize(23);
    f.setWeight(QFont::Bold);
    f.setFamily("Khmer UI");
    QFontMetrics fm(f);
    tr = fm.boundingRect(name);
    p.setFont(f);

    p.drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft, name);

    p.restore();
}

void DelegateListView::paintDescription( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QPainter &p = *painter;
    p.save();

    QString desc = "AAAaaaa"; //index.data(QvObjectModel::DetailRole).toString();
    QFont f = option.font;
    f = option.font;
    f.setWeight(QFont::DemiBold);
    p.setFont(f);
    p.drawText(option.rect, Qt::AlignBottom | Qt::AlignRight, desc);
}


void DelegateListView::paint(QPainter* pPainter,
           const QStyleOptionViewItem& option,
           const QModelIndex&          index
           ) const
{

    QString text = index.data().toString();
    QRectF r = option.rect;
    pPainter->save();
    pPainter->setPen(Qt::SolidLine);

    //pPainter->setBrush(QColor(220,220,250));
    pPainter->drawRect(r);

    pPainter->restore();

    if(index.row() == task_press_row )
    {
        drawItemBackground(pPainter,option,index);
        paintDescription(pPainter,option,index);

    }


    paintHeader(pPainter,option,index);
    //pPainter->drawText(r, Qt::AlignJustify | Qt::AlignVCenter | Qt::TextWordWrap, text);
}

QSize DelegateListView::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QSize size = QStyledItemDelegate::sizeHint(option, index);

    size.setHeight(250);

    if(index.row() == task_press_row)
    {
        size.setHeight(350);
    }


    return size;

}

QWidget *DelegateListView::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  //DialogEditTask *dialog_et = new DialogEditTask(parent);

  newEditForm * new_form = new newEditForm();

  new_form->setParent(parent,Qt::Window);
  new_form->setWindowModality(Qt::WindowModal);

  new_form->resize(QSize(1080,1860));
  new_form->move(QPoint(QPoint(0,1860)));


  return new_form;
}



bool DelegateListView::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    /*
    Q_UNUSED(model);
    Q_UNUSED(option);
    Q_UNUSED(index);
*/
    qDebug() << event;

    return false;
}

void DelegateListView::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QPropertyAnimation *animation = new QPropertyAnimation(editor, "pos", obj_view);
    animation->setDuration(2000);
    animation->setStartValue(QPoint(0,1860));
    animation->setEndValue(QPoint(0,0));
    animation->start();
}

void DelegateListView::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    newEditForm *edit_form = static_cast<newEditForm*>(editor);

    if(index.isValid())
        edit_form->setData(index.data().toString());

}

void DelegateListView::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    qDebug() << "setModelData";
    newEditForm *edit_form = static_cast< newEditForm*>(editor);
    model->setData(index,edit_form->getData());

    editor->close();

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

    emit sizeHintChanged(*index);

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
