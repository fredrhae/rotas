#ifndef ROTAS_DOMAIN_CIDADE_H_
#define ROTAS_DOMAIN_CIDADE_H_

#include <string>

class Cidade {
	std::string nome;
public:
	Cidade() {};
	Cidade(std::string nome) : nome(nome) {};
	std::string get_nome();
};

#endif // ROTAS_DOMAIN_CIDADE_H_
