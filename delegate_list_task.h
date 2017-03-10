#ifndef DELEGATE_LIST_TASK_H
#define DELEGATE_LIST_TASK_H

#include <QtWidgets>
#include <QObject>
#include <QItemDelegate>
#include <QStaticText>

#include "dialogedittask.h"

// ======================================================================
class DelegateListView : public QStyledItemDelegate {

    Q_OBJECT

public:

    DelegateListView(QObject* pobj);

    void paint(QPainter*                   pPainter,
               const QStyleOptionViewItem& option,
               const QModelIndex&          index
               ) const;


    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const ;

    void setEditorData(QWidget *editor, const QModelIndex &index) const ;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const ;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const ;



private:

    Ui::DialogEditTask *ui_dialog;

    QListView *obj_view;
    int  task_edit_row;


public slots:

    void touch_press_row(int x, int y, QModelIndex *index);
    void touch_realese(int x,int y);

};



#endif // DELEGATELISTVIEW_H
