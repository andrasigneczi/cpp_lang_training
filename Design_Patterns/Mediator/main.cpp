#include "User.h"
#include "ChatRoom.h"
#include <memory>

int main( int argc, char* argv[] ){
    std::unique_ptr<ChatRoomIF> room( new ChatRoom( "room nr. 1"));
    std::unique_ptr<UserIF> jack( new User( room.get(), "Jack" ));
    std::unique_ptr<UserIF> joe( new User( room.get(), "Joe" ));

    jack->sendMessage( "Hi Joe!");
    joe->sendMessage( "Hi Jack!");


}
