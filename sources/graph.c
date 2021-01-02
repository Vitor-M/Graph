/*
Graph implementation using adjacency matrix.

Created by : Vitor Manoel.
Contact : https://github.com/Vitor-M

Salvador, Ba.
2021-01-03

*/

#include "headers/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
- Variável de armazenamento do número de vertices do grafo.
*/
unsigned NUM_NODES = 0;


float** initAdjMatrix(unsigned num_nodes)
{
    if(num_nodes > MAX_NODES)
    {
        printf("graph.c::initAdjMatrix - 27 : Invalid Node Quantity - Number Nodes Is Over Limit");
        return NULL;
    }

    NUM_NODES = num_nodes;

    /* 
     - Alocação de mémoria para uma matriz de floats de duas dimensões.
     - O valor de uma célula da matriz corresponde ao peso da aresta que une o nó da linha ao da coluna da célula.
    
     - adjMatrix é um ponteiro para ponteiro de float que aponta para o primeiro ponteiro de float 
        de um arranjo de ponteiros de floats - que representam as colunas da matriz de ajdacências.

    */
    float** adjMatrix = (float**)malloc(NUM_NODES*sizeof(float*));
    
    if(!adjMatrix)
    {
        printf("graph.c::initAdjMatrix - 45 : Memory Alocation Error");
        exit(-1);
    }

    //Inicialização das arestas da matriz de adjacências.
    /*
     - Para cada iteração do laço será alocado mémoria para serem apontadas por cada um dos ponteiros que adjMatrix aponta.
     - Os espaços de mémoria alocadas correspondem à um arranjo de floats e representam as linhas da matriz de adjacências.
     - Assim cada coluna (ponteiros para ponteiros de floats) aponta para NUM_NODES linhas (ponteiro para floats).
    */
    
    unsigned index = 0;
    for(; index < NUM_NODES; index++)
    {
        *(adjMatrix + index) = (float*)malloc(NUM_NODES*sizeof(float));
        
        if(!(*(adjMatrix + index)))
        {
            printf("graph.c::initAdjMatrix - 63 : Memory Alocation Error");
            exit(-1);  
        }

        float* line = *(adjMatrix + index);
        unsigned sub_index = 0;
        for(; sub_index < NUM_NODES; sub_index++)
        {
            *(line + sub_index) = NO_WEIGHT;
        }
    }

    //Iniciliaza a lista de identificação dos vértices.
    /*
     - A lista de vértices (nós), não é necessária para se atingir o propósito geral do trabalho,
        ela é utilizada somente para armazenar o apelido dos nós, fornecido pelo usuário, uma vez que
        a matriz de adjacências faz referência apenas ao número id destes vertices.
    */
    initNodeList();

    return adjMatrix;
}

size_t initNodeList()
{
    /*
        TODO: Implementar lista encadeada, para que não seja necessário conhecer o número de nós. 
    */

    //Alocação de memória para armazenamento de todas as estrutura de representação dos vértices (NUM_NODES) do grafo.
    nodelist = (node**)malloc(NUM_NODES *sizeof(node*));

    if(!nodelist)
    {
        printf("graph.c::initNodeList - 97 : Memory Alocation Error");
        return(1);  
    }

    /*
     - Os elementos da lista de nós não apontam para nenhum vértice, uma vez que neste momento
        a matriz de adjacências ainda não foi preenchida.
    */
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

   /*
     - Verifica se o nó já está presente na lista. Isto é feito analisando se o ponteiro que aponta para o nó
        de indice correspondente ao parâmetro _node está nulo.
   */
    if(!(*(nodelist + _node.id)))
    {
        (*(nodelist + _node.id)) = (node*)malloc(sizeof(node));
        *(*(nodelist + _node.id)) = _node;
        return 0;
    }
    if((*(nodelist + _node.id))->id == _node.id )
    {
        printf("graph.c::addNode - 132 : the node is already in list");
        return 1;
    }
    return 2;
}

size_t delNode(node _node)
{
    /*
     - Verifica se o nó já está presente na lista. Isto é feito analisando se o ponteiro que aponta para o nó
        de indice correspondente ao parâmetro _node não está nulo.
     - E se o nó armazenado no ponteiro é de fato o mesmo nó passado por parâmetro (_node).
    */

    if(*(nodelist + _node.id) && (*(nodelist + _node.id))->id == _node.id)
    {
        free(nodelist + _node.id);
        *(nodelist + _node.id) = NULL;
        return 0;
    }
    printf("graph.c::delNode - 152 : the node isn't into the list");
    return 1;
}

node* getNodeById(unsigned _id)
{   
    /*
     - Verifica se o nó já está presente na lista. Isto é feito analisando se o ponteiro que aponta para o nó
        de indice correspondente ao parâmetro _node não está nulo.
     - E se o nó armazenado no ponteiro contêm  o mesmo id do id passado por parâmetro.
    */
    if(_id < NUM_NODES && *(nodelist + _id) && (*(nodelist + _id))->id == _id)
    {
        return *(nodelist + _id);
    }

    return NULL;
}

node* getNodeByName(char* _name)
{
        /*
     - Verifica se o nó já está presente na lista. Isto é feito analisando se há algum ponteiro que aponta para o nó
        de nome correspondente ao nome do parâmetro _node está nulo.
     - E se o nó armazenado no ponteiro contêm  o mesmo nome do nome passado por parâmetro.
    */
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
    /*
    TODO : tornar opcional a construção de grafo com arestas não direcionais e com laços..
    */

   /*
    - Verifica as condições de direcionalide e ciclicidade.
    - A primeira condição verifica se a aresta não é um laço, ou seja se os dois nós que a compõe não são iguais.
    - As outras duas condições verifica a direcionalidade da aresta. Isto é, verificam se já existe um aresta composta
        pelos mesmos dois nós.
   */
    if(_edge.start_node.id == _edge.end_node.id ||
        (*(*(adjMatrix + _edge.start_node.id) + _edge.end_node.id) != NO_WEIGHT && 
        *(*(adjMatrix + _edge.end_node.id) + _edge.start_node.id) != NO_WEIGHT))
    {
        return 1;
    }
    
    /*
     - Verifica se os dois nós da aresta estão definidos na lista de arestas.
    */
    if(!getNodeById(_edge.start_node.id) || !getNodeById(_edge.end_node.id))
    {
        return 2;
    }

    /*
     - Verifica se o peso da aresta é válido.
    */
    if(_edge.weight < 0.0 || _edge.weight == NO_WEIGHT)
    {
        return 3;
    }
    /*
     - Verifica se a aresta já não foi definida.
        Isto é, se já não foi atribuido um peso a célula correspondente a aresta na matriz de adjacências.
    */
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
        printf("graph.c::getNumEdges - 241 : the node isn't in the graph");
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

size_t getNumEdgesStartInNode(node _node, float** adjMatrix)
{
    if(!getNodeById(_node.id))
    {
        printf("graph.c::getNumEdgesStartInNode - 284 : the node isn't in the graph");
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
 

   return n_edges; 
}

edge* getEdges(node _node, float** adjMatrix)
{
    if(!getNodeById(_node.id))
    {
        printf("graph.c::getEdges - 313 : the node isn't in the graph");
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

edge* getEdgesStartInNode(node _node, float** adjMatrix)
{
    if(!getNodeById(_node.id))
    {
        printf("graph.c::getEdgesStartInNode - 375 : the node isn't in the graph");
        return NULL;
    }

    size_t node_edges = getNumEdges(_node,adjMatrix);

    edge* edges = (edge*)malloc(node_edges *sizeof(node));
    
    if(!edges)
    {
        printf("graph.c::getEdgesStartInNode - 385 : Memory Alocation Error");
        exit(-1);
    }

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
