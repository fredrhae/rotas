#include "caminho.h"

Cidade Caminho::get_origem()
{
	return distancias_entre_cidades.front().get_destino();
}

Cidade Caminho::get_destino()
{
	return distancias_entre_cidades.back().get_destino();
}