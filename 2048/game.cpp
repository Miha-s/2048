#include "Field.h"
#include "Window.h"
#include <FL/Fl_Button.H>

struct data_t {
    Field *f;
    Fl_Group *gr;
};

void init_game_over(Field *field, data_t &dat);
void game_over(int lose, void *data)
{
    data_t *dat = (data_t*)data;
    const char *mes;
    if(lose)
        mes = "You lost. Do you wanna play again?";
    else
        mes = "You have won! Do you wanna play again?";
    Fl_Widget *mes_box = dat->gr->child(1);
    mes_box->label(mes);
    dat->gr->show();
}

void end_callback(Fl_Widget *w, void *data)
{
    data_t *dat = (data_t*)data;
    dat->f->window()->hide();
}

void reset_callback(Fl_Widget *w, void *data)
{
    data_t *dat = (data_t*)data;
    dat->f->reset();
    dat->gr->hide();
}

/*

*/
int main()
{
    Pair size(4, 4);
    Pair but_size(100, 100);
    Window *win = new Window("2048");
    Field field(size, but_size, 10, win);
    data_t data;
    field.callback(game_over, (void*)&data);
    win->field(&field);

    data.f = &field;
    
    init_game_over(&field, data);
    game_over(1, &data);

    win->show();

    return Fl::run();
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
    Fl_Box *box = new Fl_Box(pos_x, pos_y, box_size_x, box_size_y);
    box->box(FL_RFLAT_BOX);

    pos_x += spac;
    pos_y += spac;
    Fl_Box *mes_box = new Fl_Box(pos_x, pos_y, mes_size_x, mes_size_y);
    //mes_box->label(mes);
    mes_box->labelsize(20);

    int but_pos_x = pos_x + (mes_size_x - 2*but_size_x)/3;
    int but_pos_y = pos_y + spac + mes_size_y;

    Fl_Button *but_no = new Fl_Button(but_pos_x, but_pos_y, 
                                but_size_x, but_size_y, "no");
    //but_no->box(FL_NO_BOX);
    but_no->labelsize(23);
    but_no->callback(end_callback, &dat);

    but_pos_x += but_size_x + (mes_size_x - 2*but_size_x)/3;
    Fl_Button *but_yes = new Fl_Button(but_pos_x, but_pos_y, 
                                but_size_x, but_size_y, "yes");
    //but_yes->box(FL_NO_BOX);
    but_yes->labelsize(23);
    but_yes->callback(reset_callback, &dat);

    gr->end();
    win->end();
    
    dat.gr = gr;
    gr->hide();
}
