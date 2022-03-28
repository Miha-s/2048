#include "Field.h"
#include "Window.h"

void test(direction) 
{
    std::cout << "HEllo" << std::endl;
}

int main()
{
    Pair size(4, 4);
    Pair but_size(70, 70);
    Window *win = new Window("2048");
    Field field(size, but_size, 10, win);
    win->field(&field);
    
    win->show();

    return Fl::run();
}
