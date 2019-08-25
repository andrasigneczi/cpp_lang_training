#include "Widget.h"

#include <iostream>

Widget::Widget()
{
}

void Widget::Draw(){
    std::cout << "Draw widget\n";
}

void Widget::Resize() {
    std::cout << "Resize widget\n";
}
