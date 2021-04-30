#ifndef SORTEDUNSORTED_H
#define SORTEDUNSORTED_H

#include <functional>
#include <unordered_map>
#include <map>

#define STDSTRING

#ifdef STDSTRING

#include <string>
typedef std::string String;

#else

#include <rw/cstring.h>
typedef RWCString String;

namespace std {
    template<>
    struct hash<String>
    {
       size_t operator () (const String& x) const
       {
          //using type = typename std::underlying_type<argument_type>::type;
          return x.hash();
       }
    };
}

#endif

//#include <rw/defs.h>

class OrderedUnordered
{
public:
    OrderedUnordered();
    void RunTests();

private:
    void fillTest();
    void reachTest();

    std::map<String,int> mOrdered;
    std::map<size_t,int> mOrderedHash;
    std::unordered_map<String, int> mUnOrdered;
    std::unordered_map<size_t, int> mUnOrderedHash;
};

#endif // SORTEDUNSORTED_H
