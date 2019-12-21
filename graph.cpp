/*
Jonathan Santos Silva RA:759052 Engenharia de Computação UFSCAR
*/
#include <iostream>
#include <vector>
#include <queue>

#define MAX 10100
#define INFINITO 999999999
typedef std::pair <int, int> pii;

typedef struct vertice 
{
    int           rotulo;
    vertice        *prox;
    int           weight;
}Vertice;

typedef struct arestas{
    std::vector<std::vector<int>> arestas;
}Arestas;

typedef struct grafo Grafo;
struct grafo 
{
    Vertice            **adj;
    int         numVertices; 
    int          numArestas; 
};
/*
@BRIEF:     INICIALIZA O GRAFO, COM A QNT DE ARESTAS E VÉRTICES Q ELE POSSUI. 
ALOCA MEMÓRIA PARA LISTA DE ADJACÊNCIA, LISTA ENCADEADA ASSOCIADA COM CADA VÉRTICE DO GRAFO
@PARAM  {int numVertices}   NÚMERO DE VÉRTICES DO GRAFO;
@PARAM   {int numArestas}    NÚMERO DE ARESTAS DO GRAFO;
@return     Retorna o grafo com as informaçoes alocadas;
*/
Grafo *inicializaGrafo(int numVertices, int numArestas)
{
    Grafo *grafo            =                     new Grafo;
    grafo->numVertices      =                   numVertices;
    grafo->numArestas       =                    numArestas;
    grafo->adj              =   new Vertice*[numVertices]();

    for(int iterator = 0; iterator < numVertices; iterator++)
        grafo->adj[iterator] = nullptr;

    return grafo;
}
/*
@BRIF   INSERE A ARESTA, LIGANDO O PONTO INICIAL COM O FINAL, COM O SEU RESPECTIVO PESO
@PARAM   {Grafo *grafo}        estrutura do grafo
@PARAM  {int startEdge}          Inicio da aresta
@param    {int endEdge}             Fim da aresta
@param  {int weight}        Peso entre as arestas
*/
void insertAresta(Grafo *grafo, int startEdge, int endEdge, int weight)
{
    Vertice *newVertice;
    newVertice              =            new Vertice;
    newVertice->weight      =                 weight;
    newVertice->rotulo      =                endEdge;
    newVertice->prox        =  grafo->adj[startEdge];
    grafo->adj[startEdge]   =             newVertice;
}
/*
@brief: Criar o grafo passando como parâmetros a estrutura que o representa e um estrutura de vetor de vetores que represetam todas as arestas do grafo;
@param:                          {Grafo *grafo}                                   Estrutura que representa o grafo;
@param: {std::vector<std::vector<int>> arestas} Vetor de vetores que armazeram as informações de todas as arestas;
*/
void criarGrafo(Grafo *grafo, std::vector<std::vector<int>> arestas)
{
    for(int iterator = 0; iterator < grafo->numArestas; iterator++){
        int startEdge       = arestas[iterator][0];
        int   endEdge       = arestas[iterator][1];
        int    weight       = arestas[iterator][2];

        insertAresta(grafo, startEdge, endEdge, weight);
    }
}
/*
@brief: Printa o grafo no com as relações de cada vértice em ordem crescente || vertice: |relação, peso_da_relação| ||
*/
void printGrafo(Grafo *grafo)
{
    Vertice *vertice;
    for(int iterator = 0; iterator < grafo->numVertices; iterator++){
        std::cout << iterator << ":";
        for(vertice = grafo->adj[iterator]; vertice != nullptr; vertice = vertice->prox)
            std::cout << "|" <<vertice->rotulo << ", " << vertice->weight << "|," ;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*
@Brief: carrega os dados do arquivo na memória
@param:   {char *fileName}                                   nome do arquivo;
@param: {Arestas *arestas}  Estrutura que armazena todas as arestas do grafo;
@param:     {Grafo *grafo}                  Estrutura que representa o grafo;   
*/
void readData(char *fileName, Arestas *arestas, Grafo *grafo)
{ 
    FILE *entrada = fopen(fileName, "r");
    if(entrada == NULL){
        printf("\nNão encontrei o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    fscanf(entrada, "%d" "%d", &grafo->numVertices, &grafo->numArestas);
    int intAux = 0;
    for(int iterator1 = 0; iterator1 < grafo->numArestas; iterator1++){
        std::vector<int> vectorAux;
        for(int iterator2 = 0; iterator2 < 3; iterator2++){
            fscanf(entrada, "%d", &intAux);
            vectorAux.push_back(intAux);
        }
        arestas->arestas.push_back(vectorAux);
    }
}

/*
@Brief: Algoritmo de Dijsktra que encontra o menor caminho de origem até destino no grafo;
@param:       {int origem}  Origem da pesquisa no grafo
@param:      {int destino}  Destino /Objetivo
@param:     {Grafo *grafo}  
@param: {Vertice *vertice}
*/
int Dijskstra(int origem, int destino, Grafo *grafo, Vertice *vertice){
    int distancia[MAX];
    int processado[MAX];
    std::vector<pii> vizinhos[MAX];
    for(int iterator = 0; iterator < grafo->numVertices; iterator ++){
        distancia[iterator] = INFINITO;
        distancia[origem] = 0;
    }

    std::priority_queue<pii, std::vector<pii>, std::greater<pii> > fila;
    fila.push(pii(distancia[origem], origem));

    while(true){
        int davez = -1;
        // int menor = INFINITO;

        while(!fila.empty()){
            int atual = fila.top().second;
            fila.pop();

            if(!processado[atual]){
                davez = atual;
                break;
            }

        }

        if(davez == -1) break;

        processado[davez] = true;
        vertice = grafo->adj[davez];
        
        for(vertice = grafo->adj[davez]; vertice != nullptr; vertice = vertice->prox){
            int dist = vertice->weight;
            int atual = vertice->rotulo;

            if(distancia[atual] > distancia[davez] + dist){
                distancia[atual] = distancia[davez] + dist;
                fila.push(pii(distancia[atual], atual));
            }
        }

    }
 
    return distancia[destino];

}

int main()
{
    char fileName[100];
    scanf("%s", fileName);
    Arestas *arestas = new Arestas;
    Grafo *grafo = new Grafo;
    Vertice *vertice  = new Vertice;

    readData(fileName, arestas, grafo); 
    grafo = inicializaGrafo(grafo->numVertices,grafo->numArestas);
    criarGrafo(grafo,arestas->arestas);
    printGrafo(grafo);
    
    int way = Dijskstra(0, grafo->numVertices - 1, grafo, vertice);
    std::cout << way << std::endl;
}

