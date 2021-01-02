/*
Dijkstra algorithm implementation using recursive function.

Created by : Vitor Manoel.
Contact : https://github.com/Vitor-M

Salvador, Ba.
2021-01-03

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "headers/dijkstra.h"

size_t initDijkstra(float** adjMatrix)
{
    if(graph)
    {
        printf("dijkstra.c::initDijkstra - 21 : the graph is already initialized");
        return 1;
    }
    if(!adjMatrix)
    {
       printf("dijkstra.c::initDijkstra - 26 : the adjacency matrix is NULL");
       return 2; 
    }

    graph = adjMatrix;

    return 0;
}

path_step* getPath(node orig_node, node dest_node)
{

    /*
     - numEdgesAtOrig define quantos vértices podemos acessar diretamente por orig_node.
            Isto é, quantas arestas existem em que orig_node é o nó inicial. 
    */
    unsigned numEdgesAtOrig = getNumEdgesStartInNode(orig_node, graph);


    if(!numEdgesAtOrig)
    {
        //printf("dijkstra.c::getPath - 32 : It's impossible to reach at the destination from the start node %d \n",orig_node.id);
        return NULL;
    }

    /*
     - edges define quais as arestas que começam em orig_node.
    */
    const edge* edges = getEdgesStartInNode(orig_node, graph);
    edge node_edges[numEdgesAtOrig];
    
    unsigned index = 0;
    for(; index < numEdgesAtOrig; index++)
    {
        node_edges[index] = *(edges + index);
    }
    free(edges);
    
    /*
     - dijkstra_path armazenará o caminho mais curto entre orig_node e dest_node dentre todos os caminhos possíveis
        que partem das arestas cujo orig_node é o vértice inicial.
    */
    path_step* dijkstra_path = NULL;  
    index = 0;

    /*
     - Busca um conjunto de arestas que liga cada uma das arestas iniciadas em orig_node ao vértice destino (dest_node).
    */
    for(; index < numEdgesAtOrig; index++)
    {
        /*
         - Alocação de memória para path auxiliar que será comparado com o dijkstra_path afim de se obter o caminho mais curto.
         - Existirá um aux_path para cada uma das arestas que começam em orig_node.
        */
        path_step* aux_path = (path_step*)malloc(sizeof(path_step));
        aux_path->_edge = node_edges[index];
        aux_path->next_edge = NULL;

        //printf("%u : %u -> %u \n",index,aux_path->_edge.start_node.id,aux_path->_edge.end_node.id);

        /*
         - Caso o vértice destino não esteja no final da aresta, será adicionado ao caminho um sub_caminho (conjunto de arestas)
            que será construído a partir do vértice do final da aresta, afim de chegar ao mesmo vértice destino.
        */
        if(aux_path->_edge.end_node.id != dest_node.id)
        {
            aux_path->next_edge = getPath(aux_path->_edge.end_node, dest_node);

        }

        /*
         - Caso o nó destino esteja no final da última aresta do caminho (aux_path)
            então o peso total do caminho é cálculado e comparado com o peso total do caminho mais curto (dijkstra_path)
            que será substituido por aux_path, caso o aux_path possua menor custo (peso).
        */
        if(isNodeInPath(aux_path, dest_node, true))
        { 
            /*
             - Caso dijkstra_path seja nulo, significa que nenhum caminho foi encontrado ainda. Logo aux_path é o menor
             caminho.
            */
            if(!dijkstra_path)
            {
                dijkstra_path = aux_path;

            }else{
            /*
             - Caso dijkstra_path já tenha sido definido e aux_path corresponda à um caminho de menor custo, 
                então dijkstra_path assume este novo caminho (aux_Path).
             - A memória apontada por dijkstra_path já pode ser liberada neste caso, uma vez que o caminho armazenado
                neste endereço já não é mais o menor caminho. 
            */
                if(getPathWeight(aux_path) < getPathWeight(dijkstra_path))
                {
                    free(dijkstra_path);
                    dijkstra_path = aux_path;
                }
            }
        }
        aux_path = NULL;
    }

    return dijkstra_path;
}

float getWeight(node orig_node, node dest_node)
{
    float weight = 0.0;
    path_step* _path = (getPath(orig_node, dest_node));
    while(_path){
        weight += _path->_edge.weight;
        _path = _path->next_edge;
    }

    return weight;
}

float getPathWeight(path_step* _path)
{
    float weight = 0.0;
    while(_path)
    {
        weight += _path->_edge.weight;
        _path = _path->next_edge;
    }
    return weight;
}

path_info* findPath(node orig_node, node dest_node)
{
    path_info* dijkstra_path = (path_info*)malloc(sizeof(path_info));
    
    if(!dijkstra_path)
    {
        printf("dijkstra.c::findPath - 160 : Memory Alocation Error");
        exit(-1);
    }

    dijkstra_path->_path = getPath(orig_node, dest_node);

    if(dijkstra_path->_path)
    {
        dijkstra_path->weight = getPathWeight((*dijkstra_path)._path);
    }

    return dijkstra_path;
}

bool isNodeInPath(path_step* _path, node _node, bool isDest)
{
    while(_path)
    {
        if((isDest && _path->_edge.end_node.id == _node.id) ||
        (!isDest && _path->_edge.start_node.id == _node.id))
        {
            return true;
        }
        _path = _path->next_edge;
    }

    return false;
}

void printPath(path_step* _path, bool named)
{
     while(_path)
    {
        if(named)
        {
            printf("\n%s -> %s (%.2f)",getNodeById(_path->_edge.start_node.id)->name, getNodeById(_path->_edge.end_node.id)->name, _path->_edge.weight);
        }else{
             printf("\n%u -> %u (%.2f)",_path->_edge.start_node.id, _path->_edge.end_node.id, _path->_edge.weight);
        }
        _path = _path->next_edge;
    }
    printf("\n");

    return;
}