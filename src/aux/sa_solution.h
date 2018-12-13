#pragma once

#include <list>

#include "../lib/data.h"
#include "sa_path.h"
#include "sa_defs.h"

class SASolution {

public:

    /** Estructura que representa la idea de moverse hacia una solución vecina
     *  sin la necesidad de modificar la estructura o crear una copia de ella.
     */
    struct NodeExchange {

        PathId src_path;
        PathId dst_path;
        NodeId src_node; // Nodo en el src para entregar a dst

        NodeExchange(PathId _src_path, PathId _dst_path, NodeId _src_node)
            : src_path(_src_path), dst_path(_dst_path), src_node(_src_node) {};

    };

    /** Constructor a partir de un pathlist */
    SASolution(const Instance&, const PathList&);

    /** Constructor por copia */
    SASolution(const SASolution&);

    /** Genera una tira de vecinos en orden aleatorio. */
    void getNeighbors(std::vector<SASolution::NodeExchange>&) const;

    /** Devuelve la diferencia entre la solucion resultande del intercambio y
     *  la solución actual.
     */
    LengthDelta delta(const SASolution::NodeExchange&) const;

    /** Realiza el intercambio mutando esta estructura. */
    void acceptExchange(const SASolution::NodeExchange&);

    /** Devuelve suma de las longitudes de los caminos de la solución */
    Length get_length() const;

    PathList to_pathlist() const;

private:

    /** Devuelve true si la solución es factible */
    bool isFeasible(const SASolution::NodeExchange&) const;

    const Instance* _in;

    Length _length;

    vector<SAPath> _paths;

};
