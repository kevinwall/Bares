# Introdução: #
 Este projeto implementa o algorítimo BARES (Basic ARithmetic Expression Evaluator based on Stacks) que tem como objetivo avaliar uma expressão matemática baseada em uma gramática e solucioná-la.

# Implementação: #
 Para realizar implementar esse projeto foram utilizadas as seguintes ferramentas:

- Parser/Tokenizer: A função do Parser é avaliar se a expressão é válida segundo as regras da gramática, já o Tokenizer converte a expressão em uma lista de tokens que será utilizada para solucionar a expressão. Ambos os processos funcionam juntos.

- Gramática: A gramática representa os tipos de expressões aritiméticas e seus componentes. Esta é utilizada para descrever uma regra para o parser avaliar as expressões.

# A Gramática: #

A gramática segue a seguinte especificação:

    <expr>            := <term>,{ ("+"|"-"|"*"|"/"|"%"|"^"),<term> };
    <term>            := "(",<expr>,")" | <integer>;
    <integer>         := "0" | {["-"]},<natural_number>;
    <natural_number>  := <digit_excl_zero>,{<digit>};
    <digit_excl_zero> := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
    <digit>           := "0"| <digit_excl_zero>;

Essa gramática _aceita_ expressões como:

* "23 + 43 - 0   + -124 - 21"
* " 21"
* "-21 +     -18"
* " -54"
* "-21 - 23 + 1234"
* "(30 + -5) ^ 4"
* "------5 + 6"

E _rejeita_ expressões como: 

* "01 + 3"
* " - 3 + 4"
* "2 +"
* "  "
* "+2 + 5"
* "-02 + 4"

# Compilação e execucão: #

Para compilar o projeto basta digitar o comando <br/>

** make <br/>

Na pasta principal do repositório e para excutar basta digitar <br/>

** ./bares arquivo_de_entrada arquivo_de_saída <br/>

Após isso, as soluções e erros se encontrarão no arquivo de saída.

# Autoria #

Todos os códigos aqui implementados foram desenvolvidos por [Kevin Wallacy de Souza Maciel](https://github.com/kevinwall) (Email de contato: <kevinwall@ufrn.edu.br>) e [Giovanne da Silva Santos](https://github.com/GSDante) (Email de contato: <giovannedssantos@gmail.com>) 

&copy; IMD/UFRN 2018-2019
