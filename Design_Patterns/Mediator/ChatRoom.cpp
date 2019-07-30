#include "ChatRoom.h"
#include "UserIF.h"
#include <iostream>

ChatRoom::ChatRoom( std::string name )
: mName( name )
{
}

void ChatRoom::sendMessage( UserIF* user, std::string msg ){
    std::cout << "[" << mName << "]" << "[" << user->getName() << "]: "  << msg << std::endl;
}
