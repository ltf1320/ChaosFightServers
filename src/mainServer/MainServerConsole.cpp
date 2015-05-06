/*****************************
@author ltf1320
@modifier

*****************************/
#include "mainServer/MainServerConsole.h"
#include <iostream>
MainServerConsole::MainServerConsole()
{
    //ctor
}

MainServerConsole::~MainServerConsole()
{
    //dtor
}
bool
MainServerConsole::priExcute(string cmd)
{
    if(!cmd.compare("start"))
    {
        cout<<"main server started"<<endl;
    }
    else if(!cmd.compare("login"))
    {
        string userName,password;
        cin>>userName>>password;
        if(MainServer::getInstance()->login(userName.c_str(),password.c_str()))
            cout<<"login success"<<endl;
        else cout<<"login failed"<<endl;
    }
    else if(!cmd.compare("register"))
    {
                string userName,password;
        cin>>userName>>password;
        if(MainServer::getInstance()->regist(userName.c_str(),password.c_str()))
            cout<<"register success"<<endl;
        else cout<<"register failed"<<endl;
    }
    else return false;
    return true;
}
