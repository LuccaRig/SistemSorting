#include <stdlib.h>
#include <stdio.h>

                    //Inicialização das Structs
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
    long int tempo_descoberta; 
    int raio_sol, quantidade_planetas;
    char nome_sistema[101];
    Planeta *planetas;

}Sistema;

                //Fim da Iniciaçização das Structs


                //Alocação dos Planetas e das Luas

void LuaNoVoid(Lua *lua){
    scanf("\t\t%s %d\n", lua->nome_lua, &lua->raio_lua);
}

void LuaNoPlaneta(Planeta *planeta, int n_luas){
    planeta->quantidade_luas = n_luas;
    planeta->luas = (Lua*) malloc(n_luas*sizeof(Lua));
    for(int i=0;i<n_luas;i++){
        LuaNoVoid(&planeta->luas[i]);
    }
}

void PlanetaNoSitema(Sistema *sistema, int n_planetas){
    int n_luas = 0;
    Planeta planeta;
    sistema->quantidade_planetas = n_planetas;
    sistema->planetas = (Planeta*) malloc(n_planetas*sizeof(Planeta));
    for(int i=0;i<n_planetas;i++){
        scanf("\t%s %d %d\n", sistema->planetas[i].nome_planeta, &sistema->planetas[i].raio_planeta, &n_luas);
        LuaNoPlaneta(&sistema->planetas[i], n_luas);
    }
}

                //Fim da Alocação dos Planetas e das Luas


                //Funções para realizar a comparação da ritação

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

int ContadorDeLuas(Planeta* planetas, int num_planetas){
    int num_luas=0;
    for(int EstouPerdendoMinhaSanidadeAosPoucos=0; EstouPerdendoMinhaSanidadeAosPoucos<num_planetas; EstouPerdendoMinhaSanidadeAosPoucos++){
        num_luas += planetas[EstouPerdendoMinhaSanidadeAosPoucos].quantidade_luas;
    }
    return num_luas;
}


                //Fim das Funções para realizar a comparação da ritação


                //Ritação e Comparação dos Sistemas

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
    if(ContadorDeLuas(sistema1.planetas, sistema1.quantidade_planetas) != ContadorDeLuas(sistema2.planetas, sistema2.quantidade_planetas)){
        return ContadorDeLuas(sistema1.planetas, sistema1.quantidade_planetas) > ContadorDeLuas(sistema2.planetas, sistema2.quantidade_planetas);
    }
    if(sistema1.planetas->luas[MaiorLua(sistema1)].raio_lua != sistema2.planetas->luas[MaiorLua(sistema2)].raio_lua){
        return sistema1.planetas->luas[MaiorLua(sistema1)].raio_lua > sistema2.planetas->luas[MaiorLua(sistema2)].raio_lua;
    }
    if(sistema1.tempo_descoberta != sistema2.tempo_descoberta){
        return sistema1.tempo_descoberta < sistema2.tempo_descoberta;
    }
    
}

void Ritacao(Sistema *Lista_Sistemas, int InicioDoVetor1, int FinalDoVetor1, int InicioDoVetor2, int FinalDoVetor2){
    int tamanho= FinalDoVetor2 - InicioDoVetor1;
    Sistema *Sistemas_Ordenados = (Sistema*) malloc(tamanho*sizeof(Sistema));
    for(int i=InicioDoVetor1, j=InicioDoVetor2,k=0;i<FinalDoVetor1||j<FinalDoVetor2;k++){
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
    free(Sistemas_Ordenados);
}

                //Fim da Ritação e Comparação

                //BromeroSort

void BromeroSort(Sistema *Lista_Sistemas, int InicioDoVetor1, int FinalDoVetor2){
    int tamanho=0, meio=0;
    tamanho = FinalDoVetor2 - InicioDoVetor1; 
    if(tamanho == 1){
        return;
    }
    if(tamanho%2 == 1){
        BromeroSort(Lista_Sistemas, InicioDoVetor1, FinalDoVetor2 - 1);
        Ritacao(Lista_Sistemas,InicioDoVetor1, FinalDoVetor2 - 1, FinalDoVetor2 - 1, FinalDoVetor2);
        return ;
    }
    meio = (FinalDoVetor2 + InicioDoVetor1)/2;
    BromeroSort(Lista_Sistemas, InicioDoVetor1, meio);
    BromeroSort(Lista_Sistemas, meio, FinalDoVetor2);
    Ritacao(Lista_Sistemas, InicioDoVetor1, meio, meio, FinalDoVetor2);
    return;
    
}

                //Fim do BromeroSort

                //Liberação de Memória
void LiberaLua(Planeta* planetas, int num_planetas){
    for(int JaMeCanseiBoraPDS2=0;JaMeCanseiBoraPDS2<num_planetas;JaMeCanseiBoraPDS2++){
        free(planetas[JaMeCanseiBoraPDS2].luas);
    }
}
void LiberaPlaneta(Sistema *sistema, int num_sistemas){
    for(int SoQueriaTomarUma=0;SoQueriaTomarUma<num_sistemas;SoQueriaTomarUma++){
        LiberaLua(sistema[SoQueriaTomarUma].planetas, sistema[SoQueriaTomarUma].quantidade_planetas);
        free(sistema[SoQueriaTomarUma].planetas);
    }
}

                //Fim da liberação de memória

int main(){
    long int quantidade_sistemas=0; 
    int n_planetas=0;
    scanf("%ld\n", &quantidade_sistemas);
    Sistema *Lista_Sistemas = (Sistema*) malloc(quantidade_sistemas*sizeof(Sistema));
    for(int i=0;i<quantidade_sistemas;i++){
        scanf("%ld %s %d %d", &Lista_Sistemas[i].tempo_descoberta, Lista_Sistemas[i].nome_sistema, &Lista_Sistemas[i].raio_sol, &n_planetas);
        if(n_planetas!=0)PlanetaNoSitema(&Lista_Sistemas[i], n_planetas);
    }
    BromeroSort(Lista_Sistemas, 0, quantidade_sistemas);
    for(int i=0;i<quantidade_sistemas;i++){
        printf("%s\n", Lista_Sistemas[i].nome_sistema); 
    }
    LiberaPlaneta(Lista_Sistemas, quantidade_sistemas);
    free(Lista_Sistemas);
}

