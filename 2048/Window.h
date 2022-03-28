#ifndef WINDOW_H
#define WINDOW_H
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include "Field.h"
#include "enumeration.h"

class Window : public Fl_Window {
    Field* f;
public:
    Window(const char *name) : Fl_Window(0, 0, name) {}
    void field(Field *f_) { f = f_;}

    virtual int handle(int e);
};
#endif //WINDOW_H
