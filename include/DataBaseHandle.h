#ifndef DATABASEHANDLE_H
#define DATABASEHANDLE_H

#include "encapsulation_mysql.h"
#include "PlayerInfo.h"

class DataBaseHandle
{
    public:
        static DataBaseHandle* getInstance();
        bool login(const char *userName,const char *password);
        bool regist(const char *userName,const char *password);
        PlayerInfo* getPlayerInfo(const char *userName);
    protected:
        DataBaseHandle();
         virtual ~DataBaseHandle();
         static DataBaseHandle* instance;
         CEncapMysql *mysql;
    private:

};


#endif // DATABASEHANDLE_H
