/*****************************
@author ltf1320
@modifier

*****************************/
#include "DataBaseHandle.h"
#include <string>

DataBaseHandle* DataBaseHandle::instance=new DataBaseHandle();

DataBaseHandle* DataBaseHandle::getInstance()
{
    return instance;
}

DataBaseHandle::DataBaseHandle()
{
    mysql=new CEncapMysql();

    mysql->Connect("127.0.0.1","root","123456","ChaosFight");//之后修改为配置

}
bool DataBaseHandle::login(const char* userName, const char* password)
{
    string sql;
    sql+="select Count(*) from player where userName=";
    sql+=userName;
    sql+=" password=";
    sql+=password;
    if(mysql->ModifyQuery(sql.c_str())>0)
        return true;
}

DataBaseHandle::~DataBaseHandle()
{
    mysql->CloseConnect();
}
