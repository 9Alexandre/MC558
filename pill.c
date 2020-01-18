
/* 	O algoritimo gera um grafo com os vetices de entrada e realiza um busca em profudidade
	coloriando cada vertice com duas cores. Caso o cagro nao possa ser clorido com apenas
	duas cores distintas, significa que ha um ciclo de comprimento impar e nesse caso
	identificamos o dotutama. Qualquer outra situacao do grafo nao podera nos dizer se temos
	um doturacu ou dotutama.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int vertice;
	int visitado;
	struct No* prox;
}no;

void inserirAresta(no *grafo, int a, int b){

  no *aux;
  no *tmp;

  aux = (no*) malloc((int)sizeof(no));
  aux->vertice = b;
  aux->prox = NULL;

  grafo[a].vertice++;
  if(grafo[a].prox == NULL)
    grafo[a].prox = aux;
  else {
    tmp = grafo[a].prox;
    if (tmp->vertice > b) {
      aux->prox = tmp;
      grafo[a].prox = aux;
    }
    else if (tmp->prox == NULL) {
      aux->prox = tmp->prox;
      tmp->prox = aux;
    }
    else {
      while((tmp->prox != NULL) && (tmp->prox->vertice < b))
		tmp = tmp->prox;
      aux->prox = tmp->prox;
      tmp->prox = aux;
    }
  }
}

/* 	Se cores[0] == 1, ha pelo menos um ciclo impar */
void DFS_cicloImpar(no *grafo, int vertice, int *cores, int num_vertices){

	int v, i;
	int cor[3] = {0, 0, 0};
	int *vizinhos;
	no *tmp, *aux;

	vizinhos = calloc((num_vertices+1), sizeof(int));

	/* Busca os vizinhos de cada vertice */
	aux = grafo[vertice].prox;
	while (aux != NULL) {
		v = aux->vertice;
		vizinhos[v] = 1;
		aux = aux->prox;
	}

	/* Busca as cores da cada vizinho */
	for (i=1; i<=num_vertices; i++){
		if(i != vertice){
			if(vizinhos[i] == 1){
				if(cores[i] == 0){
					cor[0] = 1;
				}
				else if(cores[i] == 1){
					cor[1] = 1;
				}
				else if(cores[i] == 2){
					cor[2] = 1;
				}
			}
		}
	}

	/* 	Atriubui a cor do vertice com base nas cores do vizinhos
		e verifica se exite ciclos de tamanho impar */
	if((cor[0] == 1 && cor[1] == 0 && cor[2] == 0) || (cor[0] == 0 && cor[1] == 0 && cor[2] == 1) ||
		(cor[0] == 1 && cor[1] == 0 && cor[2] == 1) || (cor[0] == 0 && cor[1] == 0 && cor[2] == 0)){
	    cores[vertice] = 1;
	}
	else if((cor[0] == 0 && cor[1] == 1 && cor[2] == 0) || (cor[0] == 1 && cor[1] == 1 && cor[2] == 0)){
	     cores[vertice] = 2;
	}
	else if((cor[0] == 0 && cor[1] == 1 && cor[2] == 1) || (cor[0] == 1 && cor[1] == 1 && cor[2] == 1)){
	    cores[0] = 1;
		return;
	}

	/*  Realiza a DFS */
	grafo[vertice].visitado = 1;
	tmp = grafo[vertice].prox;
	while(tmp != NULL){
		v = tmp->vertice;
		if(grafo[v].visitado == 0){
			DFS_cicloImpar(grafo, v, cores, num_vertices);
		}
		tmp = tmp->prox;
	}

	free(vizinhos);
}

int main(int argc, char **argv){

    int num_vertices; /* Numero de Vertices */
    int num_arestas; /* Numero de Arestas */
    int u, v, i;
	int *cores;
	no *grafo, *aux, *tmp;

    /* Leitura do quantidade de vertices e de arestas do grafo */
    scanf("%d", &num_vertices);
    scanf("%d", &num_arestas);

	if (num_arestas < 3 || num_vertices < 3) {
		printf("doturacu ou dotutama\n");
		return 0;
	}

	/* Aloca o grafo */
	grafo = malloc((num_vertices+1) * sizeof(no));

	cores = calloc((num_vertices+1), sizeof(int));

	/* Adiciona os vertices */
	for(i=1; i<=num_vertices; i++){
		grafo[i].visitado = 0;
      	grafo[i].vertice = 0;
      	grafo[i].prox = NULL;
    }

	/* Adiciona as arestas */
    for(i=1; i<=num_arestas; i++){
        scanf("%d %d", &u, &v);
        inserirAresta(grafo, u, v);
        inserirAresta(grafo, v, u);
    }

	for(i=1; i<=num_vertices; i++){
		if(grafo[i].visitado == 0){
			DFS_cicloImpar(grafo, i, cores, num_vertices);
		  	if(cores[0] == 1){
				break;
			}
		 }
	 }

	if(cores[0]){
		printf("dotutama\n");
	}
	else{
		printf("doturacu ou dotutama\n");
	}

	/* LIbera a memoria alocada */
	for(i=0; i<num_vertices; i++){
		aux = grafo[i].prox;
		while (aux != NULL) {
			tmp = aux;
			aux = aux->prox;
			free(tmp);
		}
	}

	free(grafo);
	free(cores);

    return 0;
}
