#include <stdio.h>
#include <string.h>
#include "livro.h"
#include "leitor.h"

#define MAX_LIVROS 100
#define MAX_EMPRESTIMOS 100

#define RESET_CURSOR "\033[H"

Livro livros[MAX_LIVROS] = {
    {1, "Alice no pais das maravilhas", "Lewis Carroll", 1},
    {2, "Sense Life", "Glitch Tellend", 1},
    {3, "Depressao para leigos", "John Preston", 1},
    {4, "A sutil arte de ligar o foda-se", "Mark Manson", 1},
    {5, "Chapeuzinho vermelho", "Charles Perrault", 1}
};

typedef struct {
    int idLivro;
    int idLeitor;
    char usuario[50];
    int dias;
} Emprestimo;

Livro livros[MAX_LIVROS];
Emprestimo emprestimos[MAX_EMPRESTIMOS];

int totalLivros = 5;
int totalEmprestimos = 0;

void cadastrarLivro() {
    Livro l;

    printf("\nID: ");
    scanf("%d", &l.id);
    getchar(); // limpa buffer

    printf("Titulo: ");
    fgets(l.titulo, sizeof(l.titulo), stdin);
    l.titulo[strcspn(l.titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(l.autor, sizeof(l.autor), stdin);
    l.autor[strcspn(l.autor, "\n")] = '\0';

    l.disponivel = 1;
    livros[totalLivros++] = l;

    printf("Livro cadastrado!\n");
}

void esperarVoltar() {
    int op;

    printf("\nDigite 0 para voltar: ");

    while (scanf("%d", &op) != 1 || op != 0) {
        printf("Entrada invalida! Digite 0: ");
        while(getchar() != '\n');
    }

    getchar(); 
}

void listarLivros() {
    printf("\n===== LIVROS =====\n");

    for (int i = 0; i < totalLivros; i++) {
        printf("ID: %d\n", livros[i].id);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);

        if (livros[i].disponivel) {
            printf("Status: Disponivel\n\n");
        } else {
            
           for (int j = 0; j < totalEmprestimos; j++) {
            if (emprestimos[j].idLivro == livros[i].id) {

            int idLeitor = emprestimos[j].idLeitor;
            printf("Status: Emprestado para %s\n\n",
            leitores[idLeitor].nome);
    }
}
        }
    }

    esperarVoltar();
}

void emprestarLivro() {
    int idLivro, idLeitor;

    printf("\nID do livro: ");
    scanf("%d", &idLivro);
    getchar();

    listarLeitores();

    printf("Escolha o leitor: ");
    scanf("%d", &idLeitor);
    getchar();

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].id == idLivro && livros[i].disponivel) {

            livros[i].disponivel = 0;

            emprestimos[totalEmprestimos].idLivro = idLivro;
            emprestimos[totalEmprestimos].idLeitor = idLeitor;
            emprestimos[totalEmprestimos].dias = 0;

            totalEmprestimos++;

            printf("Emprestimo realizado!\n");
            return;
        }
    }

    printf("Livro indisponivel!\n");
}

void renovarEmprestimo() {
    int id;

    printf("\nID do livro: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLivro == id) {
            printf("Emprestimo renovado!\n");
            return;
        }
    }

    printf("Nao encontrado!\n");
}

void devolucao(){
    int id;

    printf("\nID do livro: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLivro == id) {

            int leitor = emprestimos[i].idLeitor;
            int dias = emprestimos[i].dias;

            if (dias > 7) {
                float multa = (dias - 7) * 2.0;
                leitores[leitor].dividas += multa;

                printf("Multa aplicada: R$ %.2f\n", multa);
            }

            for (int j = 0; j < totalLivros; j++) {
                if (livros[j].id == id) {
                    livros[j].disponivel = 1;
                }
            }

            for (int k = i; k < totalEmprestimos - 1; k++) {
                emprestimos[k] = emprestimos[k + 1];
            }

            totalEmprestimos--;

            printf("Livro devolvido!\n");
            return;
        }
    }

    printf("Emprestimo nao encontrado!\n");
}


void avancarDias() {

    int dias;

    printf("Quantos dias avancar? ");
    scanf("%d", &dias);
    getchar();

    for (int i = 0; i < totalEmprestimos; i++) {
        emprestimos[i].dias += dias;
    }

    printf("Tempo avancado!\n");
}