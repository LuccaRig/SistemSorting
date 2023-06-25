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
    scanf("%s %d", lua->nome_lua, &lua->raio_lua);
}

void InputPlaneta(Planeta *planeta, int n_luas){
    planeta->quantidade_luas = n_luas;
    planeta->luas = (Lua*) malloc(n_luas*sizeof(Lua));
    for(int i=0;i<n_luas;i++){
        InputLua(&planeta->luas[i]);
    }
}

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
        scanf("%s %d %d", sistema->planetas[i].nome_planeta, &sistema->planetas[i].raio_planeta, &n_luas);
        InputPlaneta(&sistema->planetas[i], n_luas);
    }
}

void FreeSistema(Sistema *sistema){
    free(sistema->planetas);
    sistema->planetas = 0;
}

void FreeTudo(Sistema *Lista_Sistemas){
    free(Lista_Sistemas);
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