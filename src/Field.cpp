#include "../2048/Field.h"

enum class direction : char { up, down, left, right };

Field::Field(Pair s, Pair bs, int spacing) : size(s)
{
    int size_x = size.first * bs.first + (size.first + 1) * spacing;
    int size_y = size.second * bs.second + (size.second + 1) * spacing;

    win.reset(new Fl_Window(size_x, size_y, "2048"));

    int tmp_y = spacing;
    for(int i = 0; i < size.second; i++) {
        int tmp_x = spacing;
        for(int j = 0; j < size.first; j++) {
            std::shared_ptr<Cell> p (new Cell(Pair(tmp_x, tmp_y), 
                                        Pair(bs.first, bs.second)));
            cells.push_back(p);
            tmp_x += spacing + bs.first;
        }
        tmp_y += spacing + bs.second;
    }
}

inline void Field::comb(int i, int j, std::shared_ptr<Cell> tmp)
{
    std::shared_ptr<Cell> p = cells[pos(i, j)];
    if(tmp->val() && p->val() == tmp->val()) 
    tmp->combine_with(*p);
    tmp = p;
}

void Field::combine(direction dir)
{
    int i = 0;
    int j = 0;

    std::shared_ptr<Cell> tmp;
    
    switch(dir) {
    case direction::right:
        for(; i < size.second; i++) {
            tmp = cells[pos(i, 0)];
            for(; j + 1 < size.first - 1; j++) 
                comb(i, j, tmp);
        }
        break;
    case direction::down:
        for(; j < size.first; j++) {
            tmp = cells[pos(0, j)];
            for(; i + 1 < size.second - 1; i++) 
                comb(i, j, tmp);
        }
        break;
    case direction::left:
        for(; i < size.second; i++) {
            tmp = cells[pos(i, size.first-1)];
            for(j = size.first-2; j >= 0; j--)
                comb(i, j, tmp);
        }
        break;
    case direction::up:
        for(; j < size.first; j++) {
            tmp = cells[pos(size.second-1, j)];
            for(i = size.second - 2; i >= 0; i--)
                comb(i, j, tmp);
        }
        break;
    }
}



void Field::move(int i, int j)
{
    
}


void Field::move(direction dir) 
{
    


}

