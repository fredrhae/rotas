// projeto_menor_caminho.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "cli\exibicao.h"

using namespace std;

int main()
{

	Exibicao::exibe_instrucoes();
	cout << "Pressione qualquer tecla para sair.";
	cin.get();

    return 0;
}