#include "sockBuffer.h"
#include <cstring>
#include <iostream>

SockBuffer::SockBuffer(void(*onMessageRecv)(Msg_t*,int id), int id)
{
    this->onMessageRecv=onMessageRecv;
    nowi=0;
    this->id=id;
    pthread_mutex_init(&bufMutex,NULL);
    pthread_mutex_init(&sendMutex,NULL);
}

SockBuffer::~SockBuffer()
{
    //dtor
}

SockBuffer::SockBuffer(const SockBuffer& other)
{
    *this=other;
    //copy ctor
}


int
SockBuffer::lockBuffer()
{
    timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    time.tv_nsec+=1000;
  //  return pthread_mutex_lock(&bufMutex);
    return pthread_mutex_timedlock(&bufMutex,&time);
}

int
SockBuffer::lockSend()
{
    timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    time.tv_nsec+=1000;
  //  return pthread_mutex_lock(&bufMutex);
    return pthread_mutex_timedlock(&sendMutex,&time);
}


void
SockBuffer::unlockBuffer()
{
    pthread_mutex_unlock(&bufMutex);
}

void
SockBuffer::unlockSend()
{
    pthread_mutex_unlock(&sendMutex);
}

const int MSG_HEAD_SIZE=sizeof(Msg_head);
void
SockBuffer::recvMsg(char* data,int len)
{

    memcpy(buf+nowi,data,len);
    nowi+=len;
    while(nowi>=MSG_HEAD_SIZE)
    {
        Msg_head msg_head;
        memcpy(&msg_head,buf,MSG_HEAD_SIZE);
        if(nowi>=msg_head.length+MSG_HEAD_SIZE)
        {
            Msg_t* msg=new Msg_t(msg_head);
            msg->data=new char[msg_head.length+1];
            memcpy(msg->data,buf+MSG_HEAD_SIZE,msg_head.length);
            msg->data[msg_head.length]=0;
            onMessageRecv(msg,id);
         //   std::cout<<"start delete msg"<<std::endl;
            delete msg;
         //   std::cout<<"end delete msg"<<std::endl;
            for(int j=0;j<nowi-msg_head.length-MSG_HEAD_SIZE;j++)
                buf[j]=buf[j+msg_head.length+MSG_HEAD_SIZE];
            nowi-=msg_head.length;
            nowi-=MSG_HEAD_SIZE;
        }
        else break;
    }
}

SockBuffer& SockBuffer::operator=(const SockBuffer& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
