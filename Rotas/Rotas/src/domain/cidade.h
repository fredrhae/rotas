#ifndef ROTAS_DOMAIN_CIDADE_H_
#define ROTAS_DOMAIN_CIDADE_H_

#include <string>

namespace rotas {
	namespace domain {
		class Cidade 
		{
			std::string nome;
			int id;
			bool mediana;
			int id_mediana;

		public:
			Cidade() {};
			Cidade(std::string nome, int id) : nome(nome), id(id), id_mediana(-1), mediana(false) {};
			std::string get_nome();
			int get_id();
			bool is_mediana();
			void set_mediana(bool mediana);
			int get_id_mediana();
			void set_id_mediana(int id);
		};
	} // domain
} // rotas

#endif // ROTAS_DOMAIN_CIDADE_H_
