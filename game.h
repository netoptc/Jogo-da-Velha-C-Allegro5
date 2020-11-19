#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string>
#include <sstream>

class button{
    private:
        const char *text;
        ALLEGRO_COLOR  colorButton;
        ALLEGRO_COLOR  colorText;

    public:
        float x1, x2, x3, x4;
        int mark;

        button(float x1, float x2, float x3, float x4, ALLEGRO_COLOR  colorButton, ALLEGRO_COLOR  colorText, const char *text,ALLEGRO_FONT *fonte);
        bool getClick(int x, int y);

};

class viewport{
    private:
        ALLEGRO_FONT *fonte1;
        ALLEGRO_FONT *fonte2;
        ALLEGRO_DISPLAY *display;
        button *boxDisplay[11];
        int scorPlayer1,scorPlayer2;

    public:
        viewport();
        ALLEGRO_DISPLAY * getDisplay();
        bool onClickBoxDisplay(int x, int y, int *player);
        void drawChoice(int i, button * boxDisplay, int * player);
        void drawMap();
        void drawScore();
        int checkWinner();
        void resetViewport();


};

template<class T>
std::string toString(const T &value){
    std::ostringstream os;
    os << value;
    return os.str();
}


#endif // GAME_H_INCLUDED
