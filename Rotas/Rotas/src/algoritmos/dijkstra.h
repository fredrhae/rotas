#ifndef ROTAS_ALGORITMOS_H_
#define ROTAS_ALGORITMOS_H_

#define kCidades 9

#include <limits>;
#include <vector>;
#include "domain/caminho.h"

class Dijkstra {
		const double max_distance = std::numeric_limits<double>::infinity();
		int minima_distancia_partindo_da_origem(double distancias[], bool marcador_distancia_encontrada[], int numero_cidades);
		double* inicializa_distancias_encontradas(int);
	public:
		Dijkstra(){};
		void imprime_caminho_curto_dijkstra(Caminho menor_caminho);
		Caminho dijkstra_menor_caminho(std::vector<Caminho> distancias, Cidade origem, std::vector<Cidade> cidades);
};

#endif // ROTAS_ALGORITMOS_H_
