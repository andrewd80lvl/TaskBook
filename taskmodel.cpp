#include "taskmodel.h"



TaskModel::TaskModel(QObject *parent) : QAbstractListModel(parent)
{

    for(int i=0; i < 50; i++)
    {
        task_list << "Задача №" + QString::number(i);
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
        return QSize(0,200);

    /*
    case Qt::BackgroundRole:
        return QBrush(Qt::yellow);
   */

    case Qt::FontRole:
        return QFont("Khmer UI",32,20);

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


Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
     return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}
