#include <algorithm>
#include "cidade.h"
using namespace std;

namespace rotas 
{
	namespace domain 
	{		
		string Cidade::get_nome() {
			return nome;
		}

		int Cidade::get_id() {
			return id;
		}

		bool Cidade::is_mediana() {
			return mediana;
		}

		void Cidade::set_mediana(bool is_mediana) {
			mediana = is_mediana;
		}

		int Cidade::get_id_mediana() {
			return id_mediana;
		}

		void Cidade::set_id_mediana(int id) {
			id_mediana = id;
		}

		void Cidade::add_rota(Rota rota)
		{
			rotas.push_back(rota);
		}

		void Cidade::set_rotas(vector<Rota> novas_rotas)
		{
			rotas.clear();
			rotas = novas_rotas;
		}

		void Cidade::set_demanda(double nova_demanda)
		{
			this->demanda = nova_demanda;
		}

		void Cidade::set_capacidade(double capacidade)
		{
			this->capacidade = capacidade;
		}

		vector<Rota> Cidade::get_rotas()
		{
			return rotas;
		}
		
		double Cidade::get_distancia(Cidade destino) {
			return get_distancia(destino.get_id());
		}

		double Cidade::get_distancia(int id_destino) {
			size_t size_rotas = rotas.size();
			for (size_t i = 0; i < size_rotas; i++) {
				if (rotas[i].get_id_destino() == id_destino) {
					return rotas[i].get_distancia();
				}
			}
			return 0.0;
		}

		double Cidade::get_demanda()
		{
			return demanda;
		}

		double Cidade::get_capacidade()
		{
			return capacidade;
		}

		bool Cidade::compara_distancia(Cidade destino_a, Cidade destino_b) {
			return this->get_distancia(destino_a) < this->get_distancia(destino_b);
		}

		vector<Cidade> Cidade::ordena_por_distancia(vector<Cidade> destinos) {
			vector<Cidade> cidades_em_ordem = vector<Cidade>();

			cidades_em_ordem.push_back(destinos[0]);

			struct _compara_distancia {
				Cidade *origem;
				bool operator() (Cidade a, Cidade b) { return origem->get_distancia(a) < origem->get_distancia(b); }
			} compara_distancia;
			compara_distancia.origem = this;

			for (unsigned int i = 1; i < destinos.size(); i++) {
				auto it = upper_bound(cidades_em_ordem.begin(), cidades_em_ordem.end(), destinos[i], compara_distancia);
				cidades_em_ordem.insert(it, destinos[i]);

			}

			return cidades_em_ordem;
		}

		Cidade* Cidade::encontra_mais_proxima(vector<Cidade> *destinos)
		{
			Cidade *mais_proxima = &(destinos->at(0));
			double menor_distancia = this->get_distancia(*mais_proxima);

			for (unsigned int i = 0; i < destinos->size(); i++) {
				double distancia = this->get_distancia(destinos->at(i));
				if (distancia < menor_distancia) {
					menor_distancia = distancia;
					mais_proxima = &(destinos->at(i));
				}
			}

			return mais_proxima;
		}

		bool Cidade::aloca_demanda(double demanda)
		{
			if (demanda > capacidade) {
				return false;
			}
			else {
				capacidade -= demanda;
				return true;
			}

		}

	} // domain
} // rotas