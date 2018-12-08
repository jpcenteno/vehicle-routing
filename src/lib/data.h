//
// Created by silvia on 18/11/18.
//

#ifndef UNTITLED_DATA_H
#define UNTITLED_DATA_H


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
#include <functional>

using namespace std;


/** Datos de un nodo */
struct Node {

    int x               = 0;
    int y               = 0;
    unsigned int demand = 0;
    bool is_depot       = false;

    Node() : x(0), y(0), demand(0), is_depot(false) {}

    Node(int i, int j, unsigned int d, bool depot) {
        x = i;
        y = j;
        demand = d;
        is_depot = depot;
    }

};

/** Datos de un Saving para un par de nodos i, j */
struct Saving {

    size_t i;
    size_t j;
    unsigned int s;

    bool operator<(const Saving &a) const {
        return s < a.s;
    }

};

/** Angulos de los nodos con respecto al deposito */
struct Angular {

    Node p;
    long double alfa = 0;
    size_t id = 0;


    bool operator>(const Angular &b) const {
        return alfa > b.alfa;
    }

};

/** Lista de caminos y costo total para la salida */
typedef std::pair<std::vector<std::vector<size_t>>, int> PathList;

/** Matriz distancias entre nodos */
typedef std::vector<std::vector<unsigned int>> MatrizDist;

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

    /** Matriz de distancias */
    std::vector<std::vector<unsigned int>> distances;

    /** Inicializa la matriz distances */
    void initDistancesMatrix();

};

typedef function<PathList (const Instance&)> Algorithm;

#endif //UNTITLED_DATA_H
