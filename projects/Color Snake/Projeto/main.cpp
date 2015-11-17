#include <allegro.h>

#include "Jogo.h"

void initAllegro();
void deinitAllegro();
    
int main() {
	initAllegro();
	    
    BITMAP *buffer = create_bitmap(TAMANHO_TELA_X, TAMANHO_TELA_Y);
    Menu inicial;
    Jogo csnake; //Iniando o Color Snake
    bool jogoTerminado = false;
    double tempoAux = clock();
    
	while (!key[KEY_ESC]) {
          
        while(inicial.naoEscolheu()){ //escolhendo o nivel/velocidade do jogo
            int k = inicial.escolherNivel(buffer);
            csnake.setVelocidade(k);
            jogoTerminado = false;
        }
	    csnake.identificaDirecao(); //identifica quando a cobra muda de direcao
		if( clock() - tempoAux > csnake.getVelocidade()){
             if(key[KEY_P])
                 allegro_message("PAUSE");
             clear_bitmap(buffer);
             csnake.movimenta();
             csnake.desenhar(buffer);
             if(csnake.perdeu(buffer)){
                 if(csnake.getPontuacao() > 0 )
                     allegro_message("SUA PONTUACAO FOI DE %d",csnake.getPontuacao());
                 inicial.atualizaPontuacao(csnake.getPontuacao(),csnake.getVelocidade());
                 inicial.novoJogo();
                 csnake.reiniciaJogo();
                 jogoTerminado = true;
             }
             if(!jogoTerminado){  
                 csnake.comer(buffer);
                 int pts = csnake.retira(buffer); //retira e adiciona pontos
                 if(pts != 1)
                     csnake.addPontuacao(pts);    
             }
             tempoAux = clock();  
        }  
	}
    destroy_bitmap(buffer);
	deinitAllegro();
	return 0;
}
END_OF_MAIN()

void initAllegro() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, TAMANHO_TELA_X, TAMANHO_TELA_Y, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	show_mouse(screen);
}

void deinitAllegro() {
	clear_keybuf();
}
