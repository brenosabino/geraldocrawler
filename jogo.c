#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef int bool;
#define true 1
#define false 0
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

float Distancia(float x1, float x2, float y1, float y2){
	return sqrtf(pow((x2 - x1), 2) + pow((y2 -y1), 2));
}

typedef struct Heroi{
        const char* nome;
        int ataque;
        int hp;
        int x, y;
        int raio;
        int deslocamento;
        int desx;
        int desy;
} Heroi;

void inicializa(Heroi *hero){
        hero->nome = "Geraldo orriver";
        hero->ataque = 20;
        hero->hp = 100;
        hero->x = 400;
        hero->y = 300;
        hero->raio = 20;
        hero->deslocamento = 3;
        hero->desx = hero->x;
        hero->desy = hero->y;
}

void Destino_heroi(Heroi *hero, float destinox, float destinoy){
	float taxa = hero->deslocamento/Distancia(hero->x, destinox, hero->y, destinoy);
	
	hero->x += ((destinox-hero->x)*taxa);
	hero->y += ((destinoy-hero->y)*taxa);
}
 
typedef struct Inimigo{
        char* nome;
        int hp;
        int ataque;
} Inimigo;
 
typedef struct Boss{
        char* nome;
        int hp;
        int ataque;
} Boss;

void draw(Heroi *hero){
    al_clear_to_color(al_map_rgb(255,255,255)); //Desenha fundo da tela
    if(hero->x <= hero->desx && hero->y <= hero->desy){
		hero->x = hero->desx;
		hero->y = hero->desy;
	}
    al_draw_filled_circle(hero->x, hero->y, hero->raio, al_map_rgb(255,0,255)); //Desenha heroi
}
 
void jogada(bool *fim, Heroi *hero){
  //Para futuro uso
}
 
int main(){
        Heroi hero;

        ALLEGRO_DISPLAY *tela;
        ALLEGRO_EVENT_QUEUE *eventos;
        ALLEGRO_TIMER *draw_timer;
        int display_w = 800;
        int display_h = 600;
        float fps = 60.0;

        al_init();

        tela = al_create_display(display_w,display_h);
        eventos = al_create_event_queue();
        draw_timer = al_create_timer(1.0/fps);

        al_install_keyboard();
        al_install_mouse();
        al_init_primitives_addon();

        al_register_event_source(eventos, al_get_keyboard_event_source());
        al_register_event_source(eventos, al_get_mouse_event_source());
        al_register_event_source(eventos, al_get_timer_event_source(draw_timer));
        al_register_event_source(eventos, al_get_display_event_source(tela));

        bool fim = false;

        al_start_timer(draw_timer);
        
        ALLEGRO_EVENT evento;
        ALLEGRO_KEYBOARD_STATE tec_estado;
        ALLEGRO_MOUSE_STATE estado;

        //Inimigo inimigo[10];
        inicializa(&hero);
        //draw(&hero);
        

        while(!fim){
            al_wait_for_event(eventos, &evento);

        switch(evento.type) {
            case ALLEGRO_EVENT_TIMER:
                al_get_keyboard_state(&tec_estado);
                //jogada(&fim, &hero);
                /*
                if(al_key_down(&tec_estado, ALLEGRO_KEY_W)){
					if(hero.y < 0 + hero.raio)
						hero.y = hero.y;
                    else 
						hero.y -= 3;
				}
                if(al_key_down(&tec_estado, ALLEGRO_KEY_S)){
					if(hero.y > display_h - hero.raio)
						hero.y = hero.y;
                    else 
                    hero.y += 3;
                }
                if(al_key_down(&tec_estado, ALLEGRO_KEY_A)){
					if(hero.x < 0 + hero.raio)
						hero.y = hero.y;
                    else 
                    hero.x -= 3;
                }
                if(al_key_down(&tec_estado, ALLEGRO_KEY_D)){
					if(hero.x > display_w - hero.raio)
						hero.y = hero.y;
                    else 
                    hero.x += 3;
                }*/
            Destino_heroi(&hero, estado.x, estado.y);
            draw(&hero);
            al_flip_display();
            break;
            
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				al_get_mouse_state(&estado);
				hero.desx = estado.x;
				hero.desy = estado.y;
			
			break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fim = true;
            break;
            }
        }
return 0;
}
 
#endif /*_STRUCTS_H_*/
