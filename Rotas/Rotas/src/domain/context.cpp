#include "context.h"
#include "domain/cidade.h"

using namespace std;
using namespace rotas::domain;

vector<Cidade> Context::get_cidades_atendidas()
{
	return cidades_atendidas;
}

vector<vector<Rota>> Context::get_matriz_distancias()
{
	return matriz_distancias;
}

void Context::set_matriz_distancias(vector<vector<Rota>> nova_matriz_distancias)
{
	matriz_distancias = nova_matriz_distancias;
}

double Context::get_distancia(Cidade origem, Cidade destino)
{
	return matriz_distancias[origem.get_id()][destino.get_id()].get_distancia();
}




