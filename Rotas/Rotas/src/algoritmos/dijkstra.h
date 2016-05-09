#ifndef ROTAS_ALGORITMOS_H_
#define ROTAS_ALGORITMOS_H_

#include <limits>;
#include <vector>;
#include "caminho.h"

#define kCidades 9

class Dijkstra {
		const double max_distance = std::numeric_limits<double>::infinity();
		Caminho caminho_distancia_minima;
		double minima_distancia_partindo_da_origem(double dist[], bool sptSet[]);
	public:
		Dijkstra(){};
		void imprime_caminho_curto_dijkstra(double dist[], int n);
		void dijkstra_menor_caminho(double graph[kCidades][kCidades], int origem);
};

#endif // ROTAS_ALGORITMOS_H_
