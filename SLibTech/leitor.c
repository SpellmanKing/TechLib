#include <stdio.h>
#include "leitor.h"

Leitor leitores[MAX_LEITORES] = {
    {"Joao", "111", "9999", 0},
    {"Maria", "222", "8888", 0},
    {"Pedro", "333", "7777", 0},
    {"Ana", "444", "6666", 0},
    {"Lucas", "555", "5555", 0}
};

void listarLeitores() {
    printf("\n===== LEITORES =====\n");

    for (int i = 0; i < MAX_LEITORES; i++) {
        printf("%d - %s (Divida: %.2f)\n",
               i, leitores[i].nome, leitores[i].dividas);
    }
}