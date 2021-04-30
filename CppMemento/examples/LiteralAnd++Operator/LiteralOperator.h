#ifndef LITERALOPERATOR_H
#define LITERALOPERATOR_H

#include <sstream>

class LiteralOperator
{
public:
    LiteralOperator( long double x );
    long double getValue() { return mX; }

private:
    long double mX;
};

LiteralOperator operator"" _MM(long double x);
LiteralOperator operator"" _MM(const char* x, size_t n );

//LiteralOperator operator"" MM(long double x);
//LiteralOperator operator"" MM(const char* x , size_t n);

std::ostream& operator<<( std::ostream& out, LiteralOperator& o );





constexpr int ipow(int x, int n) // x to the nth power for n>=0
{
    return (n>0) ? x*ipow(x, n-1) : 1;
}

template<char c> // handle the single ternar y digit case
constexpr int b8_helper()
{
    static_assert(c<'8',"not a ternar y digit");
    return c - '0';
}

template<char c, char d, char... tail> // peel off one ternar y digit
constexpr int b8_helper()
{
    static_assert(c<'8',"not a ternar y digit");
    return ipow(8, 1 + sizeof...(tail))*(c-'0')+b8_helper<d, tail...>();
}

template<char... chars>
constexpr int operator"" _b8() // base 8
{
    return b8_helper<chars...>();
}

#endif // LITERALOPERATOR_H
