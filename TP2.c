#include <stdlib.h>
#include <stdio.h>

typedef struct Lua{
    char nome_lua[101];
    int raio_lua;
}Lua;

typedef struct Planeta{
    char nome_planeta[101];
    int raio_planeta, quantidade_luas;
    Lua *luas;

}Planeta;

typedef struct Sistema{
    int tempo_descoberta, raio_sol, quantidade_planetas;
    char nome_sistema[101];
    Planeta *planetas;

}Sistema;

void InputLua(Lua *lua){
    scanf("\t\t%s %d", lua->nome_lua, &lua->raio_lua);
}

void InputPlaneta(Planeta *planeta, int n_luas){
    planeta->quantidade_luas = n_luas;
    planeta->luas = (Lua*) malloc(n_luas*sizeof(Lua));
    for(int i=0;i<n_luas;i++){
        InputLua(&planeta->luas[i]);
    }
}
    //TO DO: Limpar todos os valores nas funções free
void FreePlaneta(Planeta *planeta){
    free(planeta->luas);
    planeta->quantidade_luas = 0;
}

void InputSistema(Sistema *sistema, int n_planetas){
    int n_luas = 0;
    Planeta planeta;
    sistema->quantidade_planetas = n_planetas;
    sistema->planetas = (Planeta*) malloc(n_planetas*sizeof(Planeta));
    for(int i=0;i<n_planetas;i++){
        scanf("\t%s %d %d", sistema->planetas[i].nome_planeta, &sistema->planetas[i].raio_planeta, &n_luas);
        InputPlaneta(&sistema->planetas[i], n_luas);
    }
}
    //TO DO: Limpar todos os valores nas funções free
void FreeSistema(Sistema *sistema){ 
    free(sistema->planetas);
    sistema->quantidade_planetas = 0;
}
    //TO DO: Limpar todos os valores nas funções free
void FreeTudo(Sistema *Lista_Sistemas){
    free(Lista_Sistemas);
}

void Ritação(Sistema *Lista_Sistemas, int esquerda, int direita_1,int direita_2, int direita_3){
    
}

Sistema* BromeroSort(Sistema *Lista_Sistemas, int esquerda, int direita){
    int tamanho=0, meio=0;
    tamanho = direita - esquerda; 
    if(tamanho = 1){
        return Lista_Sistemas;
    }
    if(tamanho%2 == 1){
        BromeroSort(Lista_Sistemas, esquerda, direita - 1);
        //Ritação()
        return Lista_Sistemas;
    }
    meio = (direita + esquerda)/2;
    BromeroSort(Lista_Sistemas, esquerda, meio);
    BromeroSort(Lista_Sistemas, meio, direita);
    //Ritação()
    
}

int main(){
    int quantidade_sistemas=0, n_planetas=0;
    scanf("%d", &quantidade_sistemas);
    Sistema *Lista_Sistemas = (Sistema*) malloc(quantidade_sistemas*sizeof(Sistema));
    for(int i=0;i<quantidade_sistemas;i++){
        scanf("%d %s %d %d", &Lista_Sistemas[i].tempo_descoberta, Lista_Sistemas[i].nome_sistema, &Lista_Sistemas[i].raio_sol, &n_planetas);
        InputSistema(&Lista_Sistemas[i], n_planetas);
    }

    
}