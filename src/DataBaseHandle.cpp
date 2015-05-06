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
    if(!mysql->IsConnected())
    {
        cerr<<"error: mysql connect failed"<<endl;
    }
}
bool DataBaseHandle::login(const char* userName, const char* password)
{
   char sql[200];
    sprintf(sql,"select Count(*) from player where userName=\"%s\" and password=\"%s\"",userName,password);
     if(mysql->SelectQuery(sql)<0)
    {
        cout<<mysql->GetErrMsg()<<endl;
        return false;
    }
    int ct;
    char **res=mysql->FetchRow();
    sscanf(res[0],"%d",&ct);
   // cout<<ct<<endl;
    if(ct==1)
        return true;
    return false;
}

bool DataBaseHandle::regist(const char* userName, const char* password)
{
    char sql[200];
    sprintf(sql,"select Count(*) from player where userName=\"%s\"",userName);
//    cout<<sql<<endl;

    if(mysql->SelectQuery(sql)<0)
    {
        cout<<mysql->GetErrMsg()<<endl;
        return false;
    }
    int ct;
    char **res=mysql->FetchRow();
    sscanf(res[0],"%d",&ct);
    if(ct>0)
    {
         cout<<"userName already exist"<<endl;
        return false;
    }
    sprintf(sql,"insert into player(userName,password) values(\"%s\",\"%s\");",userName,password);

  //   cout<<sql<<endl;
    if(mysql->ModifyQuery(sql)==0)
        return true;
    cout<<mysql->GetErrMsg()<<endl;
    return false;
}

PlayerInfo* DataBaseHandle::getPlayerInfo(const char* userName)
{
  //  PlayerInfo* res;
    return NULL;
}


DataBaseHandle::~DataBaseHandle()
{
    mysql->CloseConnect();
}
