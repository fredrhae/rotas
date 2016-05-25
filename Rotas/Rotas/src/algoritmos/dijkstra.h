#ifndef ROTAS_ALGORITMOS_DIJKSTRA_H_
#define ROTAS_ALGORITMOS_DIJKSTRA_H_

#define __DIJKSTRA_BUGADA 1

#include <limits>
#include <vector>
#include "domain/caminho.h"

namespace rotas
{
	namespace algoritmos
	{
		using namespace domain;

		class Dijkstra {
			const double max_distance = std::numeric_limits<double>::infinity();
			int minima_distancia_partindo_da_origem(double distancias[], bool marcador_distancia_encontrada[], size_t numero_cidades);
			double* inicializa_distancias_encontradas(size_t );
		public:
			Dijkstra() {};
			void imprime_caminho_curto_dijkstra(Caminho menor_caminho, Cidade origem);
			Caminho dijkstra_menor_caminho(std::vector<Caminho> distancias, Cidade origem, std::vector<Cidade> cidades);
		};
	} // algoritmos
} // rotas

#endif // ROTAS_ALGORITMOS_DIJKSTRA_H_
