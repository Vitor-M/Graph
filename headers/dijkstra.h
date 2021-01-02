/*
Dijkstra algorithm implementation using recursive function.

Created by : Vitor Manoel.
Contact : https://github.com/Vitor-M

Salvador, Ba.
2021-01-03

*/


#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <stdlib.h>
#include "graph.h"

//Neste trabalho os vértices de um grafo foram denominados "nós"

/*
Estrutura de representação de um caminho entre dois nós.
_edge contêm uma aresta presente no path.
next_edge aponta para o próximo segmento (aresta) que compõe o caminho. 
*/
typedef struct path_step
{
    edge _edge;
    struct path_step* next_edge;
}path_step;

/*
Estrutura de representação de um caminho completo dois nós.
_path faz representa as arestas que compõe o caminho entre dois nós.
weight é o peso correspondente a soma dos pesos das arestas que compõe o caminho. 
*/
typedef struct
{
    path_step* _path;
    float weight;
}path_info;


float** graph;   //Matriz de adjacências (grafo) contendo os nós e seus pesos.

/*
Função : initDijkstra
--------------------------
- Inicializa o grafo (graph) utilizado pelas operações de busca de cálculo de pesos dos caminhos entre dois nós.

- Recebe uma matriz de adjacências, já preenchida com arestas e pesos e então atribui esta matriz à variável graph.

- Caso a variável graph já tenha sido inicializada, retorna 1.
- Caso a matriz de adjacências seja nula, retorna 2.
- Retorna 0, caso seja possível inicializar o grafo.
*/
size_t initDijkstra(float** adjMatrix);

/*
Função : getPath
--------------------------
- Calcula todos os caminhos possíveis entre os nós de origem (orig_node) e destino (dest_node).

- Seleciona o caminho de menor custo a partir do calculo dos custos de cada um dos caminhos possíveis
    partindo da origem.

- retorna o caminho de menor custo.
- NULL é retornado caso não tenha sido encontrado um caminho válido.
*/
path_step* getPath(node orig_node, node dest_node);

/*
Função : getWeight
--------------------------
- A partir de dois nós recebidos um de origem (orig_node) e um de destino (dest_node)

- calcula o peso do caminho mínimo que ligam os dois nós.

- retorna o peso correspondente ao caminho de menor de distância entre os nós.
- retorna NULL caso não exista um caminho que liguem os dois vértices (nós).
*/
float getWeight(node orig_node, node dest_node);

/*
Função : getPathWeight
--------------------------
- A partir de conjunto de arestas recebido (path), calcula o peso de todas as arestas que compõe o caminho.

- retorna o peso correspondente ao caminho do path entre dois nós.
- retorna 0 caso não exista um caminho que liguem os dois vértices (nós).

*/
float getPathWeight(path_step* _path);

/*
Função : findPath
--------------------------
- A partir de dois nós recebidos um de origem (orig_node) e um de destino (dest_node)
    calcula o menor caminho e peso das arestas que ligam os dois nós.

- retorna o peso e o caminho de menor distânca correspondente, entre os nós.

*/
path_info* findPath(node orig_node, node dest_node);

/*
Função : isNodeInEdges
--------------------------
- Dado um nó, verifica se ele está contido em uma lista de arestas.

- Se isDest for true, então verifica se está contido no final de alguma aresta,
- caso contrário verifica se o nó está presente no inicio de alguma aresta.

- Retorna true caso alguma referência ao nó tenha sido encontrado.
*/
bool isNodeInPath(path_step* _path, node _node, bool isDest);

/*
Função : printAdjMatrix
--------------------------
- Exibe, no terminal, a sequência de arestas de um caminho entre dois nós.

- O parâmetro named, determina se os nomes dos nós deverão ser exibidos.
- Caso named seja false, os nós serão representados apenas pelos seus ids.
*/
void printPath(path_step* _path, bool named);

#endif