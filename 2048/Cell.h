#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <memory>
#include <utility>


using Pair = std::pair<int, int>;

class Cell {
    Pair pos;
    Pair size;
    int value;
    std::shared_ptr<Fl_Box> box;
public:
    Cell(Pair pos_, Pair size_);
    void move_to(Cell &c);
    void combine_with(Cell &c);

    ~Cell();
};
