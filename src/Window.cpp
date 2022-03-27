#include "../2048/Window.h"
Window::Window(int x, int y, const char *name, call c_) : 
            Fl_Window(x, y, name), c(c_) {}


int Window::handle(int e) {
    switch(e) {
    case FL_KEYBOARD:  
        if(Fl::event_key(FL_Up)) 
            c(direction::up);
        else if(Fl::event_key(FL_Down))
            c(direction::down);
        else if(Fl::event_key(FL_Right))
            c(direction::right);
        else if(Fl::event_key(FL_Left))
            c(direction::left);
        else
            return 0;
        return 1;
        break;
    }
    return 0;
}
            
   
