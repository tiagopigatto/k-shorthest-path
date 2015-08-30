#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

void dijkstra(int size, int **matriz, int no1, int no2, vector<int>& custos, vector<int>& caminho);
int leTopologia(FILE *p, int **matriz);
int menorCusto(vector<int>& custos);
void atualizaMatriz(int menorCusto, int **matriz, vector<int>&);


int main(int argc, const char *argv[]){

	return 0;
}

int leTopologia(FILE *p, int **matriz){

}


void dijkstra(int size, int **matriz, int no1, int no2, vector<int>& custos, vector<int>& caminho){

}

int menorCusto(vector<int>& custos){
	int menor = *min_element(custos.begin(), custos.end());
	int indice  = distance(custos.begin(), find(custos.begin(), custos.end(), menor));
	return indice;
}

void atualizaMatriz(int menorCusto, int **matriz, vector<int>&){


}

