#include <thread>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <mutex>
#include <string>

std::mutex mut;

class Room {
public:

    Room(int v, std::string name) : v_(v), name_(name) {
    }
    
    void inc() {++v_;}

    void printV() {
	mut.lock();
	std::cout << name_ << ": " << v_ << std::endl;
	mut.unlock();
    }

private:
    int v_;
    std::string name_;
};

using RoomUPtr = std::unique_ptr<Room>;
namespace Global {
    thread_local RoomUPtr room_;

    RoomUPtr& room() {
	return room_;
    }
}

void execRoom(int v, std::string name) {
    Global::room() = std::make_unique<Room>(v, name);
    for(int i = v; i < v + 1e5; ++i) {
	Global::room()->inc();
	Global::room()->printV();
	usleep(1e1);
    }
}

int main(int argc, char* argv[]) {
    std::thread a(execRoom, 20, "a room"), b(execRoom, 55555, "b room");
    a.join();
    b.join();
    return EXIT_SUCCESS;
}
