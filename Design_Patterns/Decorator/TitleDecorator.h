#ifndef TITLEDECORATOR_H
#define TITLEDECORATOR_H

#include "Decorator.h"

class TitleDecorator : public Decorator
{
public:
    TitleDecorator( VisualComponent* comp );
    void Draw() override;
    void Resize() override;
};

#endif // TITLEDECORATOR_H
