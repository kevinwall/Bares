#ifndef SBARES_H_
#define SBARES_H_

#include <iostream>  // cout, endl
#include <stack>     // stack
#include <string>    // string
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error
#include <vector>    // std::vector
#include "token.h"

//=== Aliases
using value_type = long int; //!< Type we operate on.
using symbol = Token; //!< A symbol in this implementation is just a char.

bool is_operator( symbol s );

bool is_operand( symbol s );

bool is_opening_scope( symbol s );

bool is_closing_scope( symbol s );

bool is_right_association( symbol op );

std::string infix_to_postfix( std::string );

value_type char2integer( char c );

value_type evaluate_postfix( std::string );

short get_precedence( symbol op );

bool has_higher_or_eq_precedence( symbol op1 , symbol op2 );

value_type execute_operator( value_type v1, value_type v2, symbol op );

std::vector<Token> infix_to_postfix( std::vector<Token>  infix );

value_type evaluate_postfix( std::vector<Token> postfix );


#endif