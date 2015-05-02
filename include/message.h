#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

struct LoginMessage{
    char userName[10];
    char password[16];
}

struct LoginResMessage{
    bool result;
}

struct RegisterMessage{
    char userName[10];
    char password[16];
}

struct RegisterResMessage{
    bool result;
}

struct MatchMessage{


}

#endif // MESSAGE_H_INCLUDED
