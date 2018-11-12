#ifndef SRC_LIB_DATA_H
#define SRC_LIB_DATA_H

#include <iostream>
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
#include <vector>
#include <math.h>

/** Datos de un nodo */
struct Node {

    int x               = 0;
    int y               = 0;
    unsigned int demand = 0;
    bool is_depot       = false;

	Node(int i, int j, unsigned int d, bool depot) {
		x = i;
		y = j;
		demand = d;
		is_depot = depot;	
	}

};

struct Saving{

	int i;
	int j;
	float s;

	bool operator<(const Saving &a) const {
    		return s < a.s;
	}
};

struct Angular{
	Node p= Node(0,0,0,false);
	float alfa = 0;

	
	bool operator>(const Angular &b) const{
		return alfa > b.alfa;
	}

};

/** Lista de caminos para la salida */
typedef std::pair<std::vector<std::vector<int>>, int> PathList;  //Es la pathList + costoTotal    

/** Matriz distancias entre nodos */
typedef std::vector<std::vector<float>> MatrizDist;


/** Una instancia del problema a resolver */
class Instance {

public:

    /** Construye la instancia leyendo de la STDIN */
    Instance();

    /** Cant de nodos */
    size_t size() const;

    /** Referencia inmutable al vector de nodos */
    const std::vector<Node> & getNodes() const;


    /** Referencia inmutable a la capacidad */
    const unsigned int & getCapacity() const;	

    /** Devuelve la matriz de distancias */
    const MatrizDist & getDistances() const;


private:

    /** Cant de nodos */
    unsigned int dimension;

    /** Capacidad de los vehículos */
    unsigned int capacity;

    /** nodos de la instancia */
    std::vector<Node> nodes;

    std::vector<std::vector<float>> distances;

    /** Inicializa la matriz distances */
    void initDistancesMatrix();

};

#endif // SRC_LIB_DATA_H
