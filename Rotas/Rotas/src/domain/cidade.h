#ifndef ROTAS_DOMAIN_CIDADE_H_
#define ROTAS_DOMAIN_CIDADE_H_

#include <string>

class Cidade {
	std::string nome;
	int id;
	bool mediana;
	int id_mediana;

public:
	Cidade() {};
	Cidade(std::string nome, int id) : nome(nome), id(id), id_mediana(-1) {};
	std::string get_nome();
	int get_id();
	bool is_mediana();
	void set_mediana(bool mediana);
	int get_id_mediana();
	void set_id_mediana(int id);
};

#endif // ROTAS_DOMAIN_CIDADE_H_
