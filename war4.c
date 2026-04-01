#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 50

struct Territorio{
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropa;
};

void limparenter(char texto[]){
    texto[strcspn(texto, "\n")] = '\0';
}

void cadastrarterritorio(struct Territorio *p){
    printf ("   -Nome do Territorio: ");
    fgets (p->nome, MAX_STRING, stdin);
    limparenter(p->nome);

    printf ("   -Cor do Exercito (ex: Preto, Azul): ");
    fgets (p->cor, MAX_STRING, stdin);
    limparenter(p->cor);

    printf ("   -Numero de Tropas: ");
    scanf ("%d", &p->tropa);
    getchar();

    printf ("\n");
}

void exibirterritorio(struct Territorio *t){
    printf ("%s ", t->nome);
    printf ("(Exercito %s, ", t->cor);
    printf ("%d Tropas)\n", t->tropa);
}

void atacar(struct Territorio *atacante, struct Territorio *defesa){
    int dadoatacante = rand() % 6 + 1;
    int dadodefesa = rand() % 6 + 1;

    printf ("\n--- RESULTADO DA BATALHA ---\n");
    printf ("O atacante %s rolou o dado e tirou: %d\n", atacante->nome, dadoatacante);
    printf ("O defensor %s rolou o dado e tirou: %d\n", defesa->nome, dadodefesa);

    if (dadoatacante > dadodefesa){
        printf ("VITORIA DO ATAQUE! Defensor perdeu %d tropas\n", defesa->tropa);
        defesa->tropa = atacante->tropa /=2;
        atacante->tropa /=2;
        strcpy(defesa->cor, atacante->cor);
    } else{
        printf ("DEFENSOR RESISTIU! Atacante perde 1 tropa\n");
        atacante->tropa -=1;
    }

    printf ("\n");
}

void liberarmemoria(struct Territorio *territorios){
    free(territorios);
}


//====== FUÇÃO MAIN =====//
int main(){
    struct Territorio *territorios;
    int escolha;
    srand(time(NULL));
    int ataque, defensor;

    printf ("=====================================================\n");
    printf ("   WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf ("=====================================================\n");

    printf ("\n");
    printf ("Quantos territorios deseja cadastrar: ");
    scanf ("%d", &escolha);
    getchar();
    printf ("\n");

    territorios = malloc(escolha * sizeof(struct Territorio));

    if (territorios == NULL){
        printf ("Falha ao alocar memoria!\n");
        return 1;   
    }

    // --- Função de Cadastro de Territorios --- //
    for(int j = 0; j < escolha; j++){
        printf ("Cadastro territorio %d\n", j + 1);
        cadastrarterritorio(&territorios[j]);       
    }

do{    
    for(int i = 0; i < escolha; i++){
        printf ("Territorio %d. ", i + 1);
        exibirterritorio(&territorios[i]);
    }

    printf ("\n=== FASE DE ATAQUE ===\n");
    printf("Escolha o territorio atacante de 1 a %d (ou 0 para sair): ", escolha);
    scanf ("%d", &ataque);
    getchar();

    if (ataque == 0){
        break;
    }

    if (ataque < 0 || ataque > escolha){
        printf ("###*ERRO, TERRITORIO ATACANTE INVALIDO*###\n");
        continue;
    }

    printf ("Escolha o territorio defensor de 1 a %d: ", escolha);
    scanf ("%d", &defensor);
    getchar();

    if (defensor <= 0 || defensor > escolha){
        printf ("###*ERRO, TERRITORIO DEFENSOR INVALIDO*###\n");
        continue;
    }

    if (ataque == defensor){
        printf ("###*ERRO, TERRITORIO DEFENSOR IGUAL O ATACANTE*###\n");
        continue;
    }

   if (strcmp(territorios[ataque - 1].cor, territorios[defensor -1].cor) == 0){
        printf ("###*ERRO, NAO PODE ATACAR TERRITORIO DA MESMA COR*###\n");
        continue;
    }

    atacar(&territorios[ataque - 1], &territorios[defensor - 1]);

} while(1);

    printf ("Fim de Jogo!\n");

    liberarmemoria(territorios);
}