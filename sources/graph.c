#include "headers/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned NUM_NODES = 0;

float** initAdjMatrix(unsigned num_nodes)
{
    if(num_nodes > MAX_NODES)
    {
        return NULL;
    }

    NUM_NODES = num_nodes;

    float** adjMatrix = (float**)malloc(NUM_NODES*sizeof(float*));
    
    if(!adjMatrix)
    {
        printf("graph.c::initAdjMatrix - 25 : Memory Alocation Error");
        exit(-1);
    }

    unsigned index = 0;
    for(; index < NUM_NODES; index++)
    {
        *(adjMatrix + index) = (float*)malloc(NUM_NODES*sizeof(float));
        
        if(!(*(adjMatrix + index)))
        {
            printf("graph.c::initAdjMatrix - 36 : Memory Alocation Error");
            exit(-1);  
        }

        float* line = *(adjMatrix + index);
        unsigned sub_index = 0;
        for(; sub_index < NUM_NODES; sub_index++)
        {
            *(line + sub_index) = NO_WEIGHT;
        }
    }

    initNodeList();

    return adjMatrix;
}

size_t initNodeList()
{
    /*
        TODO: Implementar lista encadeada, para que não seja necessário conhecer o número de nós. 

    */
    nodelist = (node**)malloc(NUM_NODES *sizeof(node*));

    if(!nodelist)
    {
        printf("graph.c::initNodeList - 63 : Memory Alocation Error");
        return(1);  
    }

    unsigned index = 0;
    for(; index < NUM_NODES; index++)
    {
        *(nodelist + index) = NULL;
    }

    return 0;
}

size_t addNode(node _node)
{
    /*
    TODO : Verificar se já existe um nó com mesmo nome na estrutura.
    */
    if(!(*(nodelist + _node.id)))
    {
        (*(nodelist + _node.id)) = (node*)malloc(NUM_NODES *sizeof(node));
        *(*(nodelist + _node.id)) = _node;
        return 0;
    }
    if((*(nodelist + _node.id))->id == _node.id )
    {
        printf("graph.c::addNode - 89 : the node is already in list");
        return 1;
    }
    return 2;
}

size_t delNode(node _node)
{
    if(*(nodelist + _node.id) && (*(nodelist + _node.id))->id == _node.id)
    {
        free(nodelist + _node.id);  //teste de função free()
        *(nodelist + _node.id) = NULL;
        return 0;
    }
    printf("graph.c::addNode - 103 : the node isn't into the list");
    return 1;
}

node* getNodeById(unsigned _id)
{   
    if(_id < NUM_NODES && *(nodelist + _id) && (*(nodelist + _id))->id == _id)
    {
        return *(nodelist + _id);
    }

    return NULL;
}

node* getNodeByName(char* _name)
{
    unsigned index = 0;
    for(; index < NUM_NODES; index++)
    {
        if(*(nodelist + index) && !strcmp((*(nodelist + index))->name,_name))
        {
            return *(nodelist + index);
        }
    }

    return NULL;
}

size_t addEdge(edge _edge, float** adjMatrix)
{
    if(_edge.start_node.id == _edge.end_node.id ||
        (*(*(adjMatrix + _edge.start_node.id) + _edge.end_node.id) != NO_WEIGHT && 
        *(*(adjMatrix + _edge.end_node.id) + _edge.start_node.id) != NO_WEIGHT))
    {
        return 1;
    }
    if(!getNodeById(_edge.start_node.id) || !getNodeById(_edge.end_node.id))
    {
        return 2;
    }
    if(_edge.weight < 0.0 || _edge.weight == NO_WEIGHT)
    {
        return 3;
    }
    if(*(*(adjMatrix + _edge.start_node.id) + _edge.end_node.id) != NO_WEIGHT)
    {
        return 4;
    }

    *(*(adjMatrix + _edge.start_node.id) + _edge.end_node.id) = _edge.weight;
    return 0;
}

size_t getNumEdges(node _node, float** adjMatrix)
{
    if(!getNodeById(_node.id))
    {
        printf("graph.c::getEdge - 158 : the node isn't in the graph");
    }

    unsigned n_edges = 0;

    //Procurando arestas que começam em _node
    /*
        A verificação da participação do nó em uma aresta se dá através
        da varredura da linha em que o nó está definido (*(adjMatrix + _node.id)). Um laço percorre
        todas as colunas (index) que cruzam com essa linha em busca de valores
        de peso válidos.
    */
    float* line_ref= *(adjMatrix + _node.id); 
    unsigned index = 0;
    for(; index < NUM_NODES; index++)
    {
        if(*(line_ref + index) != NO_WEIGHT)
            n_edges++;
            
    }

    //Procurando arestas que terminam em _node
    /*
        A verificação da participação do nó em uma aresta se dá através
        da varredura da coluna em que o nó está definido (*(*(adjMatrix + index) + _node.id)). Um laço percorre
        todas as lienhas (*(adjMatrix + index)) que cruzam com essa linha em busca de valores
        de peso válidos.
    */
    index = 0;
    for(; index < NUM_NODES; index++)
    {
        float* column_ref = *(adjMatrix + index);
        if(*(column_ref + _node.id) != NO_WEIGHT)
            n_edges++;
    }

    return n_edges;
}

edge* getEdge(node _node, float** adjMatrix)
{
    if(!getNodeById(_node.id))
    {
        printf("graph.c::getEdge - 201 : the node isn't in the graph");
    }

    size_t node_edges = getNumEdges(_node,adjMatrix);

    edge* edges = (edge*)malloc(node_edges *sizeof(node));

    unsigned edge_id = 0;

    //Procurando arestas que começam em _node
    /*
        A verificação da participação do nó em uma aresta se dá através
        da varredura da linha em que o nó está definido (*(adjMatrix + _node.id)). Um laço percorre
        todas as colunas (index) que cruzam com essa linha em busca de valores
        de peso válidos.
    */
    float* line_ref= *(adjMatrix + _node.id); 
    unsigned index = 0;
    for(; index < NUM_NODES; index++)
    {
        if(*(line_ref + index) != NO_WEIGHT)
        {
            (edges + edge_id)->start_node = _node;
            (edges + edge_id)->end_node = *(getNodeById(index));
            (edges + edge_id)->weight = (*(line_ref + index));
            edge_id++;
        }
    }

    //Procurando arestas que terminam em _node
    /*
        A verificação da participação do nó em uma aresta se dá através
        da varredura da coluna em que o nó está definido (*(*(adjMatrix + index) + _node.id)). Um laço percorre
        todas as lienhas (*(adjMatrix + index)) que cruzam com essa linha em busca de valores
        de peso válidos.
    */
    index = 0;
    for(; index < NUM_NODES; index++)
    {
        float* column_ref = *(adjMatrix + index);
        if(*(column_ref + _node.id) != NO_WEIGHT)
        {
            (edges + edge_id)->start_node = *(getNodeById(index));
            (edges + edge_id)->end_node = _node;
            (edges + edge_id)->weight = (*(line_ref + index));
            edge_id++;
        }
           
    }

    if (edge_id == 0 || edge_id > node_edges)
    {
        return NULL;
    }
    
    return edges;
}

void printAdjMatrix(float** adjMatrix, bool named)
{
    unsigned index = 0;
    printf("\n\t\t\tGrafos\t\t\t\n");
    for(; index < NUM_NODES; index++)
    {
        if(named)
        {
        printf("\t%s",getNodeById(index)->name);
        }else{
        printf("\t%d",index);
        }
        
    }
    printf("\n\n\n");

    index = 0;
    for(; index < NUM_NODES; index++)
    {
        if(named)
        {
        printf("%s",getNodeById(index)->name);
        }else{
        printf("%d",index);
        }

        float* line = *(adjMatrix + index);

        unsigned sub_index = 0;
        for(; sub_index < NUM_NODES; sub_index++)
        {
            printf("\t%.2f",*(line  + sub_index));
        }

        printf("\n");
    }
}
