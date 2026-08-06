# Compiladores — 2026.2

Material da disciplina de Compiladores.

**Professor:** João Marcelo Uchôa de Alencar
**Campus da UFC em Quixadá**
**Período:** 10/08/2026 a 11/12/2026 — segundas e quartas-feiras (33 encontros)

## Livro Texto

**LOUDEN, Kenneth C.** *Compiladores: Princípios e Práticas.* São Paulo: Thomson Learning, 2004.

### Bibliografia Auxiliar

- AHO, A. V.; LAM, M. S.; SETHI, R.; ULLMAN, J. D. *Compiladores: Princípios, Técnicas e Ferramentas* (o "Livro do Dragão"), 2ª ed.
- APPEL, A. W. *Modern Compiler Implementation in C.*
- LEVINE, J. *flex & bison.* O'Reilly.

## Conteúdo do Repositório

### `slides/` — slides das aulas (LaTeX/Beamer)

| Pasta | Assunto | Cap. Louden | Slides |
|-------|---------|-------------|--------|
| `01` | Apresentação da disciplina | — | 12 |
| `02` | Introdução | 1 | 34 |
| `03` | Varredura (análise léxica) | 2 | 67 |
| `04` | Gramáticas livres de contexto e análise sintática | 3 | 39 |
| `05` | Análise sintática descendente | 4 | 59 |
| `06` | Análise sintática ascendente | 5 | 77 |
| `07` | Análise semântica | 6 | 103 |
| `08` | Ambientes de execução | 7 | 47 |

> O capítulo 8 do Louden (Geração de Código) ainda não tem slides no repositório.

#### Compilando os slides

Os slides usam o pacote `minted`, que exige `-shell-escape` e o `pygments` instalado.

**macOS (Homebrew + MacTeX):**

```bash
brew install --cask mactex          # ou mactex-no-gui
brew install pygments
cd slides/01
pdflatex -shell-escape 01.tex
pdflatex -shell-escape 01.tex       # segunda passada: numeração total de slides
```

**Ubuntu/Debian:**

```bash
sudo apt install texlive-latex-base texlive-lang-portuguese texlive-latex-extra python3-pygments
```

Testado em macOS 15 (Darwin 25.5) com TeX Live 2026 e Pygments via Homebrew: os 8 capítulos
compilam sem erros (apenas avisos cosméticos de substituição de fonte).

### `src/` — código de exemplo em Lex/Yacc/C

Cada pasta tem instruções próprias de compilação.

| Pasta | Uso |
|-------|-----|
| `lex/` | exemplos de analisador léxico com Flex |
| `yacc/` | exemplos de analisador sintático com Bison |
| `posfix/`, `aritmetica/`, `calculator/` | tradutores e calculadoras (expressões) |
| `tiny/`, `loucomp/` | compilador da linguagem TINY (Louden) |
| `ambientes/` | exemplos de ambientes de execução |
| `dragon-front-source/` | código do Livro do Dragão |
| `julia/` | exemplos auxiliares |

## Distribuição das Aulas

**Feriados no período (segundas/quartas):** 07/09 (Independência), 12/10 (N. Sra. Aparecida),
02/11 (Finados).

### Unidade I — Introdução e Análise Léxica

| # | Data | Assunto | Material |
|---|------|---------|----------|
| 1 | seg 10/08 | Apresentação da disciplina, ferramentas e avaliação | `slides/01` |
| 2 | qua 12/08 | Introdução: histórico, programas relacionados a compiladores | `slides/02` |
| 3 | seg 17/08 | Fases da compilação, estruturas de dados, a linguagem TINY | `slides/02` |
| 4 | qua 19/08 | O processo de varredura: marcas e registro de marcas | `slides/03` |
| 5 | seg 24/08 | Expressões regulares | `slides/03` |
| 6 | qua 26/08 | Autômatos finitos determinísticos (DFA) | `slides/03` |
| 7 | seg 31/08 | Autômatos não determinísticos (NFA), Thompson, subconjuntos | `slides/03` |
| 8 | qua 02/09 | Laboratório: Flex/Lex I | `src/lex` |
| — | seg 07/09 | *Feriado — Independência* | |
| 9 | qua 09/09 | Laboratório: Flex/Lex II — o scanner do TINY | `src/tiny` |
| 10 | seg 14/09 | Revisão da Unidade I / resolução de exercícios | |
| 11 | qua 16/09 | **AP1 — Prova escrita (caps. 1–2)** | |

### Unidade II — Análise Sintática

| # | Data | Assunto | Material |
|---|------|---------|----------|
| 12 | seg 21/09 | Gramáticas livres de contexto, derivações | `slides/04` |
| 13 | qua 23/09 | Árvores de análise sintática e árvores sintáticas abstratas | `slides/04` |
| 14 | seg 28/09 | Ambigüidade, else pendente, precedência; EBNF | `slides/04` |
| 15 | qua 30/09 | Análise descendente recursiva | `slides/05` |
| 16 | seg 05/10 | Análise LL(1): tabela e algoritmo | `slides/05` |
| 17 | qua 07/10 | Conjuntos First e Follow | `slides/05` |
| — | seg 12/10 | *Feriado — N. Sra. Aparecida* | |
| 18 | qua 14/10 | Remoção de recursão à esquerda, fatoração, recuperação de erros | `slides/05` |
| 19 | seg 19/10 | Análise ascendente: visão geral e LR(0) | `slides/06` |
| 20 | qua 21/10 | Análise SLR(1) | `slides/06` |
| 21 | seg 26/10 | Análise LR(1) e LALR(1) | `slides/06` |
| 22 | qua 28/10 | Laboratório: Yacc/Bison | `src/yacc`, `src/calculator` |
| — | seg 02/11 | *Feriado — Finados* | |
| 23 | qua 04/11 | **AP2 — Prova escrita (caps. 3–5)** | |

### Unidade III — Análise Semântica e Ambientes de Execução

| # | Data | Assunto | Material |
|---|------|---------|----------|
| 24 | seg 09/11 | Atributos e gramáticas de atributos | `slides/07` |
| 25 | qua 11/11 | Grafos de dependência e algoritmos de computação de atributos | `slides/07` |
| 26 | seg 16/11 | Tabela de símbolos | `slides/07` |
| 27 | qua 18/11 | Verificação de tipos | `slides/07` |
| 28 | seg 23/11 | Organização da memória e registros de ativação | `slides/08` |
| 29 | qua 25/11 | Ambientes estáticos e ambientes em pilha | `slides/08`, `src/ambientes` |
| 30 | seg 30/11 | Ambientes dinâmicos, heap, passagem de parâmetros | `slides/08` |
| 31 | qua 02/12 | Geração de código: código intermediário e a máquina TM | Louden cap. 8 |
| 32 | seg 07/12 | **AP3 — Prova escrita (caps. 6–8)** | |
| 33 | qua 09/12 | Apresentação dos trabalhos finais | |

> O semestre encerra em 11/12/2026 (sexta-feira); a última aula em segunda/quarta é 09/12.

## Avaliação

- **AP1, AP2, AP3** — provas escritas ao final de cada unidade.
- **Trabalho** — implementação incremental de um compilador, entregue e apresentado ao
  final do semestre. As etapas acompanham as unidades: analisador léxico (Unid. I),
  analisador sintático (Unid. II) e análise semântica (Unid. III).
