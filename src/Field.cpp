#include "../2048/Field.h"

Field::Field(Pair s, Pair bs, int spacing, int max_val_, int base_, Fl_Window* win_) : 
                        size(s), max_val(max_val_), base(base_)
{
    // resizing window and creating cells
    win = win_;
    
    int size_x = size.first * bs.first + (size.first + 1) * spacing;
    int size_y = size.second * bs.second + (size.second + 1) * spacing;
    win->size(size_x, size_y);
    
    win->begin();
    win->color(fl_rgb_color(183,206,228));
    Fl_Group *cells_gr = new Fl_Group(0, 0, size_x, size_y);
    cells_gr->begin();
    
    int tmp_y = spacing;
    for(int i = 0; i < size.second; i++) {
        int tmp_x = spacing;
        for(int j = 0; j < size.first; j++) {
            std::shared_ptr<Cell> p (new Cell(Pair(tmp_x, tmp_y), bs));
            cells.push_back(p);
            tmp_x += spacing + bs.first;
        }
        tmp_y += spacing + bs.second;
    }
    cells_gr->end();
    win->end();
    generate_num();
}

// additional func to check for lose
int Field::check_lose()
{
    std::vector<std::shared_ptr<Cell>> cell_vec;
    for(int i = 0; i < size.first*size.second; i++) {
        std::shared_ptr<Cell> c(new Cell(*cells[i]));
        cell_vec.push_back(c);
    }
    int c = 0;
    if(combine(direction::up))
        c++;
    if(combine(direction::down))
        c++;
    if(combine(direction::left))
        c++;
    if(combine(direction::right))
        c++;
    if(c) {
        for(int i = 0; i < size.first*size.second; i++) 
            cells[i]->val(cell_vec[i]->val());
        return 0;
    }
    return 1;
}

void Field::generate_num()
{
    bool lose = true;
     
    for(int i = 0; i < size.first * size.second; i++) {
        if(cells[i]->val() == max_val) {
            gover_callback(0, data);
            return;
        } else if (cells[i]->val() == 0) {
            lose = false;
        }
    }
    if(lose) {
        if(check_lose())
            gover_callback(1, data);
        return;
    }
    
    while(true) {
        int r = rand()%(size.first*size.second);
        if(cells[r]->val() == 0) {
            cells[r]->val(base);
            break;
        }
    }
}

// additional function for combining two cells, 
// return 1 if cells was added, else return 0
inline int Field::comb(int i, int j, std::shared_ptr<Cell> &tmp)
{
    std::shared_ptr<Cell> p = cells[pos(i, j)];
    if(!tmp->val()) {
        tmp = p;
        return 0;
    }
    if(p->val()) {
        if(p->val() == tmp->val()) {
            tmp->combine_with(*p);
            tmp = p;
            return 1;
        }
        tmp = p;
    }
    return 0;
}

int Field::combine(direction dir)
{
    int i = 0;
    int j = 0;
    int c = 0;

    std::shared_ptr<Cell> tmp;
    
    switch(dir) {
    case direction::left:
        for(; i < size.second; i++) {
            tmp = cells[pos(i, 0)];
            for(j = 1; j < size.first; j++) 
                c += comb(i, j, tmp);
        }
        break;
    case direction::up:
        for(; j < size.first; j++) {
            tmp = cells[pos(0, j)];
            for(i = 1; i < size.second; i++) 
                c += comb(i, j, tmp);
        }
        break;
    case direction::right:
        for(; i < size.second; i++) {
            tmp = cells[pos(i, size.first-1)];
            for(j = size.first-2; j >= 0; j--)
                c += comb(i, j, tmp);
        }
        break;
    case direction::down:
        for(; j < size.first; j++) {
            tmp = cells[pos(size.second-1, j)];
            for(i = size.second-2; i >= 0; i--)
                c += comb(i, j, tmp);
        }
        break;
    }
    return c;
}

// additional function to move cell
// return 1 when cell can't be moved to thins position(tmp)
// or has been moved 
int Field::move(int i, int j, std::shared_ptr<Cell> &tmp)
{
    if(tmp->val())
        return 1;
    std::shared_ptr<Cell> p = cells[pos(i, j)];
    if(p->val()) {
        p->move_to(*tmp);
        return 1;
    }
    return 0;
}


void Field::move_(direction dir)
{
    int i = 0;
    int j = 0;
    int k = 0;

    std::shared_ptr<Cell> tmp;

    switch(dir) {
    case direction::left:
        for(; i < size.second; i++) {
            for(j = 0; j < size.first-1; j++) {
                tmp = cells[pos(i, j)];
                for(k = j+1; k < size.first; k++) 
                    if(move(i, k, tmp))
                        continue;
            }
        }
        break;
    case direction::up:
        for(; j < size.first; j++) {
            for(i = 0; i < size.second-1; i++) {
                tmp = cells[pos(i, j)];
                for(k = i+1; k < size.second; k++) 
                    if(move(k, j, tmp))
                        continue;
            }
        }
        break;
    case direction::right:
        for(; i < size.second; i++) {
            for(j = size.first-1; j > 0; j--) {
                tmp = cells[pos(i, j)];
                for(k = j-1; k >= 0; k--)
                    if(move(i, k, tmp))
                        continue;
            }
        }
        break;
    case direction::down:
        for(; j < size.first; j++) {
            for(i = size.second-1; i > 0; i--) {
                tmp = cells[pos(i, j)];
                for(k = i-1; k >= 0; k--)
                    if(move(k, j, tmp))
                        continue;
            }
        }
        break;
    }

}


void Field::step(direction dir) 
{
    combine(dir);
    move_(dir);
    generate_num();
}

void Field::callback(gover_t go, void* data_)
{
    gover_callback = go;
    data = data_;
}

void Field::reset()
{
    for(auto cell : cells) {
        cell->val(0);
    }
    generate_num();
}

Field::~Field() {}
