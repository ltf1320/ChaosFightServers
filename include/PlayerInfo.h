#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "common.h"
class PlayerInfo
{
    public:
        PlayerInfo();
        char userName[MAX_USER_NAME_LEN];
        virtual ~PlayerInfo();
    protected:
    private:
};

#endif // PLAYERINFO_H
