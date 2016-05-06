#ifndef ROTAS_DOMAIN_EDGE_H_
#define ROTAS_DOMAIN_EDGE_H_

#include "vertex.h"

class Edge {
	Vertex source;
	Vertex destination;
	double distance;
public:
	Edge() {};
	Edge(Vertex src, Vertex dst, double distance) : source(src), destination(dst), 
		distance(distance){};
	Vertex get_source();
	Vertex get_destination();
	double get_distance();
};

#endif // ROTAS_DOMAIN_EDGE_H_
