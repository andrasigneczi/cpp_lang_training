#ifndef CHATROOM_H
#define CHATROOM_H

#include "ChatRoomIF.h"

class UserIF;
class ChatRoom : public ChatRoomIF
{
public:
    ChatRoom( std::string name );

    void sendMessage( UserIF* user, std::string msg ) override;
private:
    std::string mName;
};

#endif // CHATROOM_H
