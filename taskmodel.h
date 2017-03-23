#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractListModel>
#include <QSize>
#include <QBrush>
#include <QFont>
#include <QIcon>

#define TASK_ADD_NEW 1
#define TASK_SIMPLE 2


class TaskModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TaskModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const; // количество элементов в модели

    // функция доступа к данным
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    // функция сохранение
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    // функция удаления
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    Qt::ItemFlags flags(const QModelIndex &index) const;

private:

    QStringList task_list;

};

#endif // TASKMODEL_H
