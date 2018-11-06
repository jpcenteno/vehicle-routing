#ifndef SRC_LIB_DATA_H
#define SRC_LIB_DATA_H

#include <vector>

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
	int s;

	bool operator<(const Saving &a) const {
    		return s < a.s;
	}
};

/** Lista de caminos para la salida */
typedef std::vector<std::vector<Node>> PathList;

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
