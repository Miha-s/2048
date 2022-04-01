#include "Field.h"
#include "Window.h"
#include <FL/Fl_Button.H>
#include <stdlib.h>
#include <iostream>

struct data_t {
    Field *f;
    Fl_Group *gr;
};

// create and hide window to game over menu
void init_game_over(Field *field, data_t &dat);

// game over callback
void game_over(int lose, void *data);

// close game
void end_callback(Fl_Widget *w, void *data)
{
    data_t *dat = (data_t*)data;
    dat->f->window()->hide();
}

// reset game
void reset_callback(Fl_Widget *w, void *data)
{
    data_t *dat = (data_t*)data;
    dat->f->reset();
    dat->f->window()->child(0)->activate();
    dat->gr->hide();
}

void setry_check(int argc, char **argv, int &size_, int &max_val, int &base);

int main(int argc, char **argv)
{
    int size_ = 4;
    int max_val = 2048;
    int base = 2;

    setry_check(argc, argv, size_, max_val, base);

    Pair size(size_, size_);
    Pair but_size(100, 100);
    Window *win = new Window("2048");
    Field field(size, but_size, 10, max_val, base, win);
    data_t data;
    field.callback(game_over, (void*)&data);
    win->field(&field);

    data.f = &field;
    
    init_game_over(&field, data);

    win->show();

    return Fl::run();
}


void setry_check(int argc, char **argv, int &size_, int &max_val, int &base)
{
    switch(argc) {
        case 4:
            base = strtol(argv[3], 0, 10);
            if(!base) {
                std::cerr << "Incorrect base" << std::endl;
                exit(0);
            }
        case 3: 
        {
            max_val = strtol(argv[2], 0, 10);
            if(!max_val) {
                std::cerr << "Incorrect max value" << std::endl;
                exit(0);
            }
            int tmp = base;
            bool ok = false;
            while(tmp <= max_val) {
                if(tmp == max_val) {
                    ok = true;
                    break;
                }
                tmp *= 2;
            }
            if(!ok) {
                std::cerr << "Incorrect max value" << std::endl;
                exit(0);
            }
        }
        case 2:
            size_ = strtol(argv[1], 0, 10);
            if(!size_) {
                std::cerr << "Incorrect field size" << std::endl;
                exit(0);
            }
            break;
    }
}


void init_game_over(Field *field, data_t &dat) {
    Fl_Window *win = field->window();

    int mes_size_x = 360;
    int mes_size_y = 40;
    int but_size_x = 60;
    int but_size_y = 40;
    int spac = 10;

    int box_size_x = 2*spac + mes_size_x;
    int box_size_y = 3*spac + mes_size_y + but_size_y;

    int pos_x = (field->window()->w() - box_size_x)/2;
    int pos_y = (field->window()->h() - box_size_y)/2;

    win->begin();
    Fl_Group *gr = new Fl_Group(pos_x, pos_y, box_size_x, box_size_y);
    gr->begin();
    Fl_Box *box = new Fl_Box(pos_x, pos_y, box_size_x, box_size_y);
    box->box(FL_RFLAT_BOX);
    box->color(fl_rgb_color(12, 13, 14));


    pos_x += spac;
    pos_y += spac;
    Fl_Box *mes_box = new Fl_Box(pos_x, pos_y, mes_size_x, mes_size_y);
    //mes_box->label(mes);
    mes_box->labelsize(20);
    mes_box->labelcolor(fl_rgb_color(88, 240, 237));


    int but_pos_x = pos_x + (mes_size_x - 2*but_size_x)/3;
    int but_pos_y = pos_y + spac + mes_size_y;

    Fl_Button *but_no = new Fl_Button(but_pos_x, but_pos_y, 
                                but_size_x, but_size_y, "no");
    but_no->box(FL_NO_BOX);
    but_no->labelsize(23);
    but_no->labelcolor(fl_rgb_color(88, 240, 237));
    but_no->callback(end_callback, &dat);
    

    but_pos_x += but_size_x + (mes_size_x - 2*but_size_x)/3;
    Fl_Button *but_yes = new Fl_Button(but_pos_x, but_pos_y, 
                                but_size_x, but_size_y, "yes");
    but_yes->box(FL_NO_BOX);
    but_yes->labelsize(23);
    but_yes->labelcolor(fl_rgb_color(88, 240, 237));
    but_yes->callback(reset_callback, &dat);

    gr->end();
    win->end();
    
    dat.gr = gr;
    gr->hide();
}

void game_over(int lose, void *data)
{
    data_t *dat = (data_t*)data;
    dat->f->window()->child(0)->deactivate();
    const char *mes;
    if(lose)
        mes = "You lost. \nDo you wanna play again?";
    else
        mes = "You won! \nDo you wanna play again?";
    Fl_Widget *mes_box = dat->gr->child(1);
    mes_box->label(mes);
    dat->gr->show();
}
