#include "msg_t.h"
Msg_t::Msg_t()
{
    data=0;
    head.length=0;
}

Msg_t::Msg_t(Msg_head head)
{
    this->head=head;
    data=0;
    head.length=0;
}

Msg_t::~Msg_t()
{
    if(data!=0)
    {
        delete data;
        data=0;
    }
}
