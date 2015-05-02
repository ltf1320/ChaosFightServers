#ifndef MSG_T_H
#define MSG_T_H

enum msg_type
{
    MSG_TYPE_VERSION_CHECK=1,
    MSG_TYPE_VERSION_CHECK_RES,
    MSG_TYPE_LOGIN,
    MSG_TYPE_LOGIN_RES
    MSG_TYPE_REGISTER,
    MSG_TYPE_REGISTER_RES
    MSG_TYPE_MATCH,
    MSG_TYPE_MATCH_RES
    MSG_TYPE_QUIT_MATCH,
    MSG_TYPE_QUIT_MATHC_RES,
    MSG_TYPE_SYNC_INFO,
    MSG_TYPE_CHAT,
    MSG_TYPE_CHAT_RES
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
