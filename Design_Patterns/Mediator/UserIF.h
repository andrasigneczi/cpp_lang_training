#ifndef USERIF_H
#define USERIF_H

#include <string>

class UserIF {
public:
    virtual void sendMessage( std::string msg ) = 0;
    virtual std::string getName() = 0;
};

#endif // USERIF_H
