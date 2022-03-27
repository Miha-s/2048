#include "Field.h"
#include "Window.h"

void test(direction) 
{
    std::cout << "HEllo" << std::endl;
}

int main()
{
    Pair size(5, 5);
    Pair but_size(200, 50);
    Field field(size, but_size, 20);
    Window *win = new Window(400, 400, "win", test);
//    std::shared_ptr<Fl_Window> win = field.window();
    
    win->show();
//    win->show();
    return Fl::run();
}
