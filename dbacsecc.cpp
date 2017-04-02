#include "dbacsecc.h"

DBacsecc::DBacsecc()
{

}

DBacsecc::~DBacsecc()
{
    p_sdb->close();
}

bool DBacsecc::connectDB(QString db_name)
{

    p_sdb = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));


#ifdef ANDROID

    QFile dfile("assets:/db/my_objective.db3");
    QString filePath = QStandardPaths::writableLocation( QStandardPaths::StandardLocation::AppLocalDataLocation );

    filePath.append( "/my_objective.db3");

    if (!dfile.exists()) {
        if( QFile::exists( filePath ) )
            qDebug() << QFile::remove( filePath );

        if( dfile.copy( filePath ) )
            qDebug() << QFile::setPermissions( filePath, QFile::WriteOwner | QFile::ReadOwner );

    }

    qDebug() << filePath;
    p_sdb->setDatabaseName( filePath );
#else
    p_sdb->setDatabaseName("db\\my_objective.db3");
#endif

    if (!p_sdb->open()){

        qDebug() << "Error open db:"  << p_sdb->lastError().text();

        return false;
    }

    if(p_sdb->isOpen()){
        qDebug("Sqlite bd open!");
    }
    else{

        qDebug() << "Sqlite not be open:" << p_sdb->lastError().text();
        return false;
    }



    if(p_sdb->isValid()){

       qDebug("Sqlite bd valid!");

    }else{

       qDebug() << p_sdb->lastError().text();
       return false;
    }

return true;
}

bool DBacsecc::getResultQuery(QString sql_query,QSqlQuery &sqlQuery)
{
    if (!sqlQuery.exec(sql_query)) {
        qDebug() << "Error sql query:" << sqlQuery.lastError().text();
        return false;
    }

   return true;
}
