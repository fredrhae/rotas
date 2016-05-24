#ifndef ROTAS_DOMAIN_CIDADE_H_
#define ROTAS_DOMAIN_CIDADE_H_

#include <string>
#include <vector>
#include "rota.h"

using namespace std;

namespace rotas {
	namespace domain {
		class Cidade 
		{
			string nome;
			int id;
			bool mediana = false;
			int id_mediana;
			vector<Rota> rotas_possiveis;

		public:
			Cidade() {};
			Cidade(string nome, int id) : nome(nome), id(id) {};
			Cidade(string nome, int id, vector<Rota> rotas_possiveis) : 
				nome(nome), id(id), rotas_possiveis(rotas_possiveis) {};
			
			string get_nome();
			int get_id();
			bool is_mediana();
			void set_mediana(bool mediana);
			int get_id_mediana();
			void set_id_mediana(int id);
			void add_rota(Rota rota);
			void set_rotas(vector<Rota> rotas);
		};
	} // domain
} // rotas

#endif // ROTAS_DOMAIN_CIDADE_H_
