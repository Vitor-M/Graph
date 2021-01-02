## Algoritmo de Dijkstra Adaptado

### Representação do Grafo : 
A representação do grafo neste trabalho se dá através duma **matriz de adjacências dinâmica**, implementada em C utilizando ponteiros de ponteiros e alocação dinâmica.  
Para mais informações sobre o grafo e as operações aplicadas diretamente aos seus membros verifique o [escopo](/headers/graph.h) e [código fonte](/sources/graph.c) do grafo.  
  
### Algoritmo de Busca :
O algoritmo de busca de menor caminho entre dois vértices criado para este projeto, é uma **versão adaptada do algorimo de Dijkstra construído pelo autor**.  
A função de busca criada, utiliza da recursividade para realizar o relaxamento dos caminhos possíveis e definir, dentre todos os caminhos possíveis que ligam o vértice origem ao vértice destino, qual o de menor custo.  
Para mais detalhes veja os arquivos [dijkstra.h](/headers/dijkstra.h) e [dijkstra.c](/sources/dijkstra.c).

### Demo : 
Para construir diretamente um teste do projeto - definido em [test.c](/sources/test.c) -, execute a linha de comando abaixo.
  
```
gcc -o GraphApp sources/test.c sources/graph.c sources/dijkstra.c -I.
```
  
ou ainda utilize o makefile para construir todo o projeto, invocando o comando :  
  
```
make all
```
  
Após realizada a compilação do projeto, basta digitar ``` ./GraphApp ```, para executar o teste.  
  
### Atenção :
Caso possua alguma dúvida ou crítica ao projeto, favor entrar em contato através de alguma das opções disponibilizadas na seção abaixo.  
Propositalmente todo o projeto foi desenvolvido a partir do raso conhecimento acerca de grafos e algoritmos de busca. Este foi um desafio que me impus.  
Embora tenha denominado o algoritmo de busca como uma versão modificada do algoritmo de Dijkstra, assumo que ainda não possuo conhecimento suficiente para saber se assim posso denominá-lo. Peço encarecidamente que, caso o leitor possua conhecimento e domínio no tema, me auxilie no processo de aprendizado, informado se a implementação deste repositório pode ser denominado como o foi feito (Algoritmo de Dijkstra Adaptado).  
De qualquer modo, espero que o conteúdo deste repositório possa ser útil para você de alguma forma.
Agradeço a todos por visitarem e avaliarem meu trabalho.  
  
### Sobre o autor :
Projeto desenvolvido por Vitor Manoel.  
e-mail: vitorm2000.si@gmail.com.  
WhatsApp: +55 71 98133-7404  