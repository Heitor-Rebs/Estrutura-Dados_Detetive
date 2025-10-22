#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Criando a estrutura dos nós */
struct No {
    char nome[50];
    char pista[100];
    struct No* esquerda;
    struct No* direita;
};

/* Criando a estrutura das pistas */
struct Pista {
    char pista[100];
    struct Pista* esquerda;
    struct Pista* direita;
};

/* Função para criar nó na árvore de pistas */
struct Pista* criarPista(const char* pista) {
    struct Pista* novapista = (struct Pista*) malloc(sizeof(struct Pista));
    strcpy(novapista->pista, pista);
    novapista->esquerda = NULL;
    novapista->direita = NULL;
    return novapista;
}

/* Inserir pista na BST */
struct Pista* inserirPista(struct Pista* raiz, char* pista) {
    if (raiz == NULL)
        return criarPista(pista);

        if (strcmp(pista, raiz->pista) < 0)
            raiz->esquerda = inserirPista(raiz->esquerda, pista);
        else if (strcmp(pista, raiz->pista) > 0)
            raiz->direita = inserirPista(raiz->direita, pista);

        return raiz;
}

/* Função para mostrar as pistas coletadas em ordem alfabética */
void mostrarPistas(struct Pista* raiz) {
    if (raiz != NULL) {
        mostrarPistas(raiz->esquerda);
        printf("%s\n", raiz->pista);
        mostrarPistas(raiz->direita);
    }
}

/* Função para criar nova sala */
struct No* criarSala(char* nome, char* pista) {
    struct No* novaSala = (struct No*) malloc(sizeof(struct No));
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/* Função para o usuário explorar o mapa */
void explorarSalas(struct No* raiz, char salasPassadas[][50], int *passos, struct Pista* pistas)
{
    int i = 0;
    char lado[3];
    /* Conferir se o comodo existe */
    if (raiz != NULL)
    {
        inserirPista(pistas,raiz->pista);
        /* Conferir se o comodo tem saida */
        if(raiz->esquerda == NULL && raiz->direita == NULL)
        {
            strcpy(salasPassadas[*passos], raiz->nome);
            (*passos)++;
            printf("\nSala final: %s\n",raiz->nome);
            printf("Pistas na sala: %s\n",raiz->pista);
            printf("Comodo sem saidas\n");
        }else
        {
            strcpy(salasPassadas[*passos], raiz->nome);
            (*passos)++;
            printf("\n--Explorar mansao--\n");
            printf("Sala atual: %s\n",raiz->nome);
            printf("Pistas na sala: %s\n",raiz->pista);
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
                explorarSalas(raiz->direita, salasPassadas, passos, pistas);

            }else if(strcmp(lado, "e") == 0)
            {
                explorarSalas(raiz->esquerda, salasPassadas, passos, pistas);

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
    struct Pista* pistas = criarPista("Pegadas de barro no tapete");
    struct No* raiz = criarSala("Hall de Entrada", "Pegadas de barro no tapete");
    raiz->esquerda = criarSala("Sala de Estar", "Copo quebrado e um lenço de seda caído");
    raiz->direita = criarSala("Cozinha", "Chaleira ainda quente e uma xicara pela metade");
    raiz->direita->esquerda = criarSala("Lavanderia", "Camisa manchada de sangue na maquina de lavar");
    raiz->direita->direita = criarSala("Deposito", "Caixa derrubada e lanterna apagada no chão");
    raiz->esquerda->esquerda = criarSala("Quarto de hospedes", "Janela aberta e pedaço de tecido preso no trinco");
    raiz->esquerda->direita = criarSala("Quarto Principal", "Gaveta arrombada e joia faltando.");
    raiz->esquerda->direita->direita = criarSala("Banheiro", "Luvas molhadas sobre a pia");
    raiz->esquerda->direita->esquerda = criarSala("Closet", "Frasco de veneno vazio em meio as roupas");

    explorarSalas(raiz, salasPassadas, &passos, pistas);
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

        printf("\n--Pistas coletadas--\n");
        mostrarPistas(pistas);
    }
    return;

}
