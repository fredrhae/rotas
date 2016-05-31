
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

		vector<Rota> Cidade::get_rotas()
		{
			return rotas;
		}

		double Cidade::get_distancia(Cidade destino) {			
			for (unsigned int i = 0; i < rotas.size(); i++) {
				if (rotas[i].get_id_destino() == destino.get_id()) {
					return rotas[i].get_distancia();
				}
			}
			return 0.0;
		}

	} // domain
} // rotas