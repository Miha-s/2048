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
    std::shared_ptr<Fl_Window> win;
    std::vector<std::shared_ptr<Cell>> cells;
public:
    Field(Pair s, Pair bs, int spacing);
    void move(direction dir);
    std::shared_ptr<Fl_Window> window() { return win; }
    
    ~Field();
private:
    void generate_num();
    inline int pos(int i, int j) { return i*size.first + j; }
    inline void comb(int i, int j, std::shared_ptr<Cell> tmp);
    inline int move(int i, int j, std::shared_ptr<Cell> tmp);
    void combine(direction dir);
    void move_(direction dir);
};

