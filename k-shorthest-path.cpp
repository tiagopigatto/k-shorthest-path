#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stddef.h>
#include <algorithm>


using namespace std;

//Recebe vetor de custos e retorna custo total
int custoTotal(vector<int> custos);

//Calcula menor caminho entre os nós [no1] e [no2] e preenche vetores 'caminho' e 'custos'
void dijkstra(int size, vector<vector<int> >& matriz, int no1, int no2, vector<int>& custos, vector<int>& caminho);

//Le arquivo de topologia, insere o grafo em [matrix] e retorna número de nós
int leTopologia(vector<vector<int> >& matrix);

 //Encontra índice do nó com aresta de menor custo 
long menorCusto(vector<int>& custos);

//Remove aresta de menor custo da matriz
void atualizaMatriz(int menorCusto, vector<vector<int> >& matriz, vector<int> &caminho);


int main(int argc, const char *argv[]){
    
    if (argc != 4){
        cout << "Esperam-se 3 argumentos: [no1] [no2] [k]" << endl;
        exit(1);
    }
    if (atoi(argv[1]) == atoi(argv[2])){
		 cout << "O no de origem deve ser diferente do no de destino" << endl;
		 exit(1);
	 }
	 if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0){
       cout << "Os nos de origem e destino devem ser numero positivos" << endl;
       exit(1);
    }

    int numberOfLines, no1, no2, custo = 0, minCusto;
    long no1_l, no2_l, k_l;
    long indiceMenorCusto;
    int k = 3;
    char *p;
    vector<vector<int> > matriz;
    vector<int> custos;
    vector<int> caminho;

	 no1 = atoi(argv[1]) - 1;
	 no2 = atoi(argv[2]) - 1;
	 k = atoi(argv[3]);
    
	 //Le arquivo de topologia e retorna o número de nós no grafo
    numberOfLines = leTopologia(matriz);

    if(atoi(argv[1]) > numberOfLines){
       cout << "No de origem nao existente na topologia. Consulte os indices do nos no arquivo de entrada" << endl;
       exit(1);
    }
    if(atoi(argv[2]) > numberOfLines){
       cout << "No de destino nao existente na topologia. Consulte os indices do nos no arquivo de entrada" << endl;
       exit(1);
    }

    
    for(int i=0; i< k; i++){
        //Encontra o primeiro menor caminho 
        dijkstra(numberOfLines, matriz, no1, no2, custos, caminho);
        
        //Caminho inexistente
        if (caminho.size() == 0){
            printf("Nao existe o caminho: %d\n", i + 1);
            break;
        }

        //Imprime caminho encontrado
        if(caminho.size() > 0){
            for(int k = 0; k < caminho.size(); k++){
                if(k != caminho.size() - 1){
                    printf("%d-->", caminho[k] + 1);
                }else{
                    printf("%d\n", caminho[k]  + 1);
                }
            }
        }

        //Imprime pesos de cada aresta do caminho encontrado       
        if (custos.size() > 0){
            for(int k = 0; k < custos.size(); k++){
                printf(" %d  ", custos[k]);
            }
            printf("\n");
        }
        
        //Imprime custo total do caminho
        custo = custoTotal(custos);
        printf("Custo Total: %d\n", custo);
        
        //Encontra índice do nó com aresta de menor custo 
        indiceMenorCusto = menorCusto(custos);

        //minCusto recebe o índice do nó com aresta de menor custo
        minCusto = int(indiceMenorCusto);
        
        //Remove aresta de menor custo no caminho encontrado
        atualizaMatriz(minCusto, matriz, caminho);
    }
    
    
    return 0;
}

int leTopologia(vector<vector<int> >& matrix){
    
    FILE *fp;
    char ch, *line, *node1, *node2, *weight;
    int numberOfLines = 0;
    size_t len = 0;
    int node1_int, node2_int, weight_int;
    
    fp = fopen("entrada.txt", "r");
    
    //Numero de linhas do arquivo, ou seja numero de nos
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch =='\n'){
            numberOfLines++;
        }
    }
    
    //Realoca tamanho da matriz
    matrix.resize(numberOfLines);
    for(int i=0; i< numberOfLines; i++){
        matrix[i].resize(numberOfLines);
    }
    
    
    //Retorna para o início do arquivo
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
    
    fclose(fp);
    
    return numberOfLines;
    
}


void dijkstra(int size, vector<vector<int> >& matriz, int no1, int no2, vector<int>& custos, vector<int>& caminho){
    
    int distancia[size];
    int i, num;
    int minimum, min_index = 0;
    int pai[size];
    vector<int> vetor_aux;
    int visited[size]; // visited[i] = 0 se nó i não foi visitado, visited[i] = 1 caso contrário
    
    custos.clear();
    caminho.clear();

    if (no1 == no2){
        return;

    }

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
    
    
    //Preenche vetor caminho com menor caminho
    caminho.push_back(no2);
    for(i=1;i<size;i++){
        caminho.push_back(pai[caminho.at(i-1)]); //vetor_aux[i] = pai[vetor_aux[i-1]];
        if(pai[caminho.at(i-1)] == no1) break;
    }
    //Inverte vetor caminho para impressao correta
    reverse(caminho.begin(), caminho.end());
    
    //Preenche vetor com custos do menor caminho
    for(i=0; i < caminho.size() - 1; i++)
        custos.push_back( matriz[caminho[i]][caminho[i+1]]);
    
}

long menorCusto(vector<int>& custos){
    int menor = *min_element(custos.begin(), custos.end());
    return distance(custos.begin(), find(custos.begin(), custos.end(), menor));

}

void atualizaMatriz(int menorCusto, vector<vector<int> >& matriz, vector<int> &caminho){
    
    int i, j;
    
    i = caminho.at(menorCusto);
    j = caminho.at(menorCusto+1);
    
    matriz[i][j] = 0;
    matriz[j][i] = 0;
    
}

int custoTotal(vector<int> custos){
    int custo = 0;
    
    for (int i =0; i< custos.size(); i++){
        custo += custos[i];
    }
    
    return custo;
}

