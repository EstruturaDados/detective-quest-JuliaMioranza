#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura base: cada sala tem um nome e ponteiros para esquerda/direita
typedef struct Sala {
    char nome[64];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// criarSala() – cria, de forma dinâmica, uma sala com nome
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (!nova) {
        fprintf(stderr, "Falha ao alocar memoria para a sala \"%s\".\n", nome);
        exit(EXIT_FAILURE);
    }
    strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
    nova->nome[sizeof(nova->nome) - 1] = '\0';
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// liberarArvore() – libera toda a memoria da arvore 
void liberarArvore(Sala* raiz) {
    if (!raiz) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// printa as opcoes de direção para a sala atual
static void mostrarOpcoes(const Sala* atual) {
    printf("\nOnde seguir a partir de \"%s\"?\n", atual->nome);
    if (atual->esquerda) printf("  [e] Esquerda -> %s\n", atual->esquerda->nome);
    if (atual->direita)  printf("  [d] Direita  -> %s\n", atual->direita->nome);
    printf("  [s] Sair da exploracao\n");
    printf("Escolha: ");
}

// explorarSalas() – permite a navegação do jogador pela árvore
void explorarSalas(Sala* raiz) {
    if (!raiz) {
        printf("Mapa vazio... nada para explorar.\n");
        return;
    }

    Sala* atual = raiz;
    printf("Detective Quest — Exploracao pela mansao\n");
    printf("----------------------------------------\n");
    printf("Ponto de partida: %s\n", atual->nome);
    printf("Caminho percorrido:\n");
    printf("- %s\n", atual->nome);

    while (1) {
        // se chegou num nó-folha, encerra
        if (!atual->esquerda && !atual->direita) {
            printf("\nChegou a um comodo sem saidas. Fim da exploracao em \"%s\".\n", atual->nome);
            break;
        }

        mostrarOpcoes(atual);

        char opc;
        if (scanf(" %c", &opc) != 1) {
          
            printf("\nEntrada invalida. Encerrando.\n");
            break;
        }

        if (opc == 's' || opc == 'S') {
            printf("\nExploracao encerrada por escolha do jogador em \"%s\".\n", atual->nome);
            break;
        } else if (opc == 'e' || opc == 'E') {
            if (atual->esquerda) {
                atual = atual->esquerda;
                printf("- %s\n", atual->nome);
            } else {
                printf("Caminho para a esquerda nao existe a partir daqui. :/\n");
            }
        } else if (opc == 'd' || opc == 'D') {
            if (atual->direita) {
                atual = atual->direita;
                printf("- %s\n", atual->nome);
            } else {
                printf("Caminho para a direita nao existe a partir daqui. :/\n");
            }
        } else {
            printf("Opcao \"%c\" nao reconhecida. Use e, d ou s.\n", opc);
        }
    }
}

// main() – monta o mapa inicial e da inicio a exploracao
int main(void) {
    // Mapa fixo, criado de forma manual e automatizada pela main usando criarSala().
    //
    //                [Hall de entrada]
    //                 /              \
    //        [Biblioteca]          [Corredor Leste]
    //         /        \             /            \
    // [Escritorio]  [Jardim]  [Cozinha]        [Sala de Jantar]
    //                               \
    //                            [Despensa]
    //
    Sala* hall          = criarSala("Hall de entrada");
    Sala* biblioteca    = criarSala("Biblioteca");
    Sala* corredorLeste = criarSala("Corredor Leste");
    Sala* escritorio    = criarSala("Escritorio");
    Sala* jardim        = criarSala("Jardim");
    Sala* cozinha       = criarSala("Cozinha");
    Sala* jantar        = criarSala("Sala de Jantar");
    Sala* despensa      = criarSala("Despensa");

    // ligações
    hall->esquerda          = biblioteca;
    hall->direita           = corredorLeste;

    biblioteca->esquerda    = escritorio;
    biblioteca->direita     = jardim;

    corredorLeste->esquerda = cozinha;
    corredorLeste->direita  = jantar;

    cozinha->direita        = despensa;

    // explorar
    explorarSalas(hall);

    // limpeza 
    liberarArvore(hall);
    return 0;
}
