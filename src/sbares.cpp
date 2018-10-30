/*!
 * Converts an arithmetic expression in infix notation into postfix
 * representation. After the convertion is successfyly done, the
 * program evaluates the expression based on stacks and queues.
 *
 * Input Postfix expression must be in a desired format.
 * Operands and operator, **both must be single character** (all positives).
 * Only '+', '-', '*', '%', '/', and '^' (for exponentiation) operators are expected;
 * Any other character is just ignored.
 */


#include "../include/sbares.h"



// Simple helper functions that identify the incoming symbol.
bool is_operator( Token s )
{   return s.type == Token::token_t::OPERATOR;   }

bool is_operand( Token s )
{   return s.type == Token::token_t::OPERAND ;   }

bool is_opening_scope( Token s )
{ return s.type == Token::token_t::OP_SCOPE ; }

bool is_closing_scope( Token s )
{ return s.type == Token::token_t::ED_SCOPE ; }

/// Check the operand's type of association.
bool is_right_association( Token op )
{ return op.value[0] == '^'; }

/// Converts a expression in infix notation to a corresponding profix representation.
std::string infix_to_postfix( std::string );

/// Converts a char (1-digit operand) into an integer.
value_type char2integer( char c )
{ return c - '0'; }

/// Change an infix expression into its corresponding postfix representation.
value_type evaluate_postfix( std::vector<Token> & );

/// Returns the precedence value (number) associated with an operator.
short get_precedence( Token op )
{
    switch( op.value )
    {
        case '^' : return 3;
        case '*' :
        case '/' :
        case '%' : return 2;
        case '+' :
        case '-' : return 1;
        case '(' : return 0;
        default  : assert( false );  return -1;
    }
}

/// Determines whether the first operator is >= than the second operator.
bool has_higher_or_eq_precedence( std::string op1 , std::string op2 )
{
    // pega os valores numericos correspondentes aas precedencias.
    int p_op1 = get_precedence( op1 );
    int p_op2 = get_precedence( op2 );

    if ( p_op1 > p_op2 )
    {
        return true;
    }
    else if ( p_op1 < p_op2 )
    {
        return false;
    }
    else // p_op1 == p_op2 
    {
        // exceção a regra, que acontece com associacao direita-esquerda.
        if ( is_right_association( op1 ) ) return false;
        // regra normal.
        return true;
    }
}

/// Execute the binary operator on two operands and return the result.
value_type execute_operator( value_type v1, value_type v2, Token op )
{
    switch( op.type )
    {
        case '^':  return pow( v1,v2 );
        case '*':  return v1*v2;
        case '/':  if ( v2 == 0 ) throw std::runtime_error( "divisao por zero" );
                   return v1/v2;
        case '%':  if ( v2 == 0 ) throw std::runtime_error( "divisao por zero" );
                   return v1%v2;
        case '+': return v1+v2;
        case '-': return v1-v2;
        default: throw std::runtime_error( "undefined operator" );
    }
}

int main( void )
{
    // A expression is a queue of sysmbols (chars).
    std::vector< std::string > exps {
        "4/(5^2)+(6^2^3)",
        "1+ 3 * ( 4 + 8 * 3 ^7)",
        "2*2*3",
        "2^2^3" } ;

    for ( const auto& e : exps )
    {
        auto postfix = infix_to_postfix( e );
        std::cout << ">>> Input (infix)    = " << e << "\n";
        std::cout << ">>> Output (postfix) = " << postfix << "\n";

        auto result = evaluate_postfix( postfix );
        std::cout << ">>> Result is: " << result << std::endl;
    }

    std::cout << "\n>>> Normal exiting...\n";
    return EXIT_SUCCESS;
}

std::string infix_to_postfix( std::vector< Token> & infix )
{
    std::string postfix(""); // resultado da conversao.
    std::stack< Token > s; // pilha de ajuda na conversao.

    // Percorrer a entrada, para processar cada item/token/caractere
    for( auto c : infix )
    {
        //std::cout << "\n>>> Infix: \"" << infix << "\"\n";
        //std::cout << ">>> Processando o \'" << c << "\'\n";
        // Operando vai direto pra saida.
        if( is_operand( c ) )
            postfix += c;
        else if( is_opening_scope(c) )
            s.push( c ); // '(' entra na pilha de espera em cima de quem estiver por la.
        else if( is_closing_scope(c) )
        {
            // desempilhe ateh achar o escopo de abertura correspondente.
            while( not is_opening_scope( s.top() ) )
            {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // Lembre de descartar o '(' que estah no topo da pilha.
        }
        else if ( is_operator( c ) ) // + - ^ *...
        {
            // Desempilhar as operaçoes em espera que são iguais ou superiores
            // em prioridade (com excecao da associacao direita-esquerda).
            while( not s.empty() and has_higher_or_eq_precedence( s.top(), c ) ) // s.top() >= c
            {
                postfix += s.top();
                s.pop();
            }

            // A operacao que chegar, sempre tem que esperar.
            s.push( c );
        }
        else // qualquer coisa que não seja o que eu quero. Ex.: espaço em branco.
        {
            // ignoro, não faço nada.
        }
        //std::cout << ">>> Posfix: \"" << postfix << "\"\n";
    }

    // Lembre-se de descarregar as operacoes pendentes da pilha.
    while( not s.empty() )
    {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

value_type evaluate_postfix( std::string postfix )
{
    std::stack< value_type > s;

    for( auto c : postfix )
    {
        if ( is_operand( c ) )
            s.push( char2integer( c ) );
        else if ( is_operator( c ) )
        {
            value_type op2 = s.top(); s.pop();
            value_type op1 = s.top(); s.pop();
            auto result = execute_operator( op1, op2, c ); // ( 2, 9, '*' )
            s.push( result );
        }
        else assert( false );
    }

    return s.top();
}
