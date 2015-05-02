/*****************************
@author ltf1320
@modifier

*****************************/
#include "Client.h"
#include "DataBaseHandle.h"
#include "MainServer.h"
#include <sys/socket.h>
#include <cstring>
Client::Client(int sock)
{
    buffer=new SockBuffer(MainServer::onMessageRecv,sock);
    logined=false;
}

bool Client::isLogined()
{
    return logined;
}

std::string Client::getUserName()
{
    return userName;
}

bool Client::login(const char* userName, const char* password)
{
    if(DataBaseHandle::getInstance()->login(userName,password))
    {
        logined=true;
        this->userName.assign(userName);
    }
    else
    {
        logined=false;
    }
    return logined;
}

Client::~Client()
{

}

void Client::recvMsg()
{
    char buf[1024];
    while(true)
    {
        int len=recv(sock,buf,1024,0);
        if(len<0)
        {
            if(len < 0)
            {
                if(errno == EAGAIN)
                {
                    // 由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读
                    return;
                }
                else if (errno == ECONNRESET)
                {
                    // 对方发送了RST
                    std::cout<<"RST"<<std::endl;
                    //        client->buffer.unlockBuffer();
                    MainServer::getInstance()->removeClient(sock);
                    break;
                }
                else if (errno == EINTR)
                {
                    // 被信号中断
                    continue;
                }
                else
                {
                    //其他不可弥补的错误
                    //      client->buffer.unlockBuffer();
                    MainServer::getInstance()->removeClient(sock);
                    std::cerr<< "unrecovable error"<<std::endl;
                    break;
                }
            }
        }
        else if(len==0)
        {
            // 这里表示对端的socket已正常关闭.发送过FIN了。
            //        client->buffer.unlockBuffer();
            MainServer::getInstance()->removeClient(sock);
            break;
        }
        else{
            buffer->recvMsg(buf,len);
        }
    }
}
int Client::getSock()
{
    return sock;
}
