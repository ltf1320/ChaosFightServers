/*****************************
@author ltf1320
@modifier

*****************************/
#include "MainServer.h"
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>

MainServer* MainServer::instance=new MainServer();
ThreadPool* MainServer::threadPool=NULL;
MainServer::MainServer()
{
    threadPool=new ThreadPool(10);
}

MainServer::~MainServer()
{
    threadPool->terminate();
}
void MainServer::startServer()
{

}

Client* MainServer::getClient(std::string userName)
{
    std::lock_guard<std::mutex> lck(mtx);
    return clientsByUserName[userName];
}


Client* MainServer::getClient(int sock)
{
    std::lock_guard<std::mutex> lck(mtx);
    return clientsBySock[sock];
}

MainServer* MainServer::getInstance()
{
    return instance;
}

void MainServer::setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }
}

void MainServer::listenThread()
{
 //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件

    struct epoll_event ev,events[20];
    //生成用于处理accept的epoll专用的文件描述符

    int epfd=epoll_create(25600);
    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    //把socket设置为非阻塞方式
   setnonblocking(listenfd);
    //设置与要处理的事件相关的文件描述符
    ev.data.fd=listenfd;
    //设置要处理的事件类型
    ev.events=EPOLLIN|EPOLLET;
    //ev.events=EPOLLIN;
    //注册epoll事件

    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    serveraddr.sin_port=htons(MainServer::getInstance()->port);
    bind(listenfd,(sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(listenfd, 500000);
    for ( ; ; ) {
        //等待epoll事件的发生

        int nfds=epoll_wait(epfd,events,20,500);
        //处理所发生的所有事件

        for(int i=0;i<nfds;++i)
        {
            if(events[i].data.fd==listenfd)//如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
            {
                int connfd = accept(listenfd,(sockaddr *)&clientaddr, NULL);
                if(connfd<0){
                    perror("connfd<0");
                    exit(1);
                }
                //setnonblocking(connfd);

                char *str = inet_ntoa(clientaddr.sin_addr);
               std::cout << "accapt a connection from " << str <<  std::endl;
                //设置用于读操作的文件描述符

                ev.data.fd=connfd;
                //设置用于注测的读操作事件

                ev.events=EPOLLIN|EPOLLET;
                //ev.events=EPOLLIN;

                //注册ev
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);

                threadPool->addTast([connfd](){
                    Client* client=new Client(connfd);
                    MainServer::getInstance()->addClient(client);
                });
            }
            else if(events[i].events&EPOLLIN)//如果是已经连接的用户，并且收到数据，那么进行读入。
            {
                int fd=events[i].data.fd;
                threadPool->addTast([fd](){
                    MainServer::getInstance()->getClient(fd)->recvMsg();
                });
            }
        }
    }
}

void MainServer::addClient(Client* client)
{
    std::lock_guard<std::mutex> lck(mtx);
    clientsBySock[client->getSock()]=client;
}

void MainServer::removeClient(int sock)
{
    std::lock_guard<std::mutex> lck(mtx);
    Client * client= clientsBySock[sock];
    if(client==NULL)
        return;
    if(client->isLogined())
        clientsByUserName.erase(client->getUserName());
    clientsBySock.erase(sock);
    delete client;
}

void MainServer::onMessageRecv(Msg_t* msg, int sock)
{

}
