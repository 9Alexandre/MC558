/* O código recebe um grafo poderado nao orientado e um conjunto de pares de vertices.
Para cada par de vertices, e buscado todos dos caminhos entre os dois, e para cada caminho
encontrado, e buscado o valor do maior peso entres as arestas do caminho. Por fim, com o
cojunto de valores maximo de pesos de cada caminho, o código devolve o menor de valor
desse conjunto.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct grafo {
    int numVertices;
    int **matriz;
} Grafo;

void criaGrafo(Grafo *grafo, int n);
void destroi(Grafo *grafo);
void inserirAresta(Grafo *grafo, int u, int v, int peso);
void pesoMin(int *minMax, int peso);
void pesoMax(Grafo *grafo, int *caminho, int *caminhoIdx, int *minMax);
void buscaCaminhos(Grafo *grafo, int s, int t, int *visitados, int *caminho, int *caminhoIdx, int *minMax);

int main(){

    int numVertices, numArestas;
    Grafo grafo;
    int u, v, peso;
    int areas, parAreas[50][2];
    int *caminho, caminhoIdx=0, *visitados, minMax=1000000;
    int i;

    /* Leitura do quantidade de vertices e de arestas do grafo */
    scanf("%d", &numVertices);
    scanf("%d", &numArestas);

    criaGrafo(&grafo, numVertices);

    /* Adiciona as arestas */
    for(i=0; i<numArestas; i++){
        scanf("%d %d %d", &u, &v, &peso);
        inserirAresta(&grafo, u, v, peso);
    }

   scanf("%d", &areas);

    for(i=0; i<areas; i++){
        scanf("%d %d", &u, &v);
        parAreas[i][0] = u;
        parAreas[i][1] = v;
	}

    for(i=0; i<areas; i++){

        caminho = calloc(numVertices, sizeof(int));
        visitados = calloc(numVertices, sizeof(int));

        u = parAreas[i][0];
        v = parAreas[i][1];
        buscaCaminhos(&grafo, u, v, visitados, caminho, &caminhoIdx, &minMax);

        printf("%d\n", minMax);

        caminhoIdx=0;
        minMax=1000000;
        free(caminho);
        free(visitados);
    }

    destroi(&grafo);

    return 0;
}

void criaGrafo(Grafo *grafo, int n){

    int i;

    grafo->numVertices = n;
    grafo->matriz = calloc (n, sizeof(int*));
    grafo->matriz[0] = NULL;
    for (i=1; i<n; i++){
        grafo->matriz[i] = calloc (i, sizeof(int));
    }
}

void destroi(Grafo *grafo){

    int i;

    for(i=1; i<grafo->numVertices; i++){
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
}

void inserirAresta(Grafo *grafo, int u, int v, int peso){

    if(u > v){
        grafo->matriz[u][v] = peso;
    }
    else{
       grafo->matriz[v][u] = peso;
    }
}

void pesoMin(int *minMax, int peso){

    if(peso < *minMax){
        *minMax = peso;
    }
}

void pesoMax(Grafo *grafo, int *caminho, int *caminhoIdx, int *minMax){

	int i;
	int u, v;
	int maiorPeso=0;

	for(i=0; i<*caminhoIdx-1; i++){
		u = caminho[i];
		v = caminho[i+1];

        if(u > v){
            if(grafo->matriz[u][v] > maiorPeso){
                maiorPeso = grafo->matriz[u][v];
            }
        }
        else{
            if(grafo->matriz[v][u] > maiorPeso){
                maiorPeso = grafo->matriz[v][u];
            }
        }
	}

    pesoMin(minMax, maiorPeso);
}

void buscaCaminhos(Grafo *grafo, int s, int t, int *visitados, int *caminho, int *caminhoIdx, int *minMax){

    int i;

    visitados[s] = 1;
    caminho[*caminhoIdx] = s;
  	(*caminhoIdx)++;

    if(s == t){
        pesoMax(grafo, caminho, caminhoIdx, minMax);
    }
    else{
        for(i=0; i<grafo->numVertices; ++i){
            if(visitados[i] == 0){
                if(s > i){
                    if(grafo->matriz[s][i] != 0){
                        buscaCaminhos(grafo, i, t, visitados, caminho, caminhoIdx, minMax);
                    }
                }else{
                    if(grafo->matriz[i][s] != 0){
                        buscaCaminhos(grafo, i, t, visitados, caminho, caminhoIdx, minMax);
                    }
                }
			}
        }
    }

	(*caminhoIdx)--;
    visitados[s] = 0;
}
