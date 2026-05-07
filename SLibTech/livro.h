#ifndef LIVROS_H
#define LIVROS_H

#define MAX_LIVROS 100
#define MAX_EMPRESTIMOS 100

typedef struct {
    int id;
    char titulo[50];
    char autor[50];
    int disponivel; // 1 = disponivel, 0 = emprestado
} Livro;

typedef struct {
    int idLivro;
    int idLeitor; // índice no array `leitores[]`
    int dias;
} Emprestimo;

extern Livro livros[MAX_LIVROS];
extern int totalLivros;

extern Emprestimo emprestimos[MAX_EMPRESTIMOS];
extern int totalEmprestimos;

void listarLivros();
void cadastrarLivro();
void emprestarLivro();
void renovarEmprestimo();
void devolucao();
void avancarDias();

#endif





