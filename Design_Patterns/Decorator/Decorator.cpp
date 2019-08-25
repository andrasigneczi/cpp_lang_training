#include "Decorator.h"

Decorator::Decorator( VisualComponent* comp )
    : mVSComp( comp )
{
}

void Decorator::Draw() {
    mVSComp->Draw();
}

void Decorator::Resize() {
    mVSComp->Resize();
}
