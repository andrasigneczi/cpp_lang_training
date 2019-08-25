#ifndef DECORATOR_H
#define DECORATOR_H

#include "VisualComponent.h"

class Decorator : public VisualComponent
{
public:
    Decorator( VisualComponent* comp );
    void Draw() override;
    void Resize() override;

private:
    VisualComponent* mVSComp;
};

#endif // DECORATOR_H
