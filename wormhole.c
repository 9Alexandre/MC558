#include <stdio.h>
#include <stdlib.h>

#define INF 99999

typedef struct No{
	int vertice;
    int peso;
	struct No* prox;
}no;

void inserirAresta(no *grafo, int a, int b, int peso){

    no *aux;
    no *tmp;

    aux = (no*) malloc((int)sizeof(no));
    aux->vertice = b;
    aux->peso = peso;
    aux->prox = NULL;

    grafo[a].vertice++;
    if(grafo[a].prox == NULL){
        grafo[a].prox = aux;
    }
    else{
        tmp = grafo[a].prox;
        if(tmp->vertice > b){
            aux->prox = tmp;
            grafo[a].prox = aux;
        }
        else if(tmp->prox == NULL){
            aux->prox = tmp->prox;
            tmp->prox = aux;
        }
        else{
            while((tmp->prox != NULL) && (tmp->prox->vertice < b))
            tmp = tmp->prox;
            aux->prox = tmp->prox;
            tmp->prox = aux;
        }
    }
}

int bellmanFord(no *grafo, int n, int s){

    int distacia[n];
    int u, v, w;
    int i;
    no *aux;

    for(i=0; i<n; i++){
      distacia[i] = INF;
    }

    distacia[s] = 0;

    /* Relaxamento das arestas */
    for(i=0; i<n; i++){
        aux = grafo[i].prox;
        while (aux != NULL){
            u = i;
            v = aux->vertice;
            w  = aux->peso;

            if(distacia[u] != INF && distacia[v] > distacia[u] + w){
                distacia[v] = distacia[u] + w;
            }
            	aux = aux->prox;
        }
    }

    /* Busca por cilco negativo */
    for(i=0; i<n; i++){
        aux = grafo[i].prox;
        while(aux != NULL){
            u = i;
            v = aux->vertice;
            w  = aux->peso;

            if(distacia[u] != INF && distacia[v] > distacia[u] + w){
                if(distacia[u] != INF && distacia[v] > distacia[u] + w) {
                    return 1;
                }
            }
                aux = aux->prox;
        }
    }

    return 0;
}

int main(){

    int numVertices, numArestas;
    int u, v, peso;
    int i;
	no *grafo, *aux, *tmp;

    /* Leitura do quantidade de vertices e de arestas do grafo */
    scanf("%d %d", &numVertices,  &numArestas);

    grafo = malloc((numVertices) * sizeof(no));

    /* Adiciona os vertices */
	for(i=0; i<numVertices; i++){
      	grafo[i].vertice = 0;
        grafo[i].peso = 0;
      	grafo[i].prox = NULL;
    }

	/* Adiciona as arestas */
    for(i=0; i<numArestas; i++){
        scanf("%d %d %d", &u, &v, &peso);
        inserirAresta(grafo, u, v, peso);
    }

    i = bellmanFord(grafo, numVertices, 0);

    if(i){
        printf("Possivel\n");
    }
    else{
        printf("Impossivel\n");
    }

	for(i=0; i<numVertices; i++){
		aux = grafo[i].prox;
		while (aux != NULL) {
			tmp = aux;
			aux = aux->prox;
			free(tmp);
		}
	}
	free(grafo);

    return 0;
}
