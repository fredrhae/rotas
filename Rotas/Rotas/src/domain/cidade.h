#ifndef ROTAS_DOMAIN_CIDADE_H_
#define ROTAS_DOMAIN_CIDADE_H_

#include <string>

class Cidade {
	std::string nome;
	int id;
public:
	Cidade() {};
	Cidade(std::string nome, int id) : nome(nome), id(id) {};
	std::string get_nome();
	int get_id();
};

#endif // ROTAS_DOMAIN_CIDADE_H_
