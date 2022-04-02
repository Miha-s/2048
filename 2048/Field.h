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

/* 
   This class is created to manage the whole game:
   move cells, add cells, check for lose or win
*/

class Field {
    Pair size;
    // Pair.first  - x
    // Pair.second - y
    std::vector<std::shared_ptr<Cell>> cells;
    Fl_Window* win;
    int max_val;    // the value to win
    int base;       // value for new generated cell

    typedef void (*gover_t)(int, void*);    // game over callback type
    gover_t gover_callback;
    void* data;             // data to this callback
public:
    Field(Pair s, Pair bs, int spacing, int max_val_, 
                                int base_, Fl_Window* win_);
    
    void step(direction dir);  // make a move
    void callback(gover_t go, void* data); // set callback
                                           // 1 - lose
                                           // 0 - win
    Fl_Window* window() { return win; }
    void reset();   // set field to default
    
    ~Field();
private:
    // check for end of the game and generate a new number
    void generate_num();
    int check_lose();

    inline int pos(int i, int j) { return i*size.first + j; }

    int combine(direction dir); // add cells
    void move_(direction dir);  // move cells
    inline int comb(int i, int j, std::shared_ptr<Cell> &tmp);
    inline int move(int i, int j, std::shared_ptr<Cell> &tmp);
};

#endif //FIELD_H
