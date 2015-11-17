/*Estrutura Fila duplamente encadeada com alocacao dinâmica utilizando tamplate para generalizar o tipo da Fila*/
#ifndef _FILA_H_
#define _FILA_H_

#include "Node.h"

template <class T>
class Fila{
      private:
        Node<T> *inicio; //ponteiro para o inicio da Fila
        Node<T> *fim; //ponteiro para o fim da fila
        int total; // número de elementos da fila
      public:
        Fila();
        bool vazia(){if(total == 0) return true; else return false;}
        void insere(T, bool&); //insere elemento no fim da fila
        void retira(T&, bool&); //retira elemento do começo da fila
        Node<T>* getInicio(){ return inicio;} 
        Node<T>* getFim(){ return fim;}
        int getTotal(){ return total;}
};

template <class T>
Fila<T>::Fila(){
    inicio = fim = NULL;
    total = 0;
}

template <class T>
void Fila<T>::insere(T elemento, bool &ok){
     Node<T>* aux;
     Node<T>* newNode;
     
     newNode = new Node<T>;
     
     if(vazia()){
         newNode->setInfo(elemento);     //info(newNode) = elemento
         inicio = newNode;                           
         fim = newNode;                              
     }
     else{
         newNode->setInfo(elemento);     //info(newNode) = elemento
         aux = fim;                 
         fim = newNode;                         
         aux->setDireita(fim);           //dir(aux) = fim
         fim->setEsquerda(aux);          //esq(fim) = aux
         inicio->setEsquerda(fim);       //esq(inicio) = fim
         fim->setDireita(inicio);        //dir(fim) = inicio
     }
     
     total++;
     
     ok = true;
}

template <class T>
void Fila<T>::retira(T& elemento, bool &ok){
    Node<T> *antigoInicio;
    
    if(!vazia()){
        antigoInicio = inicio;
        if(inicio == fim)
            inicio = fim = NULL;
        else{
            inicio = inicio->getDireita(); //inicio = dir(inicio)
            inicio->setEsquerda(fim);      //esq(inicio) = fim
            fim->setDireita(inicio);       //dir(fim) = inicio
        }
        elemento = antigoInicio->getInfo();  //elemento = info(antigoInicio)
        delete antigoInicio;                //freeNode(antigoInicio)
        total--;
        
        ok = true;
    }
    else
        ok = false;
}

#endif /* _FILA_H_ */
