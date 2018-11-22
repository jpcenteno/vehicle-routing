#include "lib/data.h"
#include "savings.h"

PathList Savings::operator()(const Instance& instance) const {

	// Datos de la instancia
	size_t n = instance.size();
    MatrizDist dist = instance.getDistances();
	vector<Node> nodos = instance.getNodes();
	unsigned int C = instance.getCapacity();

	// Max-heap de savings
	priority_queue<Saving> savings_pq; // O(1)

	// Savings O(n^2*log(n))
	for (size_t i = 1; i < n; i++) {
		if (nodos[i].demand > C) continue;
		for(size_t j = i + 1; j < n; j++) {
			if (nodos[j].demand > C) continue;
			savings_pq.push({i, j, dist[i][0] + dist[0][j] - dist[i][j]}); // i, j, saving
		}	
	}

	// Lista de rutas. Cada una tiene un camino y una capacidad.
	list<Ruta> rutas; // O(1)
	vector<list<Ruta>::iterator> it_ruta(n); // it_ruta[i] = iterador a la ruta de la ciudad i O(n)

	for (size_t i = 1; i < n; ++i) {
		if (nodos[i].demand <= C)
			it_ruta[i] = rutas.insert(rutas.end(), {i, nodos[i].demand});
	}

	// Control de ciudades visitadas
	size_t ciudades_visitadas = 1;
	vector<bool> visitada(n, false); // O(n)
	visitada[0] = true;

	while (!savings_pq.empty() && ciudades_visitadas < n) { // O(n)
		Saving sav = savings_pq.top(); // O(1)
		savings_pq.pop(); // (log n)

		size_t i = sav.i;
		size_t j = sav.j;

		auto ruta_i = it_ruta[i];
		auto ruta_j = it_ruta[j];

		// Están en la misma ruta
		if (ruta_i == ruta_j) continue;

		// La unión de rutas supera la capacidad de un camión
		if (ruta_i->capacidad + ruta_j->capacidad > C) continue;

		size_t front_i = ruta_i->camino.front();
		size_t back_i = ruta_i->camino.back();

		size_t front_j = ruta_j->camino.front();
		size_t back_j = ruta_j->camino.back();

		if ((front_i == i && front_j == j) || (back_i == i && back_j == j)) {
			ruta_i->camino.insert(ruta_i->camino.begin(), ruta_j->camino.rbegin(), ruta_j->camino.rend()); // O(n)
			ruta_i->capacidad += ruta_j->capacidad;
			for (auto c : it_ruta[j]->camino) // O(n)
				it_ruta[c] = it_ruta[i]; // O(1)
			rutas.erase(ruta_j); // O(1)
		} else if (front_i == i && back_j == j) {
			ruta_j->camino.insert(ruta_j->camino.end(), ruta_i->camino.begin(), ruta_i->camino.end());
			ruta_j->capacidad += ruta_i->capacidad;
			for (auto c : it_ruta[i]->camino)
				it_ruta[c] = it_ruta[j];
			rutas.erase(ruta_i);
		} else { // back_i == i && front_j == j
			ruta_i->camino.insert(ruta_i->camino.end(), ruta_j->camino.begin(), ruta_j->camino.end());
			ruta_i->capacidad += ruta_j->capacidad;
			for (auto c : it_ruta[j]->camino)
				it_ruta[c] = it_ruta[i];
			rutas.erase(ruta_j);
		}

		if (!visitada[i] && (it_ruta[i]->camino).size() > 1) {
			visitada[i] = true;
			ciudades_visitadas++; 
		}

		if (!visitada[j] && (it_ruta[j]->camino).size() > 1) {
			visitada[j] = true;
			ciudades_visitadas++; 
		}
	}

	PathList result;
	result.second = 0;
	
	size_t last;
	for (auto r : rutas) { // O(n)
		last = 0;
		vector<size_t> ruta;
		ruta.push_back(0);
		for (auto nodo : r.camino) {
			ruta.push_back(nodo); // O(1)
			result.second += dist[last][nodo];
			last = nodo;
		}
		ruta.push_back(0);
		result.first.push_back(ruta); // O(1)
		result.second += dist[last][0];
	}

	return result;
}