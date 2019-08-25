#include "BackgroundDecorator.h"

#include <iostream>

BackgroundDecorator::BackgroundDecorator( VisualComponent* comp )
    : Decorator( comp )
{
}

void BackgroundDecorator::Draw(){
    Decorator::Draw();
    std::cout << "Draw background\n";
}

void BackgroundDecorator::Resize() {
    Decorator::Resize();
    std::cout << "Resize background\n";
}
