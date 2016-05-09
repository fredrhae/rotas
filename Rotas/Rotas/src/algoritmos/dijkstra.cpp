#include "dijkstra.h"


// Uma funcao auxiliar que acha a cidade com menor distância de um 
// conjunto de cidades ainda não inclusos na rota
double Dijkstra::minima_distancia_partindo_da_origem(double distancias[], bool sptSet[])
{
	// Initialize min value
	double min = Dijkstra::max_distance, min_index;

	for (int v = 0; v < kCidades; v++)
	{
		if (sptSet[v] == false && distancias[v] <= min)
		{
			min = distancias[v];
			min_index = v;
		}
	}
	return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void Dijkstra::imprime_caminho_curto_dijkstra(double dist[], int n)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < kCidades; i++)
		printf("%d \t\t %f\n", i, dist[i]);
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void Dijkstra::dijkstra_menor_caminho(double graph[kCidades][kCidades], int origem)
{
	
	double distancias_encontradas[kCidades];     // The output array.  dist[i] will hold the shortest
					 // distance from src to i

	bool sptSet[kCidades]; // sptSet[i] will true if vertex i is included in shortest
					// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < kCidades; i++)
	{
		distancias_encontradas[i] = max_distance;
		sptSet[i] = false;

	}
	// Distance of source vertex from itself is always 0
	distancias_encontradas[origem] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < kCidades - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minima_distancia_partindo_da_origem(distancias_encontradas, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < kCidades; v++)
		{
			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && distancias_encontradas[u] != max_distance
				&& distancias_encontradas[u] + graph[u][v] < distancias_encontradas[v])
				distancias_encontradas[v] = distancias_encontradas[u] + graph[u][v];
		}
	}

	// print the constructed distance array
	imprime_caminho_curto_dijkstra(distancias_encontradas, kCidades);
}