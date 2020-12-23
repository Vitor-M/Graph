#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdlib.h>

typedef enum { false, true } bool;

/*
Estrutura de representação de nós.
id corresponde a posição do nó na matriz de adjacências.
nome se refere a identificação denominada pelo usuário. 
*/
typedef struct
{
    unsigned id;    //Indice do nó
    char name[50];  //Nome do nó
} node;

/*
Estrutura de representação de arestas.
Os dois nós que compõe a aresta são definidos como start_node e end_node.
O sentido da aresta é conotado pelo nome dos nós. de modo que uma aresta
sempre começa no start_node e termina no end_node.
weight denota o peso da aresta.
*/
typedef struct
{
    node start_node;    //Nó inicial
    node end_node;      //Nó final
    float weight;   //Peso da aresta
} edge;

const float NO_WEIGHT = -1.0; //Valor default para arestas invalidas (inexistentes/sem peso)

#define MAX_NODES = 1000; //Número máximo de nós permitidos

node** nodelist; //Lista de nós que compõe o grafo

/*
Função : initAdjMatrix
--------------------------
Constrói uma matriz de Adjacência e inicializa todas as arestas sem peso (-1).
A matriz de adjancência é uma matriz de floats simples de 2 dimensões e tamanho
variável.
O parametro num_nodes define o tamanho da matriz de adjacências. Isto é, quantos
nós o grafo em si possui.
A função retorna um ponteiro para a matriz de adjacência.
*/
float** initAdjMatrix(unsigned num_nodes);

/*
Função : initNodeList
--------------------------
Instancia a variável nodelist alocando memória suficiente para armazenar os nós do grafo.
O parametro num_nodes define o número de nós do grafo.
Retorna 0 caso tenha sido possível alocar memória suficiente para todos os nós.
Caso tenha havido problemas de alocação de memória, retorna 1;
*/
size_t initNodeList(unsigned num_nodes);

/*
Função : addNode
--------------------------
Insere um novo nó na lista de nós que compõe o grafo.
Recebe um nó e verifica se a estrutura já não está presente na lista de nós.
A verificação da presença de um nó na lista se dá através da comparação do campo id, dos nós.
Caso o nó já tenha sido inserido, retorna 1.
Se o nó não estiver na lista e ainda assim não seja possível inseri-lo, retorna 2.
Caso o nó não esteja na lista e seja inserido com sucesso, retorna 0.
*/
size_t addNode(node _node);

/*
Função : delNode
--------------------------
Deleta um nó na lista de nós que compõe o grafo.
Recebe um nó e verifica se a estrutura está presente na lista de nós.
A verificação da presença de um nó na lista se dá através da comparação do campo id, dos nós.
Caso o nó mão esteja contido, retorna 1.
Se o nó estiver contido, então ele é removido e em sua posição na lista é atribuído o valor NULL.
A função retorna 0 caso a remoção ocorra com sucesso.
*/
size_t delNode(node _node);

/*
Função : getNode
--------------------------
Verifica se existe um nó no grafo através da comparação do campo id.
Retorna NULL caso o nó não tenha sido encontrado.
Caso o nó esteja presente na lista de nós, retorna a estrutura correspondente ao id informado.
*/
node getNodeById(unsigned id);

/*
Função : getNode
--------------------------
Verifica se existe um nó no grafo através da comparação do campo nome.
Retorna NULL caso o nó não tenha sido encontrado.
Caso o nó esteja presente na lista de nós, retorna a estrutura correspondente ao nome informado.
*/
node getNodeByName(char* name);

/*
Função : getNode
--------------------------
Adiciona uma nova aresta à matriz de adjacências.
Para que uma aresta seja adicionada as condições abaixo devem ser satisfeitas.
    Os dois nós da aresta devem ser diferentes.
    Os dois nós que compôe a aresta devem estar presentes na lista de nós e matriz de adjacências.
    O peso da aresta deve ser um número racional positivo.
    A aresta não pode ter sido adicionada anteriormente.
Retorna 0 caso a aresta tenha sido adicionada
Retorna 1 caso os dois nós da arestas sejam iguais
Retorna 2 caso os nós não estejam defindosna lista de nós ou na matriz de adjacências.
Retorna 3 caso o peso da aresta seja invalido.
Retorna 4 caso a aresta já esteja definida na matriz de adjacências. 
*/
size_t addEdge(edge _edge, float** adjMatrix);

/*
Função : getEdge
--------------------------
Dado um nó e uma matriz de adjacências verifica todas as arestas cuja estrutura faz parte.
Retorna uma lista de arestas contendo todas as arestas cujo nó pertence.
Caso o nó não esteja presente em nenhuma aresta, retorna NULL.
*/
edge* getEdge(node _node, float** adjMatrix);

/*
Função : printAdjMatrix
--------------------------
Exibe, no terminal, a matriz de adjacências com seus nós e arestas.
O parametro named, determina se os nomes dos nós deverão ser exibidos.
Caso named seja false, os nós serão representados apenas pelos seus ids.
*/
void printAdjMatrix(float** adjMatrix, bool named);

#endif