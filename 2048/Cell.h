#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <memory>
#include <utility>
#include <string.h>
#include "enumeration.h"

/*
   The class is created to keep value and box of the cell
   And to combine and move this cells
*/

class Cell {
    int value;
    std::shared_ptr<Fl_Box> box;
    char strval[20];    // converted value to string
public:
    Cell(Pair pos_, Pair size_);
    Cell(const Cell& c);
    void val(int value_); 
    int val() { return value; }

    void move_to(Cell &c); // switching value between Cells
    void combine_with(Cell &c); // adding value from other Cell
                                // and setting that cell's value to 0

    ~Cell();
private:
    void init_value();  // converting value to string and setting to the box
};
