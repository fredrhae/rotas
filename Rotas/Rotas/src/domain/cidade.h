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
			vector<Rota> rotas;
			double demanda;
			double capacidade;
			bool compara_distancia(Cidade destino_a, Cidade destino_b);

		public:
			Cidade() {};
			Cidade(string nome, int id) : nome(nome), id(id), id_mediana(-1) {};
			Cidade(string nome, int id, vector<Rota> rotas_possiveis) : 
				nome(nome), id(id), rotas(rotas_possiveis), id_mediana(-1) {};
			
			string get_nome();
			int get_id();
			bool is_mediana();
			void set_mediana(bool mediana);
			int get_id_mediana();
			void set_id_mediana(int id);
			void add_rota(Rota rota);
			void set_rotas(vector<Rota> rotas);
			void set_demanda(double demanda);
			void set_capacidade(double capacidade);
			vector<Rota> get_rotas();
			double get_distancia(Cidade destino);
			double get_demanda();
			double get_capacidade();
			vector<Cidade> ordena_por_distancia(vector<Cidade> destinos);
			Cidade encontra_mais_proxima(vector<Cidade> destinos);
			double diferenca;
			bool aloca_demanda(double demanda);
		};
	} // domain
} // rotas

#endif // ROTAS_DOMAIN_CIDADE_H_
