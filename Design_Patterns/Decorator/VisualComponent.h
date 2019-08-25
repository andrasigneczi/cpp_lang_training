#ifndef VISUALCOMPONENT_H
#define VISUALCOMPONENT_H

class VisualComponent {
public:
    virtual void Draw() = 0;
    virtual void Resize() = 0;
};

#endif // VISUALCOMPONENT_H
