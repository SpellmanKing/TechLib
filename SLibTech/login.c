#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[20];
    char senha[20];
} Usuario;

Usuario usuarioSistema = {"admin", "123"};

int login() {
    char nome[20];
    char senha[20];

    printf("\n===== LOGIN =====\n");

    printf("Usuario: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Senha: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0';

    return strcmp(nome, usuarioSistema.nome) == 0 &&
           strcmp(senha, usuarioSistema.senha) == 0;
}

void telaLogin() {
    while (!login()) {
        printf("Login invalido!\n");
    }
}