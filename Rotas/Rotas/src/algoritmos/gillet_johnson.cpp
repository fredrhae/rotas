#include "gillet_johnson.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// --------- TODO: não está contando com a capacidade de cada ponto de atendimento --------
namespace rotas
{
	namespace algoritmos
	{	

		bool compara_diferencas(Cidade *a, Cidade *b) {
			return a->diferenca > b->diferenca;
		}
		
		vector<Cidade*> encontra_lista_designacao(vector<Cidade> &pontos_demanda, vector<Cidade> &pontos_atendimento) {
			vector<Cidade*> lista_designacao = vector<Cidade*>();

			if (pontos_atendimento.size() == 1) {
				lista_designacao.push_back(&(pontos_atendimento.front()));
				return lista_designacao;
			}

			for (unsigned int i = 0; i < pontos_demanda.size(); i++) {
				Cidade *ponto_demanda = &pontos_demanda[i];
				//Passo 1: Encontrar L1 e L2, as duas medianas mais próximas
				//vector<Cidade*>* Cidade::ordena_por_distancia(vector<Cidade> *destinos)
				vector<Cidade*> *pontos_atendimento_ordenados = ponto_demanda->ordena_por_distancia(&pontos_atendimento);
				//L1 -> cidades_ordenadas[0]
				//L2 -> cidades_ordenadas[1]

				//Passo 2: calcular a razão r = |L2| - |L1|
				double d1 = ponto_demanda->get_distancia(pontos_atendimento_ordenados->at(0));
				double d2 = ponto_demanda->get_distancia(pontos_atendimento_ordenados->at(1));
				ponto_demanda->diferenca = d2 - d1;

				//Passo 3: preencher a lista de designação
				lista_designacao.push_back(ponto_demanda);
			}
			return lista_designacao;
		}

		void remove_cidade(vector<Cidade> &cidades, Cidade *to_remove) {
			for (unsigned int i = 0; i < cidades.size(); i++) {
				if (cidades[i].get_id() == to_remove->get_id()) {
					cidades.erase(cidades.begin() + i);
					return;
				}
			}
		}

		void GilletJohnson::encontra_medianas(vector<Cidade> & cidades) {

			vector<Cidade> pontos_atendimento = vector<Cidade>();
			vector<Cidade> pontos_demanda = vector<Cidade>();
			for (unsigned int i = 0; i < cidades.size(); i++) {
				if (cidades[i].is_mediana()) {
					pontos_atendimento.push_back(cidades[i]);
				}
				else {
					pontos_demanda.push_back(cidades[i]);
				}
			}

			switch (pontos_atendimento.size()) {
			case 0:
				//Se não encontrou nenhum ponto de atendimento, o algoritmo não faz sentido
				//TODO disparar exceção
				return;
			case 1:
				//Se encontrou um ponto de atendimento, ele atende a todos os pontos de demanda
				for (unsigned int i = 0; i < cidades.size(); i++) {
					cidades[i].set_id_mediana(pontos_atendimento.front().get_id());
				}
				return;				
			default:
				bool flag_demanda_estourada;
				vector<Cidade*> lista_designacao;
				
				do {
					flag_demanda_estourada = false;
					// Passos 1-3: Encontrar a lista de designação
					lista_designacao = encontra_lista_designacao(pontos_demanda, pontos_atendimento);

					//Passo 4: organizar a lista por ordem decrescente de d
					sort(lista_designacao.begin(), lista_designacao.end(), compara_diferencas);

					//Passo 5: Designar os pontos de demanda ao ponto de atendimento mais próximo
					for (unsigned i = 0; i < lista_designacao.size(); i++) {
						Cidade* ponto_atendimento_mais_prox = lista_designacao[i]->encontra_mais_proxima(&pontos_atendimento);
						double capacidade = ponto_atendimento_mais_prox->get_capacidade();
						if (capacidade >= lista_designacao[i]->get_demanda()) {
							ponto_atendimento_mais_prox->set_capacidade(capacidade - lista_designacao[i]->get_demanda());
							lista_designacao[i]->set_id_mediana(ponto_atendimento_mais_prox->get_id());
							cidades[lista_designacao[i]->get_id()].set_id_mediana(ponto_atendimento_mais_prox->get_id());

							//Tira a cidade atendida dos pontos de demanda
							remove_cidade(pontos_demanda, lista_designacao[i]);
						}
						else {
							//Ponto de atendimento não tem mais capacidade, atribuir ao próximo disponível
							vector<Cidade*> *pontos_atendimento_ordenados = lista_designacao[i]->ordena_por_distancia(&pontos_atendimento);
							for (size_t j = 0; j < pontos_atendimento_ordenados->size(); j++) {
								Cidade *ponto_atendimento = pontos_atendimento_ordenados->at(j);
								
								if (lista_designacao[i]->get_demanda() >= ponto_atendimento->get_capacidade()) {
									continue;
								}

								ponto_atendimento->set_capacidade(ponto_atendimento->get_capacidade() - lista_designacao[i]->get_demanda());
								lista_designacao[i]->set_id_mediana(ponto_atendimento->get_id());
								cidades[lista_designacao[i]->get_id()].set_id_mediana(ponto_atendimento->get_id());
								break;
							}


							flag_demanda_estourada = true;
							//Tira a cidade atendida dos pontos de demanda
							remove_cidade(pontos_demanda, lista_designacao[i]);
							
							break;
						}
					}
				} while (flag_demanda_estourada);

				/*for (unsigned i = 0; i < lista_designacao.size(); i++) {
					Cidade cidade = lista_designacao[i];					
					cidades[cidade.get_id()].set_id_mediana(cidade.get_id_mediana());
				}*/
			
				break;
			}			
			
		}
	} // algoritmos
} // rotas
