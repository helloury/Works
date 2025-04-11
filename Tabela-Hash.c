//Trabalho de Tabela Hash com tratamento de colisão por sondagem linear
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NIL -1

//encontrar a primeira potência de 2 maior que N
int prox_potencia_2(int n) {
    int pot = 1;
    while (pot < n) {
        pot *= 2;
    }
    return pot;
}

//método da multiplicação
int hash_multiplicacao(int key, int size) {
    const double A = (sqrt(5) - 1) / 2;
    double frac_part = key * A - (int)(key * A);
    return (int)(size * frac_part);
}

// inserir uma chave na tabela 
void inserir(int *tabela, int size, int key) {
    int index = hash_multiplicacao(key, size);
    while (tabela[index] != NIL) { //Tratamento de colisao por sondagem linear
        index = (index + 1) % size;
    }
    tabela[index] = key;
}

//remover uma chave da tabela 
void remover(int *tabela, int size, int key) {
    int index = hash_multiplicacao(key, size);
    int start = index;
    while (tabela[index] != NIL) {
        if (tabela[index] == key) {
            tabela[index] = NIL;
            return;
        }
        index = (index + 1) % size;
        if (index == start) break; // Evita loop infinito
    }
    printf("Chave %d não encontrada.\n", key);
}

//para imprimir a tabela 
void imprimir_tabela(int *tabela, int size) {
    printf("Tabela Hash:\n");
    for (int i = 0; i < size; i++) {
        if (tabela[i] == NIL) {
            printf("[%d] /\n", i);
        } else {
            printf("[%d] %d\n", i, tabela[i]);
        }
    }
}

int main() {
    int max_elementos;
    printf("Digite a quantidade máxima de elementos a serem armazenados: ");
    scanf("%d", &max_elementos);

    int tamanho = prox_potencia_2(max_elementos);
    int *tabela = (int *)malloc(tamanho * sizeof(int));
    for (int i = 0; i < tamanho; i++) {
        tabela[i] = NIL;
    }

    int opcao, key, qtd;
    srand(time(NULL));

    do {
        printf("\nMenu:\n");
        printf("1. Inserir valor manualmente\n");
        printf("2. Gerar valores aleatórios\n");
        printf("3. Remover valor\n");
        printf("4. Exibir tabela\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um valor para inserir: ");
                scanf("%d", &key);
                inserir(tabela, tamanho, key);
                break;
            case 2:
                printf("Quantos valores aleatórios deseja gerar? ");
                scanf("%d", &qtd);
                for (int i = 0; i < qtd; i++) {
                    key = rand() % 1000; // Valores entre 0 e 999
                    inserir(tabela, tamanho, key);
                }
                break;
            case 3:
                printf("Digite um valor para remover: ");
                scanf("%d", &key);
                remover(tabela, tamanho, key);
                break;
            case 4:
                imprimir_tabela(tabela, tamanho);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    free(tabela);
    return 0;
}
