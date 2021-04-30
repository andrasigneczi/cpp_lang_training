#include "OperatorPlusPlus.h"
#include <iostream>

OperatorPlusPlus::OperatorPlusPlus()
{
    mCounter = 0;
}

#ifdef INNER_OPERATOR
OperatorPlusPlus& OperatorPlusPlus::operator++() {
    mCounter++;
    return *this;
}

OperatorPlusPlus OperatorPlusPlus::operator++( int ){
    OperatorPlusPlus ret = *this;
    operator++();
    return ret;
}
#else

OperatorPlusPlus& operator++(OperatorPlusPlus& op ) {
    op.mCounter++;
    return op;
}

OperatorPlusPlus operator++(OperatorPlusPlus& op, int ){
    OperatorPlusPlus ret = op;
    op.mCounter++;
    return ret;
}
#endif

std::ostream& operator<<( std::ostream& out, OperatorPlusPlus op ){
    out << op.getCounter();
    return out;
}

int main( int argc, char* argv[] ){
    OperatorPlusPlus oo;
    std::cout << oo << std::endl;
    std::cout << ++oo << std::endl;
    std::cout << oo++ << std::endl;
    std::cout << oo << std::endl;
}
