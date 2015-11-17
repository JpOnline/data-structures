#ifndef _JOGO_H_
#define _JOGO_H_

#define CONTINUA -1
#define TAMANHO_TELA_X 976
#define TAMANHO_TELA_Y 520

#include <time.h>
#include "Ponto.h" 
#include "Fila.h"
#include "Menu.h"

int corAleatoria(); //retorna uma cor aleatória

void desenharPonto(Ponto p, BITMAP *);
void desenharFila(Fila<Ponto>,BITMAP*); //exibe a Fila de Pontos

class Jogo{
private:
    int velocidade; //atributo que controla a velocidade do jogo
    unsigned long int pontuacao; //pontuação do jogo
    int direcionado; //controle de direção da cobra
    int borda[50]; // cores da borda da tela
    bool maisVelocidade;  // para não atualizar velocidade diversas vezes num único aperto
    Fila<Ponto> snake; // Fila de Pontos que será usado na Snake
    
    Ponto comida[100]; // máximo de 50 pontos paralelos
    int qtdComida;
    
    void desenharCenario(BITMAP *); //desenha a borda do jogo
    void desenharComida(BITMAP *);
    void posicaoAleatoria(int &, int &);
    bool colidiu(BITMAP *); //checa se a snake bateu em algum ponto ou borda
    
public:
    Jogo(); //construtor da classe
    void reiniciaJogo();
    void setVelocidade(int); // aumenta ou diminui com PGUP ou PGDOWN
    int getVelocidade(){return velocidade;}
    unsigned long int getPontuacao(){ return pontuacao;}
    bool perdeu(BITMAP*);
    
    int identificaDirecao(); //identifica qual direção foi escolhida no teclado
    unsigned long int addPontuacao(unsigned long int); //aumenta ou diminui a pontuação
    void movimenta(); //controla a movimentação do jogo
    void comer(BITMAP*);
    int retira(BITMAP*); //retira um ponto ou mais pontos, quando possível. Retorna os pontos para adicionar, mas nunca no MAIN
    void desenhar(BITMAP*); //método que controla os gráficos do jogo
    bool ehCobra(int, int); //verifica se um pixal (x,y) está na cobra
};

Jogo::Jogo(){
    srand(time(NULL));
    
    velocidade = 30;
    pontuacao = 0;
    direcionado= CONTINUA;
    
    bool ok;
    int cor1 = corAleatoria();
    int cor2;
    for(int i=0; i<10; i++){
        cor2 = corAleatoria();
        while(cor1 == cor2)
            cor2 = corAleatoria();
        Ponto ponto(cor1, TAMANHO_TELA_X/2 -(i+2)*TAMANHO_DO_PONTO, (TAMANHO_TELA_Y/(2*TAMANHO_DO_PONTO))*TAMANHO_DO_PONTO);
        snake.insere(ponto, ok); 
        cor1 = cor2;
    }
    //Inicializando cores da borda
    borda[0] = corAleatoria();
    for(int i=1; i<50; i++){
        borda[i] = corAleatoria();
        while(borda[i] == borda[i-1])
            borda[i] = corAleatoria();
    }
    
    int x, y;
    posicaoAleatoria(x, y);
    Ponto c(corAleatoria(), x, y);
    comida[0] = c;
    qtdComida = 0;
}

void Jogo::reiniciaJogo(){
    
    velocidade = 30;
    pontuacao = 0;
    direcionado = CONTINUA;
    bool ok;
    while(!snake.vazia()){
        Ponto temp;
        snake.retira(temp,ok);
    }
    int cor1 = corAleatoria();
    int cor2;
    for(int i=0; i<10; i++){
        cor2 = corAleatoria();
        while(cor1 == cor2)
            cor2 = corAleatoria();
        Ponto ponto(cor1, TAMANHO_TELA_X/2 -(i+2)*TAMANHO_DO_PONTO, (TAMANHO_TELA_Y/(2*TAMANHO_DO_PONTO))*TAMANHO_DO_PONTO);
        snake.insere(ponto, ok); 
        cor1 = cor2;
    }
    //Inicializando cores da borda
    borda[0] = corAleatoria();
    for(int i=1; i<50; i++){
        borda[i] = corAleatoria();
        while(borda[i] == borda[i-1])
            borda[i] = corAleatoria();
    }
    
    int x, y;
    posicaoAleatoria(x, y);
    Ponto c(corAleatoria(), x, y);
    comida[0] = c;
    qtdComida = 0;
}

void Jogo::setVelocidade(int k){
     if(k == 10)
         velocidade = 10;
     else if(k == 50)
         velocidade = 50;
     else if(k == 70)
         velocidade = 70;
     else
         velocidade = 30;
}

int Jogo::identificaDirecao(){
    if(snake.getTotal() == 0)//caso não haja pontos
        return 0;
    
    int direcao = snake.getInicio()->getInfo().getDirecao();
    
    if(direcionado != CONTINUA)//até o próximo ciclo, a direção não muda
        return (direcionado);
    
    if((key[KEY_UP] || key[KEY_W]) && (direcao != baixo)){
         direcionado = cima;
         return(cima);//posicaoY = posicaoY - 8;
     }else if((key[KEY_RIGHT] || key[KEY_D]) && (direcao != esquerda)){
         direcionado = direita;
         return(direita);//posicaoX = posicaoX + 8;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
     }else if((key[KEY_DOWN] || key[KEY_S]) && (direcao != cima)){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
         direcionado = baixo;
         return(baixo);//posicaoY = posicaoY + 8;
     }else if((key[KEY_LEFT] || key[KEY_A]) && (direcao != direita)){
         direcionado = esquerda;
         return(esquerda);//posicaoX = posicaoX - 8;
     }else 
         return CONTINUA;
}

unsigned long int Jogo::addPontuacao(unsigned long int pontos){
    pontuacao += pontos;
}

bool Jogo::perdeu(BITMAP *buffer){
         
    if(snake.getTotal() == 0){
           pontuacao = (pontuacao*130)/100;
           clear_bitmap(buffer);
           desenhar(buffer);
           return true;
    }
    
    Ponto inicio = snake.getInicio()->getInfo();    
    if(colidiu(buffer)&&((inicio.getPosicaoX() < TAMANHO_DO_PONTO) || (inicio.getPosicaoX() >= TAMANHO_TELA_X - TAMANHO_DO_PONTO)||
           (inicio.getPosicaoY() < TAMANHO_DO_PONTO) || (inicio.getPosicaoY() >= TAMANHO_TELA_Y - TAMANHO_DO_PONTO)))     
            return true;
    switch(inicio.getDirecao()){
        case cima:
            if(ehCobra(inicio.getPosicaoX(), inicio.getPosicaoY() - TAMANHO_DO_PONTO)&&
               ehCobra(inicio.getPosicaoX() + TAMANHO_DO_PONTO, inicio.getPosicaoY() - TAMANHO_DO_PONTO)&&
               ehCobra(inicio.getPosicaoX() - TAMANHO_DO_PONTO, inicio.getPosicaoY() - TAMANHO_DO_PONTO))
                return true;
        case baixo:
            if(ehCobra(inicio.getPosicaoX(), inicio.getPosicaoY() + TAMANHO_DO_PONTO)&&
               ehCobra(inicio.getPosicaoX() + TAMANHO_DO_PONTO, inicio.getPosicaoY() + TAMANHO_DO_PONTO)&&
               ehCobra(inicio.getPosicaoX() - TAMANHO_DO_PONTO, inicio.getPosicaoY() + TAMANHO_DO_PONTO))
                return true;
            break;
        case direita:
            if(ehCobra(inicio.getPosicaoX() + TAMANHO_DO_PONTO, inicio.getPosicaoY())&&
               ehCobra(inicio.getPosicaoX() + TAMANHO_DO_PONTO, inicio.getPosicaoY() + TAMANHO_DO_PONTO)&&
               ehCobra(inicio.getPosicaoX() + TAMANHO_DO_PONTO, inicio.getPosicaoY() - TAMANHO_DO_PONTO))
                return true;
        case esquerda:
            if(ehCobra(inicio.getPosicaoX() - TAMANHO_DO_PONTO, inicio.getPosicaoY())&&
               ehCobra(inicio.getPosicaoX() - TAMANHO_DO_PONTO, inicio.getPosicaoY() + TAMANHO_DO_PONTO)&&
               ehCobra(inicio.getPosicaoX() - TAMANHO_DO_PONTO, inicio.getPosicaoY() - TAMANHO_DO_PONTO))
                return true;
        }
    return false;
}

void Jogo::movimenta(){
    
    if (snake.getTotal() == 0)
        return;
        
    Node<Ponto> *p = snake.getInicio();
    //atualizando o primeiro ponto   
    Ponto atual = p->getInfo();
    int proximaDir = atual.movimentaPonto(identificaDirecao());
    p->setInfo(atual);
    p = p->getDireita();
    //atualizando demais pontos
    while(p != snake.getInicio()){
        atual = p->getInfo();
        proximaDir = atual.movimentaPonto(proximaDir);//atualiza coordenadas do ponto
        p->setInfo(atual);
        p = p->getDireita();
    }
    //ciclo se completa aqui
    direcionado = CONTINUA;
}

void Jogo::comer(BITMAP *buffer){
    Ponto inicio = snake.getInicio()->getInfo();
    
    int dirContraria;
    if(snake.getFim()->getInfo().getDirecao() == direita)
        dirContraria = esquerda;
    else if(snake.getFim()->getInfo().getDirecao() == esquerda)
        dirContraria = direita;
    else if(snake.getFim()->getInfo().getDirecao() == cima)
        dirContraria = baixo;
    else if(snake.getFim()->getInfo().getDirecao() == baixo)
        dirContraria = cima;
    
    if(colidiu(buffer)){
        bool ok;
        int i=0;
        
        //procurando ponto que foi encontrado                
        while(comida[i].getPosicaoX() !=  inicio.getPosicaoX() || comida[i].getPosicaoY() != inicio.getPosicaoY())
            i++;
        
        //inserindo ultimo ponto                
        Ponto u(comida[i].getCor(), snake.getFim()->getInfo().getPosicaoX(), snake.getFim()->getInfo().getPosicaoY());
        u.movimentaPonto(dirContraria);
        snake.insere(u, ok);
        
        //substituindo comida
        int x, y;
        posicaoAleatoria(x, y);
        int j = 0;
        while (j <= qtdComida && j<100 ){
            if(x == comida[j].getPosicaoX() && y == comida[j].getPosicaoY()){
                posicaoAleatoria(x,y);
                j = 0;
            }
            j++;  
        }
        int cor = corAleatoria();
        while(cor == comida[i-1].getCor())
            cor = corAleatoria();
        Ponto c(corAleatoria(), x, y);
        comida[i] = c;
        qtdComida++;
        
        //Adicionando nova comida na tela
        if(qtdComida < 100){
            cor = corAleatoria();
            while(cor == c.getCor())
                cor = corAleatoria();
            posicaoAleatoria(x, y);
            i = 0;
            while (i <= qtdComida && i<100 ){
                if(x == comida[i].getPosicaoX() && y == comida[i].getPosicaoY()){
                    posicaoAleatoria(x,y);
                    i = 0;
                }
                i++;  
            }
            
            //criando novo ponto na tela
            Ponto d(cor, x, y);
            comida[qtdComida] = d;
        }
    addPontuacao(snake.getTotal() - 1);
    }
}

int Jogo::retira(BITMAP *buffer){
    
    Ponto temp, inicio = snake.getInicio()->getInfo();  
    bool ok;
    int tempoAux = clock();
    //se não colidiu e está na borda
    if(!colidiu(buffer)&&((inicio.getPosicaoX() < TAMANHO_DO_PONTO) || (inicio.getPosicaoX() >= TAMANHO_TELA_X - TAMANHO_DO_PONTO)||
        (inicio.getPosicaoY() < TAMANHO_DO_PONTO) || (inicio.getPosicaoY() >= TAMANHO_TELA_Y - TAMANHO_DO_PONTO))){
        movimenta();//simula o próximo movimento
        snake.retira(temp,ok);
        if(snake.getTotal() == 0)
           return 1;
        while( clock() - tempoAux < getVelocidade());//espera o próximo clock;
        clear_bitmap(buffer);//atualiza os gráficos        
        desenhar(buffer);
        int k = retira(buffer); //retira e guarda pontuação
        return(2*k);//recursivo para testar próximo ponto também
        
    }
    else
        return 1;
}

void Jogo::desenhar(BITMAP *buffer){
    desenharFila(snake, buffer);//desenha a Fila com os pontos
    desenharComida(buffer); //desenhas os pontos na tela
    desenharCenario(buffer); // desenha a borda
    if((snake.getTotal() != 0)&&(snake.getInicio()->getInfo().getPosicaoX() >= 100 || snake.getInicio()->getInfo().getPosicaoY() >= 40)){
        textprintf_ex(buffer, font, 10, 10, makecol(255,255,255), -1, "PONTUACAO:");
        textprintf_ex(buffer, font, 10, 20, makecol(255,255,255), -1, "%10d", getPontuacao());
    }
    blit(buffer, screen, 0, 0, 0, 0, TAMANHO_TELA_X, TAMANHO_TELA_Y); // fixa na tela
}

void Jogo::desenharCenario(BITMAP *buffer){
    int TAM = TAMANHO_DO_PONTO;
    int TAMX = TAMANHO_DO_PONTO*10; //tamanho do retangulo de X
    int TAMY = TAMANHO_DO_PONTO*9; //tamanho do ratangulo de Y
    
    int quebra = TAMANHO_TELA_X - 2*TAM;  //quebra espaco para fazer a borda descartando os 2 pontos extremos
    int quebra_x = quebra/(10*TAM);  //quebra_X divisoes horizontais da borda
    quebra = quebra = TAMANHO_TELA_Y - 2*TAM;
    int quebra_y = quebra/(9*TAM);// quebra_y divisoes verticais da borda
    //linha superior
    for(int i=0; i<quebra_x; i++)
        rectfill(buffer, TAM + i*TAMX, 0, TAM + (i+1)*TAMX, TAM, borda[i]);
    //linha direita
    for(int i=0; i<quebra_y; i++)
        rectfill(buffer, TAMANHO_TELA_X - TAM, TAM + i*TAMY, TAMANHO_TELA_X-1, TAM + (i+1)*TAMY, borda[i+quebra_x]);
    //linha inferior, desenho voltando
    for(int i=quebra_x-1; i>=0; i--)
        rectfill(buffer, TAM + i*TAMX, TAMANHO_TELA_Y - TAM, TAM + (i+1)*TAMX, TAMANHO_TELA_Y-1, borda[(quebra_x - i)+quebra_x+quebra_y]);
    //linha esquerda, desenho subindo       
    for(int i=quebra_y-1; i>=0; i--)
       rectfill(buffer, 0, TAM + i*TAMY, TAM-1, TAM + (i+1)*TAMY, borda[(quebra_y - i) + 2*quebra_x + quebra_y]); 
}

void Jogo::desenharComida(BITMAP *buffer){
    for(int i=0; (i <= qtdComida && i < 100); i++)
        desenharPonto(comida[i], buffer);
}                             

bool Jogo::colidiu(BITMAP *buffer){
    if((getpixel(buffer, snake.getInicio()->getInfo().getPosicaoX()+TAMANHO_DO_PONTO/2, snake.getInicio()->getInfo().getPosicaoY()+ TAMANHO_DO_PONTO/2) != snake.getInicio()->getInfo().getCor())){
        return true; //retorna sempre true se a cor é diferente  
    } else {
        return false;//retorna sempre false se é da mesma cor
    }
}  

bool Jogo::ehCobra(int x, int y){
    
    Node<Ponto> *P ;
    P = snake.getInicio();
    for(int k=0; k<snake.getTotal(); k++){
        for(int i=0; i<TAMANHO_DO_PONTO; i++)
            for(int j=0; j<TAMANHO_DO_PONTO; j++)
                if(P->getInfo().getPosicaoX()+j == x && P->getInfo().getPosicaoY()+i == y){
                    return true;
                }
    P = P->getDireita(); 
    }
    return false;
}

int corAleatoria(){
    int aleatorio = rand();
    
    if(aleatorio % 8 == 0)
        return vermelho;
    if(aleatorio % 8 == 1)
        return laranja;
    if(aleatorio % 8 == 2)
        return amarelo;
    if(aleatorio % 8 == 3)
        return verde;
    if(aleatorio % 8 == 4)
        return anil;
    if(aleatorio % 8 == 5)
        return azul;
    if(aleatorio % 8 == 6)
        return roxo;
    if(aleatorio % 8 == 7)
        return rosa;                                          
}

void Jogo::posicaoAleatoria(int &x, int &y){
    int posicao[2];
    
    x = ((rand() % ((TAMANHO_TELA_X - 2*TAMANHO_DO_PONTO)/ TAMANHO_DO_PONTO)) * TAMANHO_DO_PONTO) + TAMANHO_DO_PONTO;
    y = ((rand() % ((TAMANHO_TELA_Y - 2*TAMANHO_DO_PONTO)/ TAMANHO_DO_PONTO)) * TAMANHO_DO_PONTO) + TAMANHO_DO_PONTO;
    if(ehCobra(x, y))
        posicaoAleatoria(x, y);
}

void desenharPonto(Ponto p, BITMAP *buffer){
     rectfill(buffer, p.getPosicaoX(), p.getPosicaoY(), p.getPosicaoX()+TAMANHO_DO_PONTO-1, p.getPosicaoY()+TAMANHO_DO_PONTO-1, p.getCor());
}

void desenharFila(Fila<Ponto> snake, BITMAP *buffer){
    
    Node<Ponto> *p = snake.getInicio();
    if(snake.getTotal() == 0)
        return; //não desenha se for 0
    else
        desenharPonto(p->getInfo(),buffer);//desenha o primeiro ponto
    //desenha os próximos
    p = p->getDireita();      
    while(p != snake.getInicio()){
        desenharPonto(p->getInfo(),buffer);
        p = p->getDireita();
    }
}

#endif /* _JOGO_H_ */
