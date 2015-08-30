#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <vector>
#include <iostream>
#include <stddef.h>
#include <algorithm>

using namespace std;

void dijkstra(int size, int **matriz, int no1, int no2, vector<int>& custos, vector<int>& caminho);
int leTopologia(FILE *p, int **matriz);
int menorCusto(vector<int>& custos);
void atualizaMatriz(int menorCusto, int **matriz, vector<int>&);


int main(int argc, const char *argv[]){

	return 0;
}

int leTopologia(FILE *p, int **matriz){

	/*if(argc != 4){
        printf("Espera-se 3 argumentos: No1, No2 e K.");
        exit(1);
    }*/
  
  
    int no1, no2, k;
    //no1 = atoi(argv[1]);
    //no2 = atoi(argv[2]);
    k = atoi(argv[3]);


    //Paths *arrayA, *arrayB = NULL;

    FILE *fp;
    char ch, *line, *node1, *node2, *weight;
    int numberOfLines = 0;
    size_t len = 0;
    size_t arrayA_space = 1;
    size_t arrayB_space = 1;
    int arrayA_it = 0;
    int arrayB_it = 0;
    int **matrix, i_node1, i_node2, i_weight, *custos, *caminho, **matrixCopy;

    fp = fopen("entrada.txt", "r");

    //Numero de linhas do arquivo, ou seja numero de nos
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch =='\n'){
            numberOfLines++;
        }
    }

	cout << numberOfLines << endl;
}


void dijkstra(int size, int **matriz, int no1, int no2, vector<int>& custos, vector<int>& caminho){
    
    int distancia[size];
    int i, num,aux;
    int minimum, min_index = 0;
    int pai[size];
	 vector<int> vetor_aux;
    int visited[size]; // visited[i] = 0 se nó i não foi visitado, visited[i] = 1 caso contrário
    
    //Seta todas as distancias da origem com um valor grande
    for(i = 0; i < size; i++){
        distancia[i] = 32760;
        visited[i] = 0;
    }
    
    //Distancia da origem ate a origem = 0;
    distancia[no1] = 0;
    
    //Encontra menor caminho
    for(num = 0; num < size-1; num++){
        
        minimum = 32760;
        
		  //Proximo no de menor caminho para se visitar
        for(i = 0; i < size; i++){
            if(distancia[i] <= minimum && !visited[i]){
                minimum = distancia[i];
                min_index = i;
            }
        }
        
        visited[min_index] = 1;
        
		  //Atualiza distancia dos nós ate o nó escolhido para se visitar
        for(i = 0; i < size; i++){
            if(!visited[i] && matriz[min_index][i] && distancia[min_index] != 32760 && distancia[min_index]+matriz[min_index][i] < distancia[i]){
                distancia[i] = distancia[min_index] + matriz[min_index][i];
                pai[i] = min_index;
            }
        }
    }
    
    //Se nao houver arestar que cheguem no no2, retorna vetores nulos
    if(distancia[no2] == 32760){
        custos.clear();
        caminho.clear();
        //printf("Nao ha caminho\n");
        return;
    }
    
    
    //Preenche vetor auxiliar com menor caminho
    caminho.push_back(no2);
    aux=1;
    for(i=1;i<size;i++){
		  caminho.push_back(pai[caminho.at(i-1)]); //vetor_aux[i] = pai[vetor_aux[i-1]];
        aux++;
        if(pai[caminho.at(i-1)] == no1) break;
    }
    //for(i=0; i < aux; i++)
    //    caminho[i] = vetor_aux[aux-1-i];
	 reverse(caminho.begin(), caminho.end());
    
    //Preenche vetor com custos do menor caminho
    for(i=0; i < aux-1; i++)
        custos[i] = matriz[caminho[i]][caminho[i+1]];

}

int menorCusto(vector<int>& custos){


}

void atualizaMatriz(int menorCusto, int **matriz, vector<int>&){


}
