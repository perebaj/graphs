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

void insertAresta(Grafo *grafo, int startEdge, int endEdge, int weight)
{
    Vertice *newVertice;
    newVertice              =            new Vertice;
    newVertice->weight      =                 weight;
    newVertice->rotulo      =                endEdge;
    newVertice->prox        =  grafo->adj[startEdge];
    grafo->adj[startEdge]   =             newVertice;
}

void criarGrafo(Grafo *grafo, std::vector<std::vector<int>> arestas)
{
    for(int iterator = 0; iterator < grafo->numArestas; iterator++){
        int startEdge       = arestas[iterator][0];
        int   endEdge       = arestas[iterator][1];
        int    weight       = arestas[iterator][2];

        insertAresta(grafo, startEdge, endEdge, weight);
    }
}

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

int sizeDe(Vertice *vertice){
    int count = 0;
    for(int iterator = 0; vertice != nullptr; vertice = vertice->prox)
        count ++;
    
    return count;
}

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
        int menor = INFINITO;

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

