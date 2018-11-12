#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <tuple>
#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>
#include <list>
#include <climits>
#include <queue>
#include <math.h> 

#include "lib/data.h"
#include "savings.h"

PathList Savings::operator()(const Instance& instance) const {

	// Datos de la instancia
	int n = instance.size();
    MatrizDist dist = instance.getDistances();
	vector<Node> nodos = instance.getNodes();
	int C = instance.getCapacity();

	// Max-heap de savings
	priority_queue<Saving, vector<Saving>> savings_pq;

	// Savings
	for (int i = 1; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			savings_pq.push({i, j, dist[i][0] + dist[0][j] - dist[i][j]}); // i, j, saving
		}	
	}

	// Lista de rutas. Cada una tiene un camino y una capacidad.
	list<Ruta> rutas;
	vector<list<Ruta>::iterator> it_ruta(n, rutas.end()); // it_ruta[i] = iterador a la ruta de la ciudad i

	// Control de ciudades visitadas
	int ciudades_visitadas = 1;
	vector<bool> visitada(n, false);
	visitada[0] = true;

	while (!savings_pq.empty() && ciudades_visitadas < n) {
		Saving sav = savings_pq.top();
		savings_pq.pop();

		int i = sav.i;
		int j = sav.j;

		// Saving descartado
		if (nodos[i].demand + nodos[j].demand > C) continue;

		// Las ciudades no están en ninguna ruta
		if (it_ruta[i] == rutas.end() && it_ruta[j] == rutas.end()) {
			rutas.push_back({i, j, nodos[i].demand + nodos[j].demand}); // i, j, demanda
			it_ruta[i] = it_ruta[j] = prev(rutas.end());
		// La ciudad i está en una ruta y la ciudad j no
		} else if (it_ruta[i] != rutas.end() && it_ruta[j] == rutas.end()) {
			auto r = it_ruta[i];

			if (nodos[j].demand + r->capacidad > C) continue;

			if (r->camino.front() == i) {
				r->camino.push_front(j);
				r->capacidad += nodos[j].demand;
				it_ruta[j] = it_ruta[i];
			} else if (r->camino.back() == i) {
				r->camino.push_back(j);
				r->capacidad += nodos[j].demand;
				it_ruta[j] = it_ruta[i];
			}
		// La ciudad j está en una ruta y la ciudad i no
		} else if (it_ruta[i] == rutas.end() && it_ruta[j] != rutas.end()) {
			auto r = it_ruta[j];

			if (nodos[i].demand + r->capacidad > C) continue;	

			if (r->camino.front() == j) {
				r->camino.push_front(i);
				r->capacidad += nodos[i].demand;
				it_ruta[i] = it_ruta[j];
			} else if (r->camino.back() == j) {
				r->camino.push_back(i);
				r->capacidad += nodos[i].demand;
				it_ruta[i] = it_ruta[j];
			}
		// Ambas ciudades están el alguna ruta
		} else {
			auto ruta_i = it_ruta[i];
			auto ruta_j = it_ruta[j];

			// Están en la misma ruta
			if (ruta_i == ruta_j) continue;

			// La unión de rutas supera la capacidad de un camión
			if (ruta_i->capacidad + ruta_j->capacidad > C) continue;

			int front_i = ruta_i->camino.front();
			int back_i = ruta_i->camino.back();

			int front_j = ruta_j->camino.front();
			int back_j = ruta_j->camino.back();

			if (front_i == i && front_j == j) {
				ruta_i->camino.insert(ruta_i->camino.begin(), ruta_j->camino.rbegin(), ruta_j->camino.rend());
				ruta_i->capacidad += ruta_j->capacidad;
				for (auto c : it_ruta[j]->camino)
					it_ruta[c] = it_ruta[i];
				rutas.erase(ruta_j);
			} else if (back_i == i && back_j == j) {
				ruta_i->camino.insert(ruta_i->camino.end(), ruta_j->camino.rbegin(), ruta_j->camino.rend());
				ruta_i->capacidad += ruta_j->capacidad;
				for (auto c : it_ruta[j]->camino)
					it_ruta[c] = it_ruta[i];
				rutas.erase(ruta_j);
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
		}

		if (!visitada[i] && it_ruta[i] != rutas.end()) {
			visitada[i] = true;
			ciudades_visitadas++; 
		}

		if (!visitada[j] && it_ruta[j] != rutas.end()) {
			visitada[j] = true;
			ciudades_visitadas++; 
		}
	}

	PathList result;

	/*
	TODO: Generar el PathList
	for (auto r : rutas) {
		result.push_back({std::begin(r.camino), std::end(r.camino)});
	}
	*/

	return result;
}


