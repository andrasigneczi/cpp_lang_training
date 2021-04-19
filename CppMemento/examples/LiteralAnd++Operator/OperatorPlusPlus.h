#ifndef OPERATORPLUSPLUS_H
#define OPERATORPLUSPLUS_H

#include <sstream>

//#define INNER_OPERATOR

class OperatorPlusPlus
{
#ifndef INNER_OPERATOR
    friend OperatorPlusPlus& operator++(OperatorPlusPlus& op );
    friend OperatorPlusPlus operator++(OperatorPlusPlus& op, int );
#endif

public:

    OperatorPlusPlus();
#ifdef INNER_OPERATOR
    OperatorPlusPlus& operator++();
    OperatorPlusPlus operator++( int );
#endif

    int getCounter(){ return mCounter; }

private:
    int mCounter;
};

#ifndef INNER_OPERATOR
OperatorPlusPlus& operator++(OperatorPlusPlus& op );
OperatorPlusPlus operator++(OperatorPlusPlus& op, int );
#endif

std::ostream& operator<<( std::ostream& out, OperatorPlusPlus op );


#endif // OPERATORPLUSPLUS_H
