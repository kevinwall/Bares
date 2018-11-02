#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

#include "../include/parser.h"
#include "../include/sbares.h"

void print_error_msg( const Parser::ResultType & result, std::ofstream &oss )
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
    std::string in, sai;

    if(argc != 3)
    {
        std::cout<<"Digite um arquivo de entrada: ";
        std::cin>>in;
        std::cout<<"Digite um arquivo de saída: ";
        std::cin>>sai;
    }
    else
    {
        in = argv[1];
        sai = argv[2];
    }
    

    Parser my_parser; // Instancia um parser.

    // Inicializa as stream que vão ler/escrever nos arquivos de entrada e saída respectivamente.
    std::ifstream oss(in);
    std::ofstream out(sai);

    if(!oss.is_open() or !out.is_open())
    {
    	std::cout<<"Erro na abertura dos arquivos, por favor tente novamente com entradas válidas."<<std::endl;
    	return 0;
    }

    while( ! oss.eof() )
    {
        std::string string;

        std::getline(oss, string);

        // Fazer o parsing desta expressão.
        auto result = my_parser.parse( string );

        if ( result.type != Parser::ResultType::OK )
        {
            print_error_msg( result, out );
        }
        else
        {
            std::vector<Token> lista = my_parser.get_tokens();
            std::vector<Token> lista_postfixada = infix_to_postfix( lista );
            value_type evaluate;
            bool div_zero = false;
            try{  evaluate = evaluate_postfix( lista_postfixada );

            }
            catch(std::runtime_error)
            { 
                out << "Division by zero!\n";
                div_zero = true;
            }
            catch(std::out_of_range)
            {
            	out << "Numeric overflow error!\n";
            	div_zero = true;
            }


            if(div_zero == false)
            {
            	out << evaluate << std::endl;
            }
            

        }   
    }

    oss.close();
    out.close();

    std::cout<<"Expressões solucionadas e gravadas no arquivo "<<sai<<std::endl;

    return EXIT_SUCCESS;
}
