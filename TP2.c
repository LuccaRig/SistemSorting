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
/*void FreePlaneta(Planeta *planeta){
    free(planeta->luas);
    planeta->quantidade_luas = 0;
}*/

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
/*void FreeSistema(Sistema *sistema){ 
    free(sistema->planetas);
    sistema->quantidade_planetas = 0;
}
    //TO DO: Limpar todos os valores nas funções free
void FreeTudo(Sistema *Lista_Sistemas){
    free(Lista_Sistemas);
}*/
int MaiorPlaneta(Sistema sistema){
    int maior=0;
    for(int i=0;i<sistema.quantidade_planetas;i++){
            if(sistema.planetas[i].raio_planeta > maior){
                maior=i;
            }
    }
    return maior;
}

int MaiorLua(Sistema sistema){
    int maior=0;
    for(int i=0;i<sistema.planetas->quantidade_luas;i++){
            if(sistema.planetas->luas[i].raio_lua > maior){
                maior=i;
            }
    }
    return maior;
}

int ComparacaoDosSistemas(Sistema sistema1, Sistema sistema2){
    
    if(sistema1.raio_sol != sistema2.raio_sol){
        return sistema1.raio_sol > sistema2.raio_sol;
    }
    if(sistema1.quantidade_planetas != sistema2.quantidade_planetas){
        return sistema1.quantidade_planetas > sistema2.quantidade_planetas;
    }
    if(sistema1.planetas[MaiorPlaneta(sistema1)].raio_planeta != sistema2.planetas[MaiorPlaneta(sistema2)].raio_planeta){
        return sistema1.planetas[MaiorPlaneta(sistema1)].raio_planeta > sistema2.planetas[MaiorPlaneta(sistema2)].raio_planeta;
    }
    if(sistema1.planetas->quantidade_luas != sistema2.planetas->quantidade_luas){
        return sistema1.planetas->quantidade_luas > sistema2.planetas->quantidade_luas;
    }
    if(sistema1.planetas->luas[MaiorLua(sistema1)].raio_lua != sistema2.planetas->luas[MaiorLua(sistema2)].raio_lua){
        return sistema1.planetas->luas[MaiorLua(sistema1)].raio_lua > sistema2.planetas->luas[MaiorLua(sistema2)].raio_lua;
    }
    if(sistema1.tempo_descoberta != sistema2.tempo_descoberta){
        return sistema1.tempo_descoberta > sistema2.tempo_descoberta;
    }
    
}

void Ritacao(Sistema *Lista_Sistemas, int InicioDoVetor1, int FinalDoVetor1, int InicioDoVetor2, int FinalDoVetor2){
    int tamanho= FinalDoVetor2 - InicioDoVetor1;
    Sistema *Sistemas_Ordenados = (Sistema*) malloc(tamanho*sizeof(Sistema));
    for(int i=InicioDoVetor1, j=InicioDoVetor1,k=0;i<FinalDoVetor1||j<FinalDoVetor2;k++){
        if(i==FinalDoVetor1){
            Sistemas_Ordenados[k] = Lista_Sistemas[j];
            j++;
        }
        else if(j==FinalDoVetor2){
            Sistemas_Ordenados[k] = Lista_Sistemas[i];
            i++;
        }
        else if(ComparacaoDosSistemas(Lista_Sistemas[i], Lista_Sistemas[j])){
            Sistemas_Ordenados[k] = Lista_Sistemas[i];
            i++;
        }
        else{
            Sistemas_Ordenados[k] = Lista_Sistemas[j];
            j++;
        }
    }
    for(int i=InicioDoVetor1,j=0;i<FinalDoVetor2;i++,j++){
        Lista_Sistemas[i] = Sistemas_Ordenados[j];
    }
    //free(Sistemas_Ordenados); TO DO: Liberar memória dos Sistemas_Ordenados
}

Sistema* BromeroSort(Sistema *Lista_Sistemas, int InicioDoVetor1, int FinalDoVetor2){
    int tamanho=0, meio=0;
    tamanho = FinalDoVetor2 - InicioDoVetor1; 
    if(tamanho = 1){
        return Lista_Sistemas;
    }
    if(tamanho%2 == 1){
        BromeroSort(&Lista_Sistemas, InicioDoVetor1, FinalDoVetor2 - 1);
        Ritacao(&Lista_Sistemas,InicioDoVetor1, tamanho - 1, tamanho - 1, FinalDoVetor2);
        return Lista_Sistemas;
    }
    meio = (FinalDoVetor2 + InicioDoVetor1)/2;
    BromeroSort(&Lista_Sistemas, InicioDoVetor1, meio);
    BromeroSort(&Lista_Sistemas, meio, FinalDoVetor2);
    Ritacao(&Lista_Sistemas, InicioDoVetor1, tamanho, tamanho, FinalDoVetor2);
    
}

int main(){
    int quantidade_sistemas=0, n_planetas=0;
    scanf("%d", &quantidade_sistemas);
    Sistema *Lista_Sistemas = (Sistema*) malloc(quantidade_sistemas*sizeof(Sistema));
    for(int i=0;i<quantidade_sistemas;i++){
        scanf("%d %s %d %d", &Lista_Sistemas[i].tempo_descoberta, Lista_Sistemas[i].nome_sistema, &Lista_Sistemas[i].raio_sol, &n_planetas);
        InputSistema(&Lista_Sistemas[i], n_planetas);
    }
    BromeroSort(&Lista_Sistemas, 0, quantidade_sistemas);
    for(int i=0;i<quantidade_sistemas;i++){
        printf("%s", Lista_Sistemas[i].nome_sistema); 
    }

    
}