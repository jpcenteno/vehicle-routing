#pragma once

#include <vector>
#include <cstdint>

#include "sa_defs.h"
#include "../lib/data.h"

using namespace std;

/** Ruta utilizada en simulated annealing.
 */
class SAPath {

public:

    /** Constructor en base a un vector de ids de nodo.
     *
     * @complejidad: O( nodes.size() )
     */
    SAPath(const Instance& in, vector<NodeId> nodes);

    /** Constructor por copia.
     *
     * @complejidad: O( FIXME )
     */
    SAPath(const SAPath&);

    /** Devuelve longitud del camino. Incluye el paso por el deposito.
     *
     * @complejidad O(1)
     */
    Length get_length() const;

    /** Devuelve la carga del vehículo.
     *
     * @complejidad O(1)
     */
    Quantity get_quantity() const;

    const std::list<NodeId>& get_nodes() const;

    /** Devuelve cantidad de nodos
     *
     * @complejidad O(1)
     */
    size_t size() const;

    /** Devuelve la longitud que resultaría de insertar un nodo `node`. No
     *  modifica
     *
     * @complejidad O( _path.size() )
     */
    Length size_after_insert(const NodeId node) const;

    /** Devuelve la Longitud que resultaría de remover un nodo `node`. No
     *  modifica la estructura.
     *
     * @complejidad O( _path.size() )
     */
    Length size_after_delete(const NodeId nnode) const;

    /** Añade un nodo. Devuelve la longitud resultante.
     *
     * @complejidad O( _path.size() )
     */
    Length add_node(const NodeId node);

    /** Elimina un nodo. Devuelve la longitud resultante.
     *
     * @complejidad O( _path.size() )
     */
    Length del_node(const NodeId node);

    /** Devuelve true si y solo si es factible añadir un nodo bajo la capacidad
     *  del vehículo.
     *
     * @complejidad O(1)
     */
    bool is_add_feasible(const NodeId nnode) const;

private:

    /** Puntero a la instancia del problema */
    const Instance* _in;

    /** Nodos por los que pasa el recorrido. Sin contar salida y llegada al deposito */
    list<NodeId> _path;

    /** Longitud del camino, contando el deposito */
    Length _length;

    /** Carga que lleva el vehiculo */
    Quantity _q;

};
