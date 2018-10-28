#include "../include/parser.h"
#include <iterator>
#include <algorithm>
#include "..include/sbares.h"

int main( int argc, char* argv[]){


	// Verifica se o foram usados os argumentos corretamente
	if( argc < 2 ){
		std::cout << "ERROR! Wrong syntaxe!\n$./bares < input_file > [ output_file ]\n";
		return -1;
	}

	// Cria um vetor dinâmico para armazenar cada linha do arquivo
	sc::vector < std::string > elementos;

	std::string arq_entrada = argv[1];

	std::ifstream file;

	file.open( elementos );

	if( file.fail()){
		std::cout << " error!\nTry again!\n";
		std::exit(1);
	}

	std::string linha;

	while( getline( file, linha )){
		elementos.push_back( linha );
	}

	file.close();


	return 0;
}