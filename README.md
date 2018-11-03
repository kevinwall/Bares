# Introdu��o: #
 Este projeto implementa o algor�timo BARES (Basic ARithmetic Expression Evaluator based on Stacks) que tem como objetivo avaliar uma express�o matem�tica baseada em uma gram�tica e solucion�-la.

# Implementa��o: #
 Para realizar implementar esse projeto foram utilizadas as seguintes ferramentas:

- Parser/Tokenizer: A fun��o do Parser � avaliar se a express�o � v�lida segundo as regras da gram�tica, j� o Tokenizer converte a express�o em uma lista de tokens que ser� utilizada para solucionar a express�o. Ambos os processos funcionam juntos.

- Gram�tica: A gram�tica representa os tipos de express�es aritim�ticas e seus componentes. Esta � utilizada para descrever uma regra para o parser avaliar as express�es.

# A Gram�tica: #

A gram�tica segue a seguinte especifica��o:

    <expr>            := <term>,{ ("+"|"-"|"*"|"/"|"%"|"^"),<term> };
    <term>            := "(",<expr>,")" | <integer>;
    <integer>         := "0" | {["-"]},<natural_number>;
    <natural_number>  := <digit_excl_zero>,{<digit>};
    <digit_excl_zero> := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
    <digit>           := "0"| <digit_excl_zero>;

Essa gram�tica _aceita_ express�es como:

* "23 + 43 - 0   + -124 - 21"
* " 21"
* "-21 +     -18"
* " -54"
* "-21 - 23 + 1234"
* "(30 + -5) ^ 4"
* "------5 + 6"

E _rejeita_ express�es como: 

* "01 + 3"
* " - 3 + 4"
* "2 +"
* "  "
* "+2 + 5"
* "-02 + 4"

# Compila��o e execuc�o: #

Para compilar o projeto basta digitar o comando <br/>

**make** <br/>

Na pasta principal do reposit�rio e para excutar basta digitar <br/>

**./bares arquivo-de-entrada [arquivo-de-sa�da]**  <br/>

Caso o usu�rio n�o digite nenhum arquivo de sa�da, os resultados ser�o mostrados via cout. <br/>

Caso nenhum arquivo seja digitado, o usu�rio entrara com os nomes dos arquivos de entrada e sa�da 
dentro do algor�timo. <br/>

E por fim, caso o usu�rio entre com mais par�metros do que os especificados, a execu��o � parada.

# Autoria #

Todos os c�digos aqui implementados foram desenvolvidos por [Kevin Wallacy de Souza Maciel](https://github.com/kevinwall) (Email de contato: <kevinwall@ufrn.edu.br>) e [Giovanne da Silva Santos](https://github.com/GSDante) (Email de contato: <giovannedssantos@gmail.com>) 

&copy; IMD/UFRN 2018-2019
