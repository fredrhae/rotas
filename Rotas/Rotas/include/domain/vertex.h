#ifndef ROTAS_DOMAIN_VERTEX_H_
#define ROTAS_DOMAIN_VERTEX_H_

#include <string>

class Vertex {
	std::string label;
public:
	Vertex() {};
	Vertex(std::string label) : label(label) {};
	std::string get_label();
};

#endif // ROTAS_DOMAIN_VERTEX_H_
