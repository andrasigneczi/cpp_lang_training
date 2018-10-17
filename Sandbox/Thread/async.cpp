#include <future>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

int ff( int i ) {
    //this_thread::sleep_for( chrono::milliseconds( i * 100 ));
    if( i ) return i;
    throw runtime_error( "exception: ff(0)" );
}

void printStatus( future_status s ) {
    switch( s ) {
    case future_status::ready:    cout << "ready\n";    break;
    case future_status::deferred: cout << "deferred\n"; break;
    case future_status::timeout:  cout << "timeout\n";  break;
    }
}

void printValue( future<int>& f ) {
    try {
        cout << "value: " << f.get() << endl;

    } catch( runtime_error& e ) {
        cerr << e.what() << endl;
    }
}

int main( int argc, char* argv[] ) {

    future<int> v0 = async( launch::async, ff, 0 );
    future<int> v1 = async( launch::async, ff, 1 );

    future_status s0 = v0.wait_for( chrono::milliseconds(10));
    future_status s1 = v1.wait_for( chrono::milliseconds(10));

    printStatus( s0 );
    printStatus( s1 );
    printValue( v0 );
    printValue( v1 );

    return 0;
}

