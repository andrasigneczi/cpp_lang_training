#ifndef USER_H
#define USER_H

#include "UserIF.h"

class ChatRoomIF;
class User : public UserIF
{
public:
    User( ChatRoomIF* chatRoom, std::string name );

    void sendMessage( std::string msg );
    std::string getName();
private:

    ChatRoomIF* mChatRoom;
    std::string mName;

};

#endif // USER_H
