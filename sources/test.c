#include "headers/graph.h"
#include "headers/dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned graph_num_nodes;
    printf("Digite o numero de nós do grafo: ");
    scanf("%u", &graph_num_nodes);

    float **graph = initAdjMatrix(graph_num_nodes);

    /* Nomeação dos nós */
    unsigned index = 0;
    node node_pattern; 
    for(; index < graph_num_nodes; index++)
    {
        node_pattern.id = index;
        printf("Digite o nome do nó %u : ", index);
        scanf(" %[^\n]", node_pattern.name);
        addNode(node_pattern);
    }

    printf("\n");

    /* Distribuição de pesos nas arestas */
    index = 0;
    edge edge_pattern;
    for(; index < graph_num_nodes; index++)
    {
        float weight = 0.0;
        unsigned subindex = 0;
        for(; subindex < graph_num_nodes; subindex++)
        {
            if(*(*(graph + index) + subindex) == NO_WEIGHT && 
                *(*(graph + subindex) + index) == NO_WEIGHT &&
                index != subindex)  //Condição de unidirecionalidade do Grafo
            {
                printf("Digite o peso da aresta %s -> %s : ", getNodeById(index)->name, getNodeById(subindex)->name);
                printf("Digite um valor negativo caso não queira adicionar um peso ! \n Peso : ");
                scanf("%f", &weight);

                edge_pattern.start_node = *getNodeById(index);
                edge_pattern.end_node = *getNodeById(subindex);
                edge_pattern.weight = weight >= 0 ? weight : NO_WEIGHT;

                addEdge(edge_pattern, graph);
            } 
        }
        system("clear");
    }


    printAdjMatrix(graph,true);

    /* Caminho mais curto entre dois nós utilizando Dijkstra */

    char opt;
    initDijkstra(graph);
    
    printf("\nBusca de Caminhos de Dijkstra: \n");
    printf("\nDigite X para sair : ");
    scanf(" %c", &opt);

    while(opt != 'x' && opt != 'X')
    {
        /*
            TODO: Verificar se os nós informados para aplicação de dijkstra são válidos (estão no grafo). 
        */
        node orig,dest;
        printf("\nDigite o valor do indice do no de origem: ");
        scanf("%u", &orig.id);
        printf("\nDigite o valor do indice do no de destino: ");
        scanf("%u", &dest.id);
        
        path_info* dijkstra_path = findPath(orig,dest);

        if(dijkstra_path)
        {
            printf("\nCaminho de peso %.2f encontrado por dijkstra: ", dijkstra_path->weight);
            printPath(dijkstra_path->_path, true);
            free(dijkstra_path);
        }

        dijkstra_path = NULL;

        printf("\nBusca de Caminhos de Dijkstra: \n");
        printf("\nDigite X para sair : ");
        scanf(" %c", &opt);
    }

 
    //printf("%s -> %d",getNodeById(5)->name, getNumEdges(*getNodeById(5),graph));
    return 0;
}