#include "delegatelistview.h"


SimpleDelegate::SimpleDelegate(QObject* pobj = 0) : QStyledItemDelegate(pobj)
{
}

void SimpleDelegate::paint(QPainter*     pPainter,
               const QStyleOptionViewItem& option,
               const QModelIndex&          index
              ) const
{
        if (option.state & QStyle::State_MouseOver) {

            QRect           rect = option.rect;
            QLinearGradient gradient(0, 0, rect.width(), rect.height());


            gradient.setColorAt(0, Qt::white);
            gradient.setColorAt(0.5, Qt::blue);
            gradient.setColorAt(1, Qt::green);
            pPainter->setBrush(gradient);
            pPainter->drawRect(rect);
        }
        QStyledItemDelegate::paint(pPainter, option, index);


}

