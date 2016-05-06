#ifndef ROTAS_DOMAIN_PATH_H_
#define ROTAS_DOMAIN_PATH_H_

#include "domain\edge.h"
#include <vector>

class Path {
	std::vector<Edge> route;
	double total_distance;
public:
	Path() {};
	Path(std::vector<Edge> route) : route(route){};
	Vertex get_source();
	Vertex get_destination();
	double get_total_distance();
};

#endif // ROTAS_DOMAIN_PATH_H_
