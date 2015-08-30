#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <vector>
#include <iostream>
<<<<<<< HEAD
#include <algorithm>
#include <iterator>
=======
#include <stddef.h>
#include <algorithm>
>>>>>>> 6e13049967e73f8e116ecc4b3057aac55c507ed6

using namespace std;

void dijkstra(int size, int **matriz, int no1, int no2, vector<int>& custos, vector<int>& caminho);
int leTopologia(vector<vector<int> >& matrix );
int menorCusto(vector<int>& custos);
void atualizaMatriz(int menorCusto, int **matriz, vector<int> &caminho);


int main(int argc, const char *argv[]){
    
	return 0;
}

int leTopologia(vector<vector<int> >& matrix){

    FILE *fp;
    char ch, *line, *node1, *node2, *weight;
    int numberOfLines = 0;
    size_t len = 0;
    int node1_int, node2_int, weight_int;

    fp = fopen("6.txt", "r");

    //Numero de linhas do arquivo, ou seja numero de nos
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch =='\n'){
            numberOfLines++;
        }
    }

    matrix.resize(numberOfLines);
    for(int i=0; i< numberOfLines; i++){
        matrix[i].resize(numberOfLines);
    }

    

    fseek(fp, 0, SEEK_SET);

    //Loop para ler todas as linhas do arquivo
    for(int i = 0; i<numberOfLines; i++){
        //Le a linha
        getline(&line, &len, fp);
        
        //Lê o primeiro no
        node1 = strtok(line, " []-;");
        node1_int = atoi(node1);
        
        //Loop para ler todos os nos e os pesos
        do{
            //Lê o segundo no
            node2 = strtok(NULL, " []-;\n");
            if (node2 == NULL) break;
            node2_int = atoi(node2);
            
            //Lê o peso
            weight = strtok(NULL, " []-;\n");
            if (weight == NULL) break;
            weight_int = atoi(weight);
            
            //Atribui a matriz o peso certo
            matrix[node1_int - 1][node2_int - 1] = weight_int;
            
        }while (node2 != NULL || weight != NULL);
    }

    return numberOfLines;

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
	int menor = *min_element(custos.begin(), custos.end());
	int indice  = distance(custos.begin(), find(custos.begin(), custos.end(), menor));
	return indice;
}

void atualizaMatriz(int menorCusto, int **matriz, vector<int> &caminho){

	int i, j;

	i = caminho.at(menorCusto);
	j = caminho.at(menorCusto+1);

	matriz[i][j] = 0;
	matriz[j][i] = 0;	

}

