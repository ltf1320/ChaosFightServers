#ifndef MSG_T_H
#define MSG_T_H

enum msg_type
{
    MSG_TYPE_TEXT=1,
    MSG_TYPE_INIT,
    MSG_TYPE_JOIN,
    MSG_TYPE_LEAVE,
    MSG_TYPE_SYNC
};

class Msg_head
{
public:
    int length;
    int frame;
    msg_type type;
};

class Msg_t
{
    public:
        Msg_t();
        Msg_t(Msg_head head);
        Msg_head head;
        char* data;
        virtual ~Msg_t();
    protected:
    private:
};

#endif // MSG_T_H
