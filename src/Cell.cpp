#include "../2048/Cell.h"


Cell::Cell(Pair pos_, Pair size_) : value(0), 
        box(new Fl_Box(pos_.first, pos_.second, size_.first, size_.second, "0"))
{}


// to do correct
void Cell::move_to(Cell &c)
{   
    std::swap(value, c.value);
    int x = box->x();
    int y = box->y();
    box->position(c.box->x(), c.box->y());
    c.box->position(x, y);
}

// to do correct
void Cell::combine_with(Cell &c)
{
    value *= c.value;
    c.value = 0;
}

Cell::~Cell() {}
