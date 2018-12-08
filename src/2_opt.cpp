#include "2_opt.h"

/*
	Costo de una ruta
	Input: 
		- Referencia a ruta
		- Referencia a matriz de distancias
	Output:
		- Costo de la ruta
*/
unsigned int TwoOpt::costo_ruta(const vector<size_t>& ruta, const MatrizDist& dist) const {
	size_t last = 0;
	unsigned int costo = 0;
	for (size_t i = 1; i < ruta.size(); ++i) { 
		costo += dist[last][ruta[i]];
		last = ruta[i];
	}

	return costo;
}

/*
	Swap de dos nodos de la ruta
	Input:
		- i,j: Posición de los nodos en la ruta
		- Referencia a una ruta [0, 1, ... , i, ... , j, ... , n - 1]
	Output:
		- Ruta con los nodos intercambiados tal que nueva_ruta = [0, 1, ... , j, j - 1, ... , i + 1, i, ... , n - 1]
*/
vector<size_t> TwoOpt::swap_nodos(size_t i, size_t j, const vector<size_t>& ruta) const {
	vector<size_t> nueva_ruta;
	size_t n = ruta.size();

	nueva_ruta.push_back(0);
	for (size_t k = 1; k < i; ++k) nueva_ruta.push_back(ruta[k]);
	for (size_t k = j; k >= i; --k) nueva_ruta.push_back(ruta[k]);
	for (size_t k = j + 1; k < n - 1; ++k) nueva_ruta.push_back(ruta[k]);
	nueva_ruta.push_back(0);

	return nueva_ruta;
}

/*
 	Heurística 2-opt para mejorar el costo de una ruta.
 	Input:
 		- Referencia modificable a una ruta
 		- Referencia a la matriz de distancias
 	Output:
 		- Costo de la ruta mejorada (si es posible)
*/
unsigned int TwoOpt::two_opt(vector<size_t>& ruta, const MatrizDist& dist) const {
	size_t n = ruta.size();
	unsigned int mejor_costo = 0;
	bool hay_mejora = true;

	while (hay_mejora) {
		hay_mejora = false;
		mejor_costo = costo_ruta(ruta, dist);
		for (size_t i = 1; i < n - 1; ++i) {
			for (size_t j = i + 1; j < n - 1; ++j) {
				vector<size_t> nueva_ruta = swap_nodos(i, j, ruta);
				unsigned int nuevo_costo = costo_ruta(nueva_ruta, dist);
				if (nuevo_costo < mejor_costo) {
					hay_mejora = true;
					ruta = nueva_ruta;
					mejor_costo = nuevo_costo;
				}
			}
		}
	}

	return mejor_costo;
}

/*
	Clusterización utilizando el método de savings y ruteo utilizando la heurísitica 2-opt
	Input:
		- Instancia de CVRP
	Output:
		- PathList
*/
PathList TwoOpt::operator()(const Instance& instance) const {
	const Savings solve_saving;
	PathList result = solve_saving(instance);

	MatrizDist dist = instance.getDistances();
	result.second = 0;
	for (auto &ruta : result.first) {
		result.second += two_opt(ruta, dist);
	}

	return result;
}
