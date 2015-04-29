/*****************************
@author ltf1320
@modifier

*****************************/
#include <iostream>
#include <mainServer/MainServerConsole.h>
#include <encapsulation_mysql.h>
using namespace std;

int main()
{
    cout<<"ChaosFight Main Server"<<endl;
    MainServerConsole console;
    CEncapMysql *mysql=new CEncapMysql();
    mysql->Connect("127.0.0.1","root","123456");
    string cmd;
    while(true)
    {
        cin>>cmd;
        console.excute(cmd);
    }
    return 0;
}
