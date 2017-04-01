#ifndef DBACSECC_H
#define DBACSECC_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include <QDebug>
#include <QStandardPaths>

class DBacsecc
{
public:
    DBacsecc();

    bool connectDB(QString db_name);
    bool getResultQuery(QString sql_query,QSqlQuery &sqlQuery);

private:
    QSqlDatabase *p_sdb;

};

#endif // DBACSECC_H
