#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Criando a estrutura dos nós */
struct No {
    char nome[50];
    struct No* esquerda;
    struct No* direita;
};

/* Função para criar novo nó */
struct No* criarSala(char* nome) {
    struct No* novaSala = (struct No*) malloc(sizeof(struct No));
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/* Função para o usuário explorar o mapa */
void explorarSalas(struct No* raiz, char salasPassadas[][50], int *passos)
{
    int i = 0;
    char lado[3];
    /* Conferir se o comodo existe */
    if (raiz != NULL)
    {
        /* Conferir se o comodo tem saida */
        if(raiz->esquerda == NULL && raiz->direita == NULL)
        {
            strcpy(salasPassadas[*passos], raiz->nome);
            (*passos)++;
            printf("Comodo sem saidas\n");
        }else
        {
            strcpy(salasPassadas[*passos], raiz->nome);
            (*passos)++;
            printf("--Explorar mansao--\n");
            printf("Sala atual: %s\n",raiz->nome);
            printf("d - Direita\n");
            printf("e - Esquerda\n");
            printf("s - Sair\n");
            printf("Selecione o lado: ");
            scanf(" %1s", lado);
            lado[strcspn(lado, "\n")] = '\0';
            if(strcmp(lado, "s") == 0)
            {
                return;
            }else if(strcmp(lado, "d") == 0)
            {
                explorarSalas(raiz->direita, salasPassadas, passos);
            }else if(strcmp(lado, "e") == 0)
            {
                explorarSalas(raiz->esquerda, salasPassadas, passos);
            }else
            {
                printf("Opcao Invalida");
            }
        }
    }
}

int main()
{
    char salasPassadas[10][50];
    int passos = 0, i = 0;
    struct No* raiz = criarSala("Hall de Entrada");
    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Cozinha");
    raiz->direita->esquerda = criarSala("Lavanderia");
    raiz->direita->direita = criarSala("Deposito");
    raiz->esquerda->esquerda = criarSala("Quarto de hospedes");
    raiz->esquerda->direita = criarSala("Quarto Principal");
    raiz->esquerda->direita->direita = criarSala("Banheiro");
    raiz->esquerda->direita->esquerda = criarSala("Closet");
    explorarSalas(raiz, salasPassadas, &passos);
    /* Mostrar os comodos passados */
    if(passos == 0)
    {
        return;
    }else
    {
        printf("\n\n--Salas percorridas--\n");
        for(i=0;i<passos;i++)
        {
            printf("Sala %d: %s\n",i+1,salasPassadas[i]);
        }
    }
    return;

}
