#include <future>
#include <thread>
#include <iostream>

using namespace std;

int ff( int i ) {
    //this_thread::sleep_for( chrono::milliseconds( i * 100 ));
    if( i ) return i;
    throw runtime_error( "ff(0)" );
}

int main( int argc, char* argv[] ) {
    packaged_task<int(int)> pt1( ff );
    packaged_task<int(int)> pt2( ff );

    pt1( 10 );
    pt2( 50 );

    auto v1 = pt1.get_future();
    cout << "dbg1\n";
    auto v2 = pt2.get_future();
    cout << "dbg2\n";

    try {
        cout << v1.get() << endl;
        cout << "dbg3\n";
        cout << v2.get() << endl;
        cout << "dbg4\n";

    } catch( exception& e ) {
        cout << e.what() << endl;
    }

    return 0;
}
