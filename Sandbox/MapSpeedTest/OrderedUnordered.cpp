#include "OrderedUnordered.h"
#include <chrono>
#include <iostream>
#include <locale.h>
#include <rw/locale.h>

#define ITEMCOUNT 1000000
#ifdef STDSTRING
inline String ToString( int i ) {
    return std::to_string( i );
}
#else
inline String ToString( int i ) {
    return  RWLocale::global().asString((long)i );
}
#endif

inline size_t hash( const String& s ) {
    return std::hash<String>{}( s );
}

OrderedUnordered::OrderedUnordered()
{
}


void OrderedUnordered::RunTests() {

	std::unordered_map<int, int> unOrdered;
	unOrdered.emplace( 10, 12 );
	unOrdered.emplace( 10, 11 );
	std::cout << "second: " << unOrdered.find( 10 )->second << std::endl;
	
    using namespace std::chrono;
    auto t0 = high_resolution_clock::now();

    //this_thread::sleep_for(milliseconds{20});
    fillTest();
    reachTest();

    auto t1 = high_resolution_clock::now();
    std::cout << std::endl << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed\n";
}

void OrderedUnordered::fillTest() {

    using namespace std::chrono;
    auto t0 = high_resolution_clock::now();

    //this_thread::sleep_for(milliseconds{20});
    for( int i = 0; i < ITEMCOUNT; i++ )
        mOrdered.emplace( ToString( i ), i );


    auto t1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed (Fill ordered map)\n";

    t0 = high_resolution_clock::now();

    //this_thread::sleep_for(milliseconds{20});
    for( int i = 0; i < ITEMCOUNT; i++ )
        mOrderedHash.emplace( hash( ToString( i )), i );


    t1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed (Fill ordered map + hash)\n";


    t0 = high_resolution_clock::now();

    //this_thread::sleep_for(milliseconds{20});
    for( int i = 0; i < ITEMCOUNT; i++ )
        mUnOrdered.emplace( ToString( i ), i );


    t1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed (Fill unordered map)\n";

    t0 = high_resolution_clock::now();

    //this_thread::sleep_for(milliseconds{20});
    for( int i = 0; i < ITEMCOUNT; i++ )
        mUnOrderedHash.emplace( hash( ToString( i )), i );


    t1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed (Fill unordered map + hash)\n";

}

void OrderedUnordered::reachTest() {

    using namespace std::chrono;
    auto t0 = high_resolution_clock::now();

    for( int i = 0; i < ITEMCOUNT; i++ ) {
        if( mOrdered.find( ToString( i )) == mOrdered.end())
            std::cerr << "error" << std::endl;
    }


    auto t1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed (Reach item in ordered map)\n";

    t0 = high_resolution_clock::now();

    for( int i = 0; i < ITEMCOUNT; i++ ) {
        if( mOrderedHash.find( hash( ToString( i ))) == mOrderedHash.end())
            std::cerr << "error" << std::endl;
    }


    t1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed (Reach item in ordered map + hash)\n";

    t0 = high_resolution_clock::now();

    for( int i = 0; i < ITEMCOUNT; i++ ) {
        if( mUnOrdered.find( ToString( i )) == mUnOrdered.end())
            std::cerr << "error" << std::endl;
    }


    t1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed (Reach item in unordered map)\n";


    t0 = high_resolution_clock::now();

    for( int i = 0; i < ITEMCOUNT; i++ ) {
        if( mUnOrderedHash.find( hash( ToString( i ))) == mUnOrderedHash.end())
            std::cerr << "error" << std::endl;
    }


    t1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed (Reach item in unordered map + hash)\n";
}
