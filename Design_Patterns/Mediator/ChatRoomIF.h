#ifndef CHATROOMIF_H
#define CHATROOMIF_H

#include <string>

class UserIF;
class ChatRoomIF
{
public:
    virtual void sendMessage( UserIF* user, std::string msg ) = 0;
};

#endif // CHATROOMIF_H
