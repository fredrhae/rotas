#ifndef _ROTAS_DOMAIN_CONTEXT_H_
#define _ROTAS_DOMAIN_CONTEXT_H_

#include <vector>
#include "domain/cidade.h"
#include "domain/rota.h"

namespace rotas 
{
	namespace domain
	{
		using namespace rotas::domain;
		class Context{
				std::vector<std::vector<Rota>> matriz_distancias;
				std::vector<Cidade> cidades_atendidas;
			public:
				Context() {};
				Context(std::vector<Cidade> cidades_atendidas_entrada,
						std::vector<std::vector<Rota>> matriz_distancias_entrada):
							cidades_atendidas(cidades_atendidas_entrada),
							matriz_distancias(matriz_distancias_entrada){};
				std::vector<Cidade> get_cidades_atendidas();
				std::vector<std::vector<Rota>> get_matriz_distancias();
				void set_matriz_distancias(std::vector<std::vector<Rota>> nova_matriz_distancias);
				double get_distancia(Cidade origem, Cidade destino);
				double get_distancia(int id_cidade_origem, int id_cidade_destino);
		};
	}
}

#endif// _ROTAS_DOMAIN_CONTEXT_H_
