#ifndef SOCKBUFFER_H
#define SOCKBUFFER_H

#include <msg_t.h>
#include <pthread.h>
#include "common.h"
/**
 * @brief The SockBuffer class
 * sock缓存类
 */
class SockBuffer
{
    public:
        SockBuffer(void (*onMessageRecv)(Msg_t *msg, int id),int id);
        virtual ~SockBuffer();
        char buf[BUFFER_SIZE];
        //接收消息，如果解析成功，则调用onMessageRecv
        void recvMsg(char *data,int len);
        //回调函数，在server里指向ServerHundle::hundleMessage
        void (*onMessageRecv)(Msg_t*,int id);
        int lockBuffer();
        void unlockBuffer();

        int lockSend();
        void unlockSend();

        int id;
    protected:
        pthread_mutex_t bufMutex;
        pthread_mutex_t sendMutex;
        int nowi;
        SockBuffer(const SockBuffer& other);
        SockBuffer& operator=(const SockBuffer& other);
    private:
};

#endif // SOCKBUFFER_H
