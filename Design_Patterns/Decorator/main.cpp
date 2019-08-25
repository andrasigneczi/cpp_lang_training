#include "Window.h"
#include "BackgroundDecorator.h"
#include "TitleDecorator.h"
#include "Widget.h"

int main( int argc, char* argv[] ) {
    Window w;
    w.setContent( new BackgroundDecorator( new TitleDecorator( new Widget())));
    w.Draw();
}
