#include "TitleDecorator.h"

#include <iostream>

TitleDecorator::TitleDecorator( VisualComponent* comp )
    : Decorator( comp )
{
}

void TitleDecorator::Draw(){
    Decorator::Draw();
    std::cout << "Draw title\n";
}

void TitleDecorator::Resize(){
    Decorator::Resize();
    std::cout << "Resize title\n";
}
