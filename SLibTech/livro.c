#include <stdio.h>
#include <string.h>

#include "livro.h"
#include "leitor.h"

static int validarIndiceLeitor(int idLeitor) {
    return (idLeitor >= 0 && idLeitor < MAX_LEITORES);
}

static Livro* buscarLivroPorId(int idLivro) {
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].id == idLivro) {
            return &livros[i];
        }
    }
    return NULL;
}

static Emprestimo* buscarEmprestimoAtivoPorLivroId(int idLivro) {
    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLivro == idLivro) {
            return &emprestimos[i];
        }
    }
    return NULL;
}

static int existeEmprestimoAtivoParaLivro(int idLivro) {
    return buscarEmprestimoAtivoPorLivroId(idLivro) != NULL;
}

static void esperarVoltar(void) {
    int op;
    printf("\nDigite 0 para voltar: ");
    while (scanf("%d", &op) != 1 || op != 0) {
        printf("Entrada invalida! Digite 0: ");
        while (getchar() != '\n') {}
    }
    getchar();
}

Livro livros[MAX_LIVROS] = {
    {1, "Alice no pais das maravilhas", "Lewis Carroll", 1},
    {2, "Sense Life", "Glitch Tellend", 1},
    {3, "Depressao para leigos", "John Preston", 1},
    {4, "A sutil arte de ligar o foda-se", "Mark Manson", 1},
    {5, "Chapeuzinho vermelho", "Charles Perrault", 1}
};

Emprestimo emprestimos[MAX_EMPRESTIMOS];

int totalLivros = 5;
int totalEmprestimos = 0;

void cadastrarLivro(void) {
    if (totalLivros >= MAX_LIVROS) {
        printf("\nLimite de livros atingido!\n");
        esperarVoltar();
        return;
    }

    Livro l;

    printf("\nID: ");
    if (scanf("%d", &l.id) != 1) {
        while (getchar() != '\n') {}
        printf("Entrada invalida!\n");
        esperarVoltar();
        return;
    }
    getchar(); // limpa buffer

    printf("Titulo: ");
    if (!fgets(l.titulo, sizeof(l.titulo), stdin)) {
        printf("Erro lendo titulo!\n");
        esperarVoltar();
        return;
    }
    l.titulo[strcspn(l.titulo, "\n")] = '\0';

    printf("Autor: ");
    if (!fgets(l.autor, sizeof(l.autor), stdin)) {
        printf("Erro lendo autor!\n");
        esperarVoltar();
        return;
    }
    l.autor[strcspn(l.autor, "\n")] = '\0';

    l.disponivel = 1;
    livros[totalLivros++] = l;

    printf("Livro cadastrado!\n");
    esperarVoltar();
}

void listarLivros(void) {
    printf("\n===== LIVROS =====\n");

    for (int i = 0; i < totalLivros; i++) {
        printf("\nID: %d\n", livros[i].id);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);

        if (livros[i].disponivel) {
            printf("Status: Disponivel\n");
        } else {
            Emprestimo *e = buscarEmprestimoAtivoPorLivroId(livros[i].id);
            if (e && validarIndiceLeitor(e->idLeitor)) {
                printf("Status: Emprestado para %s\n", leitores[e->idLeitor].nome);
            } else {
                printf("Status: Indisponivel\n");
            }
        }
    }

    esperarVoltar();
}

void emprestarLivro(void) {
    int idLivro;
    int idLeitor;

    printf("\nID do livro: ");
    if (scanf("%d", &idLivro) != 1) {
        while (getchar() != '\n') {}
        printf("Entrada invalida!\n");
        esperarVoltar();
        return;
    }
    getchar();

    Livro *l = buscarLivroPorId(idLivro);
    if (!l) {
        printf("Livro nao encontrado!\n");
        esperarVoltar();
        return;
    }

    if (!l->disponivel) {
        printf("Livro indisponivel!\n");
        esperarVoltar();
        return;
    }

    if (existeEmprestimoAtivoParaLivro(idLivro)) {
        printf("Ja existe um emprestimo ativo para este livro!\n");
        esperarVoltar();
        return;
    }

    if (totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido!\n");
        esperarVoltar();
        return;
    }

    listarLeitores();

    printf("\nEscolha o leitor (ID): ");
    if (scanf("%d", &idLeitor) != 1) {
        while (getchar() != '\n') {}
        printf("Entrada invalida!\n");
        esperarVoltar();
        return;
    }
    getchar();

    if (!validarIndiceLeitor(idLeitor)) {
        printf("Leitor invalido!\n");
        esperarVoltar();
        return;
    }

    l->disponivel = 0;
    emprestimos[totalEmprestimos].idLivro = idLivro;
    emprestimos[totalEmprestimos].idLeitor = idLeitor;
    emprestimos[totalEmprestimos].dias = 0;
    totalEmprestimos++;

    printf("Emprestimo realizado!\n");
    esperarVoltar();
}

void renovarEmprestimo(void) {
    int idLivro;
    int novosDias;

    printf("\nID do livro: ");
    if (scanf("%d", &idLivro) != 1) {
        while (getchar() != '\n') {}
        printf("Entrada invalida!\n");
        esperarVoltar();
        return;
    }
    getchar();

    Emprestimo *e = buscarEmprestimoAtivoPorLivroId(idLivro);
    if (!e) {
        printf("Emprestimo nao encontrado!\n");
        esperarVoltar();
        return;
    }

    printf("Quantos dias deseja renovar (incremento)? ");
    if (scanf("%d", &novosDias) != 1 || novosDias < 0) {
        while (getchar() != '\n') {}
        printf("Valor invalido!\n");
        esperarVoltar();
        return;
    }
    getchar();

    e->dias += novosDias;
    printf("Emprestimo renovado! Agora com %d dias.\n", e->dias);
    esperarVoltar();
}

void devolucao(void) {
    int idLivro;

    printf("\nID do livro: ");
    if (scanf("%d", &idLivro) != 1) {
        while (getchar() != '\n') {}
        printf("Entrada invalida!\n");
        esperarVoltar();
        return;
    }
    getchar();

    Emprestimo *e = buscarEmprestimoAtivoPorLivroId(idLivro);
    if (!e) {
        printf("Emprestimo nao encontrado!\n");
        esperarVoltar();
        return;
    }

    int idLeitor = e->idLeitor;
    int dias = e->dias;

    if (validarIndiceLeitor(idLeitor) && dias > 7) {
        float multa = (dias - 7) * 2.0f;
        leitores[idLeitor].dividas += multa;
        printf("Multa aplicada: R$ %.2f\n", multa);
    }

    Livro *l = buscarLivroPorId(idLivro);
    if (l) {
        l->disponivel = 1;
    }

    // remover empréstimo ativo do array (compactar)
    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLivro == idLivro) {
            for (int k = i; k < totalEmprestimos - 1; k++) {
                emprestimos[k] = emprestimos[k + 1];
            }
            totalEmprestimos--;
            break;
        }
    }

    printf("Livro devolvido!\n");
    esperarVoltar();
}

void avancarDias(void) {
    int dias;

    printf("\nQuantos dias avancar? ");
    if (scanf("%d", &dias) != 1 || dias < 0) {
        while (getchar() != '\n') {}
        printf("Valor invalido!\n");
        esperarVoltar();
        return;
    }
    getchar();

    for (int i = 0; i < totalEmprestimos; i++) {
        emprestimos[i].dias += dias;
    }

    printf("Tempo avancado!\n");
    esperarVoltar();
}

