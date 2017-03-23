#include "taskmodel.h"

#include <QDebug>


TaskModel::TaskModel(QObject *parent) : QAbstractListModel(parent)
{

    QModelIndex idx;
    idx.sibling(0,0);

    task_list << "Добавить задачу";
    QVariant add_new();
    setData(idx,add_new,Qt::UserRole);

    for(int i=0; i < 5; i++)
    {
        task_list << "Задача № " + QString::number(i);
    }

}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    return task_list.count();
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    switch(role)
    {

    case Qt::DisplayRole:
        return QVariant(task_list.at(index.row()));

    case Qt::SizeHintRole:
        return QSize(0,150);

    case Qt::DecorationRole:
        return QIcon(":/images/icons/icon.png");

    case Qt::BackgroundRole:
         return QBrush(Qt::yellow);

    case Qt::FontRole:
        return QFont("Khmer UI",28,true);

    case Qt::UserRole:

        if(index.row() == 0)
            return TASK_ADD_NEW;
        else
            return TASK_SIMPLE;

    default:
        return QVariant();

    }
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole)
        task_list.replace(index.row(),value.toString());

    return true;
}

bool TaskModel::removeRows(int row, int count, const QModelIndex &parent)
{
   Q_UNUSED(parent);

   qDebug() << "removeRows";

   if((row + count) > task_list.count()){
       qCritical() << "error removeRows";
       return false;
   }

   // tell QT what you will be doing
   beginRemoveRows(QModelIndex(),row,(row + count)-1);

   for(int i = row; i < (count + row); i++){
       task_list.removeAt(i);
   }

   endRemoveRows();

   return true;
}


Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
     return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

