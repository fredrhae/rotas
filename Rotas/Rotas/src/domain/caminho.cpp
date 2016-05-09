#include "caminho.h"

Cidade Caminho::get_origem()
{
	return caminho.front().get_destino();
}

Cidade Caminho::get_destino()
{
	return caminho.back().get_destino();
}

double Caminho::get_distancia_total()
{
	double total_distance = 0.0;
	for each (Rota element in caminho)
	{
		total_distance += element.get_distancia();
	}

	return total_distance;
}