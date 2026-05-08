# Sistema de Biblioteca (Console) — SLibTech

Projeto em **C** que implementa um sistema de biblioteca em modo console. O usuário realiza **login**, visualiza **animações** e acessa um **menu** com operações como cadastro/listagem de livros, empréstimo, renovação, devolução e avanço de dias.

## Funcionalidades

- **Login** com usuário e senha fixos.
- **Cadastrar livro** (título e autor), respeitando limite máximo.
- **Listar livros** com status:
  - Disponível
  - Emprestado (mostra o nome do leitor)
- **Emprestar livro** para um leitor cadastrado (leitores são pré-definidos no código).
- **Renovar empréstimo** (incrementa dias do empréstimo ativo).
- **Devolver livro**:
  - Marca o livro como disponível novamente
  - Remove o empréstimo ativo do array
  - Aplica multa se o empréstimo estiver com mais de 7 dias
- **Avançar dias**: soma dias informados a todos os empréstimos ativos.

## Credenciais de acesso

No código está definido:
- **Usuário:** `admin`
- **Senha:** `123`

## Como executar / Compilar

O projeto é um programa em C com arquivos separados.

### Opção 1: Compilar com GCC (exemplo)

> Ajuste o caminho caso seu GCC esteja em outro local.

No diretório onde estão os fontes (ex.: `TechLib/SLibTech`), compile incluindo todos os `.c` do módulo.

Exemplo:
```bash
gcc main.c menu.c login.c livro.c leitor.c utils.c animacao.c -o biblioteca
```

Depois execute:
```bash
.
./biblioteca
```

### Opção 2: Compilar com MinGW (Windows)

Se estiver usando MinGW (gcc), o comando é o mesmo do GCC, apenas garantindo que o `gcc` está disponível no PATH.

## Estrutura de arquivos

- `TechLib/SLibTech/main.c`
  - Ponto de entrada (`main`)
  - Fluxo: login → animações → menu
- `TechLib/SLibTech/menu.c`
  - Implementa o menu principal e chama as funções do sistema
- `TechLib/SLibTech/login.c`
  - Validação de login (usuário/senha fixos)
- `TechLib/SLibTech/livro.c`
  - Lógica do domínio de livros e empréstimos
  - Estruturas e arrays globais (livros/emprestimos) e operações
- `TechLib/SLibTech/leitor.c`
  - Lista de leitores pré-definidos no código e listagem
- `TechLib/SLibTech/animacao.c`
  - Animações ASCII (carregamento e folhear)
- `TechLib/SLibTech/utils.c`
  - Função utilitária para ler/validar opções numéricas

### Headers

- `livro.h`, `leitor.h`, `menu.h`, `login.h`, `animacao.h`, `utils.h`

## Observações / Limitações

- O sistema utiliza **arrays fixos** (tamanho definido em headers), por isso existem limites como:
  - `MAX_LIVROS = 100`
  - `MAX_EMPRESTIMOS = 100`
  - `MAX_LEITORES = 5`
- Livros e leitores são iniciados/armazenados em memória (não persiste em arquivo).
- O login é baseado em credenciais fixas no código.

## Licença

Sem licença definida.

