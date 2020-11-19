#include "game.h"

#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGHT 480


button::button(float x1, float x2, float x3, float x4, ALLEGRO_COLOR  colorButton, ALLEGRO_COLOR  colorText, const char *text , ALLEGRO_FONT *fonte1) :x1(x1), x2(x2), x3(x3), x4(x4){
     al_draw_filled_rectangle(x1, x2, x3, x4, colorButton);
     al_draw_text(fonte1,colorText, x1 + ((x3-x1)/2), x2+ ((x4-x2)/2 -5), ALLEGRO_ALIGN_CENTRE , text);
     mark = 0;
}

viewport::viewport(){
    /*inicializando perifericos*/
    al_install_mouse();
    al_init_font_addon();
    al_init_primitives_addon();
    fonte1 = al_load_ttf_font("fonts/arial.ttf",12, 0);
    fonte2 = al_load_ttf_font("fonts/arial.ttf",100, 0);

    /*inicializando display*/
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    al_set_window_title(display, "Jogo da Velha");

    if (!display){
        fprintf(stderr, "Falha ao criar a janela\n");
    }

    drawMap();
    drawScore();

    boxDisplay[0] = new button(10, 450, 50, 470,al_map_rgba(255,255,255,255),al_map_rgb(0,0,0), "RESET", fonte1);
    boxDisplay[1] = new button(70, 450, 110, 470,al_map_rgba(255,255,255,255),al_map_rgb(0,0,0), "QUIT", fonte1);

    boxDisplay[2] = new button(120, 40, 248, 170, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);
    boxDisplay[3] = new button(256, 40, 385, 170, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);
    boxDisplay[4] = new button(393, 40, 520, 170, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);

    boxDisplay[5] = new button(120, 175, 248, 305, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);
    boxDisplay[6] = new button(256, 175, 385, 305, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);
    boxDisplay[7] = new button(393, 175, 520, 305, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);

    boxDisplay[8] = new button(120, 312, 248, 440, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);
    boxDisplay[9] = new button(256, 312, 385, 440, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);
    boxDisplay[10]= new button(393, 312, 520, 440, al_map_rgba(0,0,0,0),al_map_rgb(0,0,0), "", fonte1);

    scorPlayer1 = 0;
    scorPlayer2 = 0;

}

void viewport::drawMap(){
    /*linhas do jogo da velha*/
    al_clear_to_color(al_map_rgba(0,0,0,0));
    al_draw_line(120,172.33,DISPLAY_WIDTH - 120 ,172.33, al_map_rgb(255,255,255),9);
    al_draw_line(120,308.66,DISPLAY_WIDTH - 120 ,308.66, al_map_rgb(255,255,255),9);
    al_draw_line(252.33,40,252.33,DISPLAY_HEIGHT - 40, al_map_rgb(255,255,255),9);
    al_draw_line(388.66,40,388.66,DISPLAY_HEIGHT - 40, al_map_rgb(255,255,255),9);
}


void viewport::resetViewport(){

    drawMap();
    drawScore();
    for(int i = 0; i<11; i++){
        boxDisplay[i]->mark = 0;
    }
    boxDisplay[0] = new button(10, 450, 50, 470,al_map_rgba(255,255,255,255),al_map_rgb(0,0,0), "RESET", fonte1);
    boxDisplay[1] = new button(70, 450, 110, 470,al_map_rgba(255,255,255,255),al_map_rgb(0,0,0), "QUIT", fonte1);

}

ALLEGRO_DISPLAY * viewport::getDisplay(){
    return display;
}

bool button::getClick(int x, int y){
    if(x >= x1 && x <= x3)
        if(y >= x2 && y <= x4)
            return true;
    return false;
}

bool viewport::onClickBoxDisplay(int x, int y, int * player){
    for(int i = 0; i< 11; i++){
        if(boxDisplay[i]->getClick(x,y)){
            switch(i){
                case 0:
                    scorPlayer1 = 0;
                    scorPlayer2 = 0;
                    resetViewport();
                    return true;
                case 1:
                    return false;
                default:
                    drawChoice(i, boxDisplay[i], player);
                    int result = checkWinner();
                    if(result == 1){
                        scorPlayer1+= 1;
                        resetViewport();
                    }else if(result == 2){
                        scorPlayer2+= 1;
                        resetViewport();
                    }else if(result == 3){
                        resetViewport();
                    }
                    return true;
            }
        }
    }
    return true;
}

void viewport::drawScore(){
    std::string scor1 = "PLAYER1: ";
    std::string scor2 = "PLAYER2: ";
    scor1.append(toString(scorPlayer1));
    scor2.append(toString(scorPlayer2));
    al_draw_text(fonte1,al_map_rgba(255,255,255,255), 10, 10, 0, scor1.c_str());
    al_draw_text(fonte1,al_map_rgba(255,255,255,255), 10, 30, 0, scor2.c_str());
}

void viewport::drawChoice(int i, button * boxDisplay, int * player){
    if(!boxDisplay->mark){
        if(*player == 1){
            al_draw_text(fonte2,al_map_rgba(255,255,255,100),boxDisplay->x1 + 30, boxDisplay->x2 + 10, 0, "X");
            boxDisplay->mark = 1;
            *player = 2;
        }else{
            al_draw_text(fonte2,al_map_rgba(255,255,255,100),boxDisplay->x1 + 25, boxDisplay->x2 + 10, 0, "O");
            boxDisplay->mark = 2;
            *player = 1;
        }

    }
}
int viewport::checkWinner(){

    if(boxDisplay[2]->mark == 1 && boxDisplay[3]->mark == 1  && boxDisplay[4]->mark == 1)
        return 1;
    if(boxDisplay[2]->mark == 2 && boxDisplay[3]->mark == 2  && boxDisplay[4]->mark == 2)
        return 2;
    if(boxDisplay[5]->mark == 1 && boxDisplay[6]->mark == 1  && boxDisplay[7]->mark == 1)
        return 1;
    if(boxDisplay[5]->mark == 2 && boxDisplay[6]->mark == 2  && boxDisplay[7]->mark == 2)
        return 2;
    if(boxDisplay[8]->mark == 1 && boxDisplay[9]->mark == 1  && boxDisplay[10]->mark == 1)
        return 1;
    if(boxDisplay[8]->mark == 2 && boxDisplay[9]->mark == 2  && boxDisplay[10]->mark == 2)
        return 2;
    if(boxDisplay[2]->mark == 1 && boxDisplay[5]->mark == 1  && boxDisplay[8]->mark == 1)
        return 1;
    if(boxDisplay[2]->mark == 2 && boxDisplay[5]->mark == 2  && boxDisplay[8]->mark == 2)
        return 2;
    if(boxDisplay[3]->mark == 1 && boxDisplay[6]->mark == 1  && boxDisplay[9]->mark == 1)
        return 1;
    if(boxDisplay[3]->mark == 2 && boxDisplay[6]->mark == 2  && boxDisplay[9]->mark == 2)
        return 2;
    if(boxDisplay[4]->mark == 1 && boxDisplay[7]->mark == 1  && boxDisplay[10]->mark == 1)
        return 1;
    if(boxDisplay[4]->mark == 2 && boxDisplay[7]->mark == 2  && boxDisplay[10]->mark == 2)
        return 2;
    if(boxDisplay[2]->mark == 1 && boxDisplay[6]->mark == 1  && boxDisplay[10]->mark == 1)
        return 1;
    if(boxDisplay[2]->mark == 2 && boxDisplay[6]->mark == 2  && boxDisplay[10]->mark == 2)
        return 2;
    if(boxDisplay[4]->mark == 1 && boxDisplay[6]->mark == 1  && boxDisplay[8]->mark == 1)
        return 1;
    if(boxDisplay[4]->mark == 2 && boxDisplay[6]->mark == 2  && boxDisplay[8]->mark == 2)
        return 2;


    for(int i=2; i < 11; i++){
        if(boxDisplay[i]->mark == 0)
            return 0;
    }


    return 3;
}

