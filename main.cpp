/*
    Jogo da velha feito em C++ e Allegro5
    desenvolvido por João Queiroz de Almeida Neto
	gitHub: https://github.com/netoptc
*/


#include "game.h"

int  main(){

    ALLEGRO_MOUSE_STATE state;
    ALLEGRO_EVENT_QUEUE *queue;

    if (!al_init()){
        fprintf(stderr, "Falha ao inicializar a Allegro 5\n");
        return -1;
    }

    if (!al_init_ttf_addon()){
        fprintf(stderr, "Falha ao inicializar complemento ttf!\n");
        return -1;
    }

    viewport * myViewport = new viewport();

    queue =  al_create_event_queue();
    al_register_event_source (queue,al_get_mouse_event_source());
    al_register_event_source (queue,al_get_display_event_source (myViewport->getDisplay()));

    int player = 1;
    bool running = true;
    while (running){
        al_flip_display();
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            al_get_mouse_state(&state);
            running = myViewport->onClickBoxDisplay(state.x, state.y, &player);
        }
    }

    al_destroy_display (myViewport->getDisplay());
    al_uninstall_keyboard();

    return  0 ;
}

