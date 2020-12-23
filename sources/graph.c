#include <headers/graph.h>
#include <stdlib.h>
#include <stdio.h>

float** initAdjMatrix(unsigned num_nodes)
{
    float** adjMatrix = (float**)malloc(num_nodes*sizeof(float));
    
    if(!adjMatrix)
    {
        ptrinf("graph.c::initAdjMatrix - 11 : Memory Alocation Error");
        exit(-1);
    }

    unsigned index = 0;
    for(index;index < num_nodes; index++)
    {
        *(adjMatrix + index) = (float*)malloc(num_nodes*sizeof(float));
        
        if(!(*(adjMatrix + index)))
        {
            ptrinf("graph.c::initAdjMatrix - 22 : Memory Alocation Error");
            exit(-1);  
        }
        *(*(adjMatrix + index)) = NO_WEIGHT;
    }
}

size_t initNodeList(unsigned num_nodes)
{

}

size_t addNode(node _node)
{

}

size_t delNode(node _node)
{

}

node getNodeById(unsigned id)
{

}

node getNodeByName(char* name)
{

}

size_t addEdge(edge _edge, float** adjMatrix)
{

}

edge* getEdge(node _node, float** adjMatrix)
{

}

void printAdjMatrix(float** adjMatrix, bool named)
{

}
