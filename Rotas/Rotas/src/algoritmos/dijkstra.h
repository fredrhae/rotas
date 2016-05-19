#ifndef ROTAS_ALGORITMOS_H_
#define ROTAS_ALGORITMOS_H_

#define kCidades 9

#include <limits>;
#include <vector>;
#include "caminho.h"

class Dijkstra {
		const double max_distance = std::numeric_limits<double>::infinity();
		Caminho caminho_distancia_minima;
		int minima_distancia_partindo_da_origem(double distancias[], bool marcador_distancia_encontrada[], int numero_cidades);
		double* inicializa_distancias_encontradas(int);
	public:
		Dijkstra(){};
		void imprime_caminho_curto_dijkstra(double dist[], int n);
		void dijkstra_menor_caminho(std::vector<Caminho> distancias, Cidade origem);
};

#endif // ROTAS_ALGORITMOS_H_
