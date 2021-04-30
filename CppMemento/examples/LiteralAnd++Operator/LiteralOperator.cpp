#include "LiteralOperator.h"
#include <iostream>

LiteralOperator::LiteralOperator( long double x )
{
    mX = x;
}

LiteralOperator operator"" _MM(long double x) {
    return LiteralOperator( x );
}

LiteralOperator operator"" _MM(const char* x, size_t n ){
    std::stringstream buff;
    for( const char* pc = x; *pc != 0; pc++ ){
        if(( *pc >= '0' && *pc <= '9' ) || *pc == '.' )
            buff << *pc;
    }
    return LiteralOperator( std::atof( buff.str().c_str()));
}

/*
LiteralOperator operator"" MM(long double x) {
    return LiteralOperator( x );
}

LiteralOperator operator"" MM(const char* x, size_t n ){
    std::stringstream buff;
    for( const char* pc = x; *pc != 0; pc++ ){
        if(( *pc >= '0' && *pc <= '9' ) || *pc == '.' )
            buff << *pc;
    }
    return LiteralOperator( std::atof( buff.str().c_str()));
}
*/

std::ostream& operator<<( std::ostream& out, LiteralOperator& o ){
    out << o.getValue();
    return out;
}

int main( int argc, char* argv[] ){

    LiteralOperator o = 100.11_MM;
    std::cout << o << std::endl;
    o = "dssdc2sdc2sdc2.34576"_MM;
    std::cout << o << std::endl;

    std::cout << 102_b8 << std::endl;
    return 0;
}
