#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <ostream>
#include <streambuf>

#include "../include/parser.h"
#include "../include/sbares.h"

void print_error_msg( const Parser::ResultType & result, std::ostream &oss )
{
    switch ( result.type )
    {
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            oss << "Unexpected end of expression at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::ILL_FORMED_INTEGER:
            oss << "Ill formed integer at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::MISSING_TERM:
            oss << "Missing <term> at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            oss << "Extraneous symbol after valid expression found at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            oss << "Integer constant out of range beginning at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::MISSING_ED_SCOPE:
        	oss << "Missing closing ”)” at column (" << result.at_col << ")!\n";
            break;
        default:
            oss << "Unhandled error found!\n";
            break;
    }
}

int main(int argc, char const *argv[])
{
    // Estas são as strings e streams responsáveis por ler as expressões e escrever os resultados.

    std::string in, sai; // Strings que guardam os nomes dos arquivos de entrada e saída.
    std::streambuf * buf; // Ponteiro para o buffer da stream responsável por ligar a saída para o cout ou o arquivo de saída.
    std::ofstream of; // Ofstream para o arquivo de saída.
    std::ifstream oss; // Ifstream para o arquivo de entrada

    if(argc < 3 and argc != 2) // Caso o usuário não tenha digitado os arquivos de entrada e saída.
    {
        std::cout<<"Digite um arquivo de entrada: ";
        std::cin>>in;
        std::cout<<"Digite um arquivo de saída: ";
        std::cin>>sai;

        oss.open(in);
        of.open(sai);

        buf = of.rdbuf();
    }
    else if(argc == 3) // Caso o usuário tenha digitado o nome dos dois arquivos.
    {
        in = argv[1];
        sai = argv[2];

        oss.open(in);
        of.open(sai);

        buf = of.rdbuf();
    }
    else if(argc == 2) // Caso o usuário não tenha digitado o arquivo de saída, utilizados o cout como saída.
    {
        in = argv[1];
        oss.open(in);

        buf = std::cout.rdbuf();
    }
    else // Caso o usuário tenha digitado uma entrada inválida.
    {
        std::cout<<"Entradas inválidas"<<std::endl;
        return 0;
    }
    

    std::ostream out(buf); // Inicializa a ostream responsável por escrever os resultados. Seja no cout ou no arquivo de saída.

    Parser my_parser; // Instancia um parser.

    if(!oss.is_open() or out.bad()) // Caso um dos arquivos não forem abertos.
    {
    	std::cout<<"Erro na abertura dos arquivos, por favor tente novamente com entradas válidas."<<std::endl;
    	return 0;
    }

    while( ! oss.eof() ) // Enquanto não chegamos no fim do arquivo, vamos pegar as expressões.
    {
        std::string string; // String que guarda a expressão atual.

        std::getline(oss, string); // Retiramos uma linha do arquivo (uma expressão).

        // Fazer o parsing desta expressão.
        auto result = my_parser.parse( string );

        if ( result.type != Parser::ResultType::OK ) // Caso a expressão não esteja dentro das normas da gramática impimimos o erro correspondente.
        {
            print_error_msg( result, out );
        }
        else // Caso a expressão esteja dentro das normas, vamos tentar executá-la
        {
            std::vector<Token> lista = my_parser.get_tokens(); // Recebemos o vetor de tokens gerados pelo tokenizer (dentro do parser).
            std::vector<Token> lista_postfixada = infix_to_postfix( lista ); // Recebemos o vetor de tokens posfixado, baseado no vetor de tokens gerado pelo tokenizer.
            value_type evaluate; // Resultado da expressão.
            bool div_zero = false; // Flag para caso haja visisão por zero ou o resultado ultrapasse o range, não imprimimos nada no arquivo fora o erro.
            try{  evaluate = evaluate_postfix( lista_postfixada ); // Tentamos solucionar a expessão.

            }
            catch(std::runtime_error) // Caso haja divisão por zero imprimimos o erro correspondente.
            { 
                out << "Division by zero!\n";
                div_zero = true;
            }
            catch(std::out_of_range) // Caso o resultado ultrapasse o range especificado.
            {
            	out << "Numeric overflow error!\n";
            	div_zero = true;
            }


            if(div_zero == false) // Caso o resultado esteja dentro das normas, jogamos ele para a saída.
            {
            	out << evaluate << std::endl;
            }
            

        }   
    }

    // Fechando corretamente os arquivos de entrada e saída.
    oss.close();
    of.close();

    //std::cout<<"Expressões solucionadas e gravadas no arquivo "<<sai<<std::endl;

    return EXIT_SUCCESS;
}
