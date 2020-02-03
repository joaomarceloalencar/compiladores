
# Compiladores 

Material Disciplina de Compiladores
Professor João Marcelo Uchôa de Alencar
Campus da UFC em Quixadá

## Conteúdo

### src/ - código de exemplo usando _Lex/Yacc/C_.
São vários exemplos, cada um com instruções de compilação específicas dentro de cada pasta.

### slides/ - pasta com os _slides_ das aulas. 
Considerando uma máquina com Ubuntu 18.04, é preciso instalar os seguintes pacotes:

```bash
$ sudo apt install texlive-latex-base texlive-lang-portuguese texlive-latex-extra python-pygments
```

Em seguida, para cada capítulo, construa o pdf. Por exemplo, para o capítulo 01:

```bash
$ cd compiladores/slides/01
$ pdflatex -shell-escape 01.tex
```
