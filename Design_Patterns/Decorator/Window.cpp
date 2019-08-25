#include "Window.h"

Window::Window()
{
}

void Window::setContent( VisualComponent* content ){
    mVSComp = content;
}

void Window::Draw(){
    mVSComp->Draw();
}

void Window::Resize() {
    mVSComp->Resize();
}
