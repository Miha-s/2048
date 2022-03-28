#include "Field.h"
#include "Window.h"

void test(direction) 
{
    std::cout << "HEllo" << std::endl;
}

int main()
{
    Pair size(5, 5);
    Pair but_size(70, 30);
    Window *win = new Window("2048");
    Field field(size, but_size, 20, win);
    win->field(&field);
    
    win->show();

    return Fl::run();
}
