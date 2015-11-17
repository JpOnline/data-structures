class Menu{
private:
    bool telaInicial;
    unsigned long int melhorPontuacao;
    int melhorVelocidade;
public:
    Menu(){ 
        telaInicial = true;
        melhorPontuacao = 0;
        melhorVelocidade = 30;
    }
    int escolherNivel(BITMAP*);
    bool naoEscolheu(){ return telaInicial;}
    void atualizaPontuacao(unsigned long int,int);
    void novoJogo();

};

int Menu::escolherNivel(BITMAP *buffer){
    BITMAP *telaInicio = load_bitmap("img\\TelaInicio.bmp",NULL);
    BITMAP *telaInicioBotoesSelecionados = load_bitmap("img\\TelaInicioBotoesSelecionados.bmp",NULL);
    
    while(telaInicial){
        if(key[KEY_ESC])
            telaInicial = false;
        clear_bitmap(buffer);
        
        //seleciona botao fazendo-o aumentar
        if(mouse_x > 70 && mouse_x < 200 && mouse_y > 326 && mouse_y < 394){
            blit(telaInicio, buffer, 0, 0, 0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y); 
            blit(telaInicioBotoesSelecionados, buffer, 55, 310, 55, 310, 200, 150);
        }  
        else if(mouse_x > 284 && mouse_x < 425 && mouse_y > 326 && mouse_y < 390 ){
            blit(telaInicio, buffer, 0, 0, 0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y); 
            blit(telaInicioBotoesSelecionados, buffer, 270, 300, 270, 300, 200, 150);
        }
        else if(mouse_x > 510 && mouse_x < 647 && mouse_y > 327 && mouse_y < 390 ){
            blit(telaInicio, buffer, 0, 0, 0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y); 
            blit(telaInicioBotoesSelecionados, buffer, 490, 300, 490, 300, 170, 150);
        }  
        else if(mouse_x > 727 && mouse_x < 920 && mouse_y > 326 && mouse_y < 390 ){
            blit(telaInicio, buffer, 0, 0, 0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y); 
            blit(telaInicioBotoesSelecionados, buffer, 700, 300, 700, 300, 230, 150);
        }  
        else
            blit(telaInicio, buffer, 0, 0, 0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y);
        
        //retorna velocidade de acordo com o nivel escolhido
        if(mouse_b & 1 && mouse_x > 70 && mouse_x < 200 && mouse_y > 324 && mouse_y < 392){
            telaInicial = false;
            return(70);
        }   
        else if(mouse_b & 1 && mouse_x > 294 && mouse_x < 412 && mouse_y > 330 && mouse_y < 387 ){
            telaInicial = false;
            return(50);
        }
        if(mouse_b & 1 && mouse_x > 520 && mouse_x < 640 && mouse_y > 330 && mouse_y < 387 ){
            telaInicial = false;
            return(30);
        }
        if(mouse_b & 1 && mouse_x > 734 && mouse_x < 910 && mouse_y > 330 && mouse_y < 387 ){
            telaInicial = false;
            return(10);
        }
        
        if(melhorPontuacao > 0){
            textprintf_ex(buffer, font, 400, 255, makecol(0,0,0), -1, "MELHOR PONTUACAO: %d", melhorPontuacao);
            switch(melhorVelocidade){
                case 10:textprintf_ex(buffer, font, 400, 267, makecol(0,0,0), -1, "NIVEL: IMPOSSIVEL"); break;
                case 30:textprintf_ex(buffer, font, 400, 267, makecol(0,0,0), -1, "NIVEL: DIFICIL"); break;
                case 50:textprintf_ex(buffer, font, 400, 267, makecol(0,0,0), -1, "NIVEL: MEDIO"); break;
                case 70:textprintf_ex(buffer, font, 400, 267, makecol(0,0,0), -1, "NIVEL: FACIL"); break;
            }
        }
        blit(buffer, screen, 0, 0, 0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y);
    }
    
    destroy_bitmap(telaInicio);
    destroy_bitmap(telaInicioBotoesSelecionados);
}

void Menu::atualizaPontuacao(unsigned long int pontos,int velocidade){
    if(pontos > melhorPontuacao){
        melhorPontuacao = pontos;
        melhorVelocidade = velocidade;
    }
    
}

void Menu::novoJogo(){
     telaInicial = true;
}
     
