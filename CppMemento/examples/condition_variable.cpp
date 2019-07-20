#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <list>
#include <condition_variable>
#include <iostream>
#include <system_error>

using namespace std;


template<typename T>
class SyncQueue {
public:

    void put( T t ) {
        lock_guard<mutex> lck( mMutex );
        mQueue.push_back( move( t ));
        mCondV.notify_one();
    }

    T get(chrono::steady_clock::duration d) {
        unique_lock<mutex> lck( mMutex );
        bool not_empty = mCondV.wait_for( lck, d, [this]{ return !mQueue.empty();});
        if( not_empty ) {
            T retV = move( mQueue.front());
            mQueue.pop_front();
            return retV;
        } else {
            throw system_error( make_error_code(errc::timed_out), "timeout");
        }
    }

private:
    condition_variable mCondV;
    list<T> mQueue;
    mutex mMutex;
};

class Message {
public:
    Message( string name ) {
        mName = name;
    }
    //Message( Message&& ) = delete;
    //Message( Message&& ) = default;
//    Message( Message&& m ) {
//        mName = move( m.mName );
//        //this_thread::sleep_for( chrono::milliseconds( 100 ));
//    }

//    Message( const Message& m ) {
//        mName = m.mName;
//        this_thread::sleep_for( chrono::milliseconds( 1000 ));
//        cout << "Copy called\n";
//    }

    string getName() { return mName; }

private:
    string mName;
};

SyncQueue<Message> syncQueue;
void produce() {
    for( int i = 0; i < 10; i++ ) {
        Message m( string( "aaa" ) + to_string( i ));
        syncQueue.put( move( m ));
    }
}

void consume() {
    try {
        while( true ) {
            Message m = syncQueue.get( chrono::milliseconds(300));
            cout << m.getName() << endl;
        }
    }
    catch( system_error& e ) {
        cout << e.what() << endl;
    }
//    catch( ... ) {
//        cout << "what now?" << endl;
//    }
}

int main( int argc, char* argv[] ) {
    thread t1( produce );
    thread t2( consume );

    t1.join();
    t2.join();
    return 0;
}

