#include <future>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

int ff( int i ) {
    this_thread::sleep_for( chrono::milliseconds( i * 100 ));
    if( i ) return i;
    throw runtime_error( "ff(0)" );
}

int main( int argc, char* argv[] ) {
    auto c1 = std::chrono::high_resolution_clock::now();

    packaged_task<int(int)> pt1( ff );
    packaged_task<int(int)> pt2( ff );


    auto v1 = pt1.get_future();
    cout << "dbg1\n";
    cout.flush();
    auto v2 = pt2.get_future();
    cout << "dbg2\n";
    cout.flush();

    thread t1(move(pt1), 40 );
    thread t2(move(pt2), 50 );

    // print the status while we are waiting
    bool s1 = false, s2 = false;
    do {
        s1 = v1.wait_for(chrono::milliseconds(50)) == future_status::ready;
        s2 = v2.wait_for(chrono::milliseconds(50)) == future_status::ready;
        cout<< "Value 1 is " << (s1 ? "" : "not ") << "ready" << endl;
        cout<< "Value 2 is " << (s2 ? "" : "not ") << "ready" << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    } while (!s1 || !s2);

    try {
        cout << v1.get() << endl;
        cout << "dbg3\n";
	cout.flush();
        cout << v2.get() << endl;
        cout << "dbg4\n";
	cout.flush();

    } catch( exception& e ) {
        cout << e.what() << endl;
    }
    auto c2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(c2 - c1).count() << " microseconds\n";

    t1.join();
    t2.join();
    return 0;
}
