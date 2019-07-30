#ifndef BACKGROUNDDECORATOR_H
#define BACKGROUNDDECORATOR_H

#include "Decorator.h"

class BackgroundDecorator : public Decorator
{
public:
    BackgroundDecorator( VisualComponent* comp );
    void Draw() override;
    void Resize() override;
};

#endif // BACKGROUNDDECORATOR_H
