#include "gillet_johnson.h"
#include <iostream>
#include <string>

namespace rotas
{
	namespace algoritmos
	{
		using namespace std;

		void GilletJohnson::atribui_medianas(std::vector<Caminho> caminhos, std::vector<Cidade> cidades) {
			cout << "Caminhos: " << endl;

			//TODO proteções para tamanhos de distancias e caminhos

			//Passo 1 - Para cada cidade, encontrar L1 e L2	
			//Separar as medianas
			vector<Cidade> medianas = vector<Cidade>();
			for (unsigned int i = 0; i < cidades.size(); i++) {
				Cidade cidade = cidades.at(i);
				if (cidade.is_mediana()) {
					medianas.push_back(cidade);
				}
			}

			//Caso não encontre pelo menos 2 medianas, o algoritmo não tem como funcionar
			if (medianas.size() < 2) {
				//TODO disparar exceção
				cout << "Erro!!!" << endl;
				return;
			}

			//Achar o indice da mediana mais próxima (L1)
			int L1 = -1;
			double distancia = caminhos[0].distancias_entre_cidades[0].get_distancia();
			double distancia_min = distancia;
			for (unsigned int j = 0; j < medianas.size(); j++) {
				distancia = caminhos[0].distancias_entre_cidades[j].get_distancia();
				distancia_min = distancia < distancia_min ? distancia : distancia_min;
			}




			std::cout << "Cidades: " << std::endl;
			for (int i = 0; i < 9; i++) {
				Cidade cidade = cidades.at(i);
				std::cout << cidade.get_nome() << " ";
			}
			std::cout << std::endl;
		}
	} // algoritmos
} // rotas
