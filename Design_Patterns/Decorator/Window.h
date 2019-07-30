#ifndef WINDOW_H
#define WINDOW_H

#include "VisualComponent.h"

class Window : public VisualComponent
{
public:
    Window();
    void setContent( VisualComponent* content );
    void Draw() override;
    void Resize() override;

private:
    VisualComponent* mVSComp;
};

#endif // WINDOW_H
