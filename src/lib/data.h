#ifndef SRC_LIB_DATA_H
#define SRC_LIB_DATA_H

#include <vector>

/** Datos de un nodo */
struct Node {

    int x               = 0;
    int y               = 0;
    unsigned int demand = 0;
    bool is_depot       = false;

};


/** Una instancia del problema a resolver */
class Instance {

public:

    /** Construye la instancia leyendo de la STDIN */
    Instance();

    /** Cant de nodos */
    size_t size() const;

    /** Referencia inmutable al vector de nodos */
    const std::vector<Node> & getNodes() const;

private:

    /** Cant de nodos */
    unsigned int dimension;

    /** Capacidad de los vehículos */
    unsigned int capacity;

    /** nodos de la instancia */
    std::vector<Node> nodes;

};

#endif // SRC_LIB_DATA_H
