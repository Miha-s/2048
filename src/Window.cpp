#include "../2048/Window.h"

int Window::handle(int e) {
    switch(e) {
    case FL_KEYBOARD:  
        if(Fl::event_key(FL_Up)) 
            f->step(direction::up);
        else if(Fl::event_key(FL_Down))
            f->step(direction::down);
        else if(Fl::event_key(FL_Right))
            f->step(direction::right);
        else if(Fl::event_key(FL_Left))
            f->step(direction::left);
        else
            return 0;
        return 1;
        break;
    }
    return Fl_Window::handle(e);
}
            
   
