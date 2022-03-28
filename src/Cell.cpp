#include "../2048/Cell.h"


Cell::Cell(Pair pos_, Pair size_) : value(0), 
        box(new Fl_Box(pos_.first, pos_.second, size_.first, size_.second, "0"))
{
    box->labelsize(24);
    box->box(FL_RFLAT_BOX);
    box->color(FL_BLUE);
    box->labelfont(FL_BOLD);
    init_value();
}

void Cell::val(int value_)
{
    value = value_;
    init_value();
}

void Cell::init_value()
{
    sprintf(strval, "%d", value);
    box->label(strval);
    switch(value) {
    case 0:
        box->color(fl_rgb_color(40, 200, 220));
        break;
    case 2:
        box->color(fl_rgb_color(50, 213, 103));
        break;
    case 4:
        box->color(fl_rgb_color(27, 225, 34));
        break;
    case 8:
        box->color(fl_rgb_color(23, 90, 222));
        break;
    case 16:
        box->color(fl_rgb_color(140, 85, 220));
        break;
    case 32:
        box->color(fl_rgb_color(255, 255, 0));
        break;
    case 64:
        box->color(fl_rgb_color(255, 153, 50));
        break;
    case 128:
        box->color(fl_rgb_color(255, 128, 0));
        break;
    case 256:
        box->color(fl_rgb_color(200, 100, 0));
        break;
    case 512:
        box->color(fl_rgb_color(255, 0, 0));
        break;
    case 1024:
        box->color(fl_rgb_color(153, 0, 0));
        break;
    case 2048:
        box->labelcolor(FL_WHITE);
        box->color(fl_rgb_color(0, 0, 0));
        break;
    }
}

void Cell::move_to(Cell &c)
{   
    std::swap(value, c.value);
    init_value();
    c.init_value();
}

void Cell::combine_with(Cell &c)
{
    value += c.value;
    c.value = 0;
    init_value();
    c.init_value();
}

Cell::~Cell() {}
