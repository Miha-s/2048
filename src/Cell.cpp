#include "../2048/Cell.h"


Cell::Cell(Pair pos_, Pair size_) : value(0), 
        box(new Fl_Box(pos_.first, pos_.second, size_.first, size_.second, "0"))
{}

void Cell::val(int value_)
{
    value = value_;
    init_value();
}

void Cell::init_value()
{
    sprintf(strval, "%d", value);
    box->label(strval);
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
