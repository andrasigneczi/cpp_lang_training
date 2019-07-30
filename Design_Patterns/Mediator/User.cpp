#include "User.h"
#include "ChatRoomIF.h"

User::User( ChatRoomIF* chatRoom, std::string name )
: mChatRoom( chatRoom )
, mName( name )
{
}

void User::sendMessage( std::string msg ) {
    mChatRoom->sendMessage( this, msg );
}

std::string User::getName(){
    return mName;
}
