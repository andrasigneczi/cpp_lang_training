#ifndef WIDGET_H
#define WIDGET_H

#include "VisualComponent.h"

class Widget : public VisualComponent
{
public:
    Widget();
    void Draw() override;
    void Resize() override;
};

#endif // WIDGET_H
