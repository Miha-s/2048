#ifndef FIELD_H
#define FIELD_H
#include <memory>
#include <utility>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <vector>
#include "Cell.h"
#include "enumeration.h"

// Pair.first  - x
// Pair.second - y



class Field {
    Pair size;
    std::vector<std::shared_ptr<Cell>> cells;
    Fl_Window* win;

    typedef void (*gover_t)(int, void*);
    gover_t gover_callback;
    void* data;
public:
    Field(Pair s, Pair bs, int spacing, Fl_Window* win_);
    void step(direction dir);
    void callback(gover_t go, void* data);
    Fl_Window* window() { return win; }
    void reset();
    
    ~Field();
private:
    void generate_num();
    inline int pos(int i, int j) { return i*size.first + j; }
    inline void comb(int i, int j, std::shared_ptr<Cell> &tmp);
    inline int move(int i, int j, std::shared_ptr<Cell> &tmp);
    void combine(direction dir);
    void move_(direction dir);
};

#endif //FIELD_H
