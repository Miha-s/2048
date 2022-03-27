#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include "enumeration.h"


class Window : public Fl_Window {
    typedef void (*call)(direction);
    call c;
public:
    Window(int x, int y, const char *name, call c_);

    virtual int handle(int e);
};
