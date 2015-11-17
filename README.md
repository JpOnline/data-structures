# data-structures
Data Structures class at UFSCar.

# projects/Color Snake

Color Snake v1.0 é uma versão modificada do clássico jogo Snake. O jogador
controla uma cobra capaz de “comer” bloquinhos e, cada bloquinho comido por ela é
acrescentado em seu rabo, aumentando assim o seu tamanho. O objetivo do jogo,
semelhante ao Snake original, é fazer a maior pontuação possível. A diferença do Color
Snake em relação ao clássico é que as cores influenciam durante o jogo, fazendo com
que seja possível diminuir o tamanho da cobra, atravessar paredes ou impossibilitando a
captura de novos bloquinhos.

## Sobre o jogo

### Jogabilidade:

O jogador direciona o movimento a cobra utilizando as setas
direcionais do teclado ou as teclas W, A, S, D. Para “comer” um bloquinho basta
passar com a cabeça da cobra sobre um bloquinho avulso no mapa, desde que
este não seja da mesma cor da cabeça. A cobra pode diminuir o tamanho seu
tamanho ao passar por uma parede cuja cor seja a mesma de sua cabeça.

### Término de jogo:

Há 3 formas de terminar o jogo:
* Tentando atravessar uma parede que não seja da mesma cor
da cabeça da cobra;
* Colidindo a cabeça da cobra com seu corpo;
* Fazendo a cobra diminuir de tamanho até que desapareça,
somando 30% dos pontos já conseguidos até então a
pontuação final.

### Desenvolvimento do jogo
O jogo tem como estrutura de dados uma fila duplamente encadeada, cujo
conceito de FIFO, first in first out, é empregado na lógica da cobra do color snake. A ideia
de “diminuir” a cobra foi justamente para adequar o jogo clássico à essa estrutura. Alinguagem de programação utilizada foi o C++, utilizando a biblioteca ALLEGRO 4.2.2
para a interface gráfica.

A classe Node, ilustrada abaixo, é um template que contém a informação do nó e
os endereços de memória dos nós anterior e posterior. No nosso jogo, essa classe é
responsável por guardar a cor e posição de cada bloquinho.

![imagem da estrutura de nó][nodeImg]

A classe Fila tem como atributos dois ponteiros do tipo Node, sendo um para o
início e um para o final da fila, além de uma variável de controle de tamanho da fila
chamada Total. Tem como métodos:
* cria() do tipo boolean;
* nsere(T do tipo elemento, variável do tipo boolean por referência indicando
sucesso ou não da operação);
* remove(T do tipo elemento por referência, variável do tipo boolean
indicando sucesso ou não da operação);
* vazia() do tipo boolean, que verifica o tamanho da fila a partir do atributo
Total.

![imagem contendo fila de nós][nodeQueue]

Implementadas as TADs, prosseguimos com a estrutura do jogo. Foi criada uma
classe Ponto, onde as informações de cor, posição e direção dos bloquinhos sãoarmazenadas. Há também uma classe menu, que armazena a maior pontuação do
jogador enquanto o jogo estiver rodando; o nível de dificuldade, que “seta” a velocidade
inicial da cobra; além de permitir que o jogo seja reiniciado, uma vez que, quando o jogo
termina, ele retorna ao menu.

Na classe Jogo estão contidas as manipulações das classes Fila, Node e Pontos,
ou seja, nessa classe estão contidas as regras do jogo, funcionalidade, entre outros.
Podemos destacar:

* Sistema de pontuação: quando o jogador aumenta a cobra, ele ganha um
ponto para cada ponto da cobra; quando a diminui, o jogador ganha dois
elevado ao número de pontos que ele retirou ao mesmo tempo;

![telas do jogo explicando pontuação][screenshots]

* O método colidir, que verifica se a cobra colidiu com algum ponto ou borda
do mapa, ou até consigo;
* O método comer, que é responsável por acrescentar o ponto do mapa à
cobra caso ela “coma” o bloquinho;
* O método retira, que é responsável por remover um ponto da cobra quando
ela passa pela borda do mapa;
* O método corAleatória, responsável por gerar bloquinhos de cores
aleatórias, na inicialização da cobra, nos bloquinhos que aparecem
dispersos no mapa e nas bordas.

A interface gráfica foi a parte final do desenvolvimento. Como a biblioteca utilizada
foi a Allegro, foi necessário criar novos métodos que fizessem uso das classes já
mencionadas para mostrar a estrutura de forma interativa. Dentre eles, podemos citar os
métodos desenharComida, método que desenha os bloquinhos aleatórios do mapa,
desenharFila, que desenha a cobra, desenharCenario, cujo nome é autoexplicativo, entre
outros.

Para finalizar, mostraremos abaixo alguns screenshots do jogo, sendo o primeiro a
da interface, e outra do jogo em andamento:

![tela do final do jogo][endGame]

![tela do menu inicial][startGame]

![tela do jogo][middleGame]

Bom jogo!

<!-- images -->
[nodeImg]: https://raw.githubusercontent.com/JpOnline/data-structures/master/projects/Color%20Snake/img/Documentacao/node.png
[nodeQueue]: https://raw.githubusercontent.com/JpOnline/data-structures/master/projects/Color%20Snake/img/Documentacao/nodeQueue.png
[screenshots]: https://raw.githubusercontent.com/JpOnline/data-structures/master/projects/Color%20Snake/img/Documentacao/screenshots.png
[endGame]: https://raw.githubusercontent.com/JpOnline/data-structures/master/projects/Color%20Snake/img/Documentacao/endGame.png
[startGame]: https://raw.githubusercontent.com/JpOnline/data-structures/master/projects/Color%20Snake/img/Documentacao/startGame.png
[middleGame]: https://raw.githubusercontent.com/JpOnline/data-structures/master/projects/Color%20Snake/img/Documentacao/middleGame.png
