#include <memory>
#include <utility>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <vector>
#include "Cell.h"


using Pair = std::pair<int, int>;
enum class direction : char;

// Pair.first  - x
// Pair.second - y



class Field {
    Pair size;
    std::unique_ptr<Fl_Window> win;
    std::vector<std::unique_ptr<Cell>> cells;
public:
    Field(Pair s, int spacing);
    void move(direction dir);
    
    ~Field();
};

