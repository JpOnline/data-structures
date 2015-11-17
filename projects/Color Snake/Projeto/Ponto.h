#ifndef _PONTO_H_
#define _PONTO_H_

#define TAMANHO_DO_PONTO 8 
#define CONTINUA -1

//Cores usadas no jogo
#define vermelho makecol(255, 0, 0)
#define laranja makecol(254, 104, 0)
#define amarelo makecol(252, 229, 3)
#define verde makecol(0, 128, 0)
#define azul makecol(0, 128, 255)
#define anil makecol(0, 0, 160)
#define roxo makecol(128, 0, 128)
#define rosa makecol(255, 0, 128)

//direcoes do movimento da cobra
enum Direcao{cima, baixo, esquerda, direita};

class Ponto{
      private:
             int cor; //cor do ponto
             int posicaoX; //posicaoX dentro da tela
             int posicaoY; //posicaoY dentro da tela
             int direcao; // direcao que o ponto está
      public:
             Ponto();
             Ponto(int, int, int); //contrutor com cor, posX e posY
             int getDirecao(){ return direcao;};
             int getCor(){return cor;}
             int getPosicaoX(){return posicaoX;}
             int getPosicaoY(){return posicaoY;}
             int movimentaPonto(int);//movimenta o ponto na direção correta
};

Ponto::Ponto(){
    direcao = direita;
    posicaoX = 8;
    posicaoY = 8;
    cor = vermelho; 
}

Ponto::Ponto(int c, int pX, int pY){
    direcao = direita;
    posicaoX = (pX>=0 && pX<=TAMANHO_TELA_X) ? pX : 8;
    posicaoY = (pY>=0 && pY<=TAMANHO_TELA_Y) ? pY : 8;
    if(c == amarelo || c == verde || c == laranja || c == roxo || c == rosa || c == azul || c == anil)
        cor = c;
    else
        cor = vermelho;
}

int Ponto::movimentaPonto(int dirNova){
    
    int dirVelha = direcao;
    
    if(dirNova==CONTINUA)//direcao não mudou
        switch(direcao){
              case cima:
                   posicaoY = posicaoY - TAMANHO_DO_PONTO;
                   if(posicaoY < 0)
                       posicaoY = TAMANHO_TELA_Y - 2*TAMANHO_DO_PONTO;
                   break;
              case direita:
                   posicaoX = posicaoX + TAMANHO_DO_PONTO;
                   if(posicaoX > TAMANHO_TELA_X - TAMANHO_DO_PONTO)
                       posicaoX =  TAMANHO_DO_PONTO;
                   break;
              case baixo:
                   posicaoY = posicaoY + TAMANHO_DO_PONTO; 
                   if(posicaoY > TAMANHO_TELA_Y - TAMANHO_DO_PONTO)
                       posicaoY = TAMANHO_DO_PONTO;  
                   break;
              case esquerda:
                   posicaoX = posicaoX - TAMANHO_DO_PONTO;  
                   if(posicaoX < 0)
                       posicaoX = TAMANHO_TELA_X - 2*TAMANHO_DO_PONTO;   
                   break;
              default:
                   posicaoX = posicaoX + TAMANHO_DO_PONTO; 
          }
    else{  //neste caso, direcao mudou;
        direcao = dirNova;
        switch(dirNova){
              case cima:
                   posicaoY = posicaoY - TAMANHO_DO_PONTO;
                   if(posicaoY < 0)
                       posicaoY = TAMANHO_TELA_Y - 2*TAMANHO_DO_PONTO;
                   break;
              case direita:
                   posicaoX = posicaoX + TAMANHO_DO_PONTO;
                   if(posicaoX > TAMANHO_TELA_X - TAMANHO_DO_PONTO)
                       posicaoX =  TAMANHO_DO_PONTO;
                   break;
              case baixo:
                   posicaoY = posicaoY + TAMANHO_DO_PONTO; 
                   if(posicaoY > TAMANHO_TELA_Y - TAMANHO_DO_PONTO)
                       posicaoY = TAMANHO_DO_PONTO;  
                   break;
              case esquerda:
                   posicaoX = posicaoX - TAMANHO_DO_PONTO;  
                   if(posicaoX < 0)
                       posicaoX = TAMANHO_TELA_X - 2*TAMANHO_DO_PONTO;   
                   break;
              default:
                   posicaoX = posicaoX + TAMANHO_DO_PONTO;     
        }
    }
    return(dirVelha);
}

#endif /* _PONTO_H_ */
