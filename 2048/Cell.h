#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <memory>
#include <utility>
#include <string.h>


using Pair = std::pair<int, int>;

class Cell {
    int value;
    std::shared_ptr<Fl_Box> box;
    char strval[20];
public:
    Cell(Pair pos_, Pair size_);
    Cell(const Cell& c);
    void val(int value_); 
    void move_to(Cell &c);
    void combine_with(Cell &c);
    int val() { return value; }

    ~Cell();
private:
    void init_value();
};
