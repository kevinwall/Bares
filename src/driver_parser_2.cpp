#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

#include "../include/parser.h"

/*
std::vector<std::string> expressions =
{
    "4 + 03",
    "10",
    "    12    +    4   8",
    "32767 - 32768 + 3",
    "5 + -32766",
    "5 + -32769",
    "12 + 3",
    "-3+-5+-6",
    "12 + 3     -3 + -34 ",
    "+12",
    "1.3 * 4",
    "a + 4",
    "       ",
    "  123 *  548",
    "4 + ",
    "32a23",
    "43 + 54 -   ",
    "(10 * 3) / (4 ^ 5)   % 3"
};
*/

void print_error_msg( const Parser::ResultType & result, std::ofstream &oss )
{
    //std::string error_indicator( str.size()+1, ' ');

    // Have we got a parsing error?
    //error_indicator[result.at_col] = '^';
    switch ( result.type )
    {
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            oss << ">>> Unexpected end of input at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::ILL_FORMED_INTEGER:
            oss << ">>> Ill formed integer at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::MISSING_TERM:
            oss << ">>> Missing <term> at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            oss << ">>> Extraneous symbol after valid expression found at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            oss << ">>> Integer constant out of range beginning at column (" << result.at_col << ")!\n";
            break;
        default:
            oss << ">>> Unhandled error found!\n";
            break;
    }

    //std::cout << "\"" << str << "\"\n";
    //std::cout << " " << error_indicator << std::endl;
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
    // Tentar analisar cada expressão da lista.
    std::ifstream oss(in);
    std::ofstream out(sai);

    while( ! oss.eof() )
    {
        std::string string;

        std::getline(oss, string);

        // Fazer o parsing desta expressão.
        auto result = my_parser.parse( string );
        // Preparar cabeçalho da saida.
       // out << std::setfill('=') << std::setw(80) << "\n";
       // out << std::setfill(' ') << ">>> Parsing \"" << string << "\"\n";
        // Se deu pau, imprimir a mensagem adequada.
        if ( result.type != Parser::ResultType::OK )
            print_error_msg( result, out );
       // else
           // out << ">>> Expression SUCCESSFULLY parsed!\n";

         // Recuperar a lista de tokens.
        auto lista = my_parser.get_tokens();

        /*
        std::cout << ">>> Tokens: { ";
        std::copy( lista.begin(), lista.end(),
                std::ostream_iterator< Token >(std::cout, " ") );
        std::cout << "}\n";
        std::cout << std::endl;
        */
    }



    //std::cout << "\n>>> Normal exiting...\n";

    return EXIT_SUCCESS;
}
