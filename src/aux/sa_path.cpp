#include "sa_path.h"

#include <algorithm>
#include <numeric>

// Detalles de implementación:
// ---------------------------
//
// La representación interna del objeto esta dada por:
// _path
// _length
// _q
//
// En _path se incluyen como inicio y fin el nodo 0 (deposito) como una forma
// de simplificar los calculos internos. Estos deberían ser transparentes para
// el usuario.

#include <iostream> // FIXME sacalo
SAPath::SAPath(const Instance& in, vector<NodeId> path) : _in(&in) {


    copy(begin(path), end(path), std::back_inserter(_path)); // O(length path)

    // O(length path)
    _q = accumulate(begin(_path), end(_path), static_cast<Quantity>(0),
        [&in](const Quantity acc, const NodeId node){
            const Quantity q = (node != 0) ? in.getNodes()[node].demand : 0;
            return acc + q;
        });

    // O(length path)
    _length = 0;
    for( PathIndex i = 1; i < path.size(); ++i) {
        NodeId node = path[i];
        NodeId prev = path[i - 1];
        _length     += in.getDistances()[prev][node];
    }

}


SAPath::SAPath(const SAPath& other)
        : _in(other._in),
          _path(other._path),
          _length(other._length),
          _q(other._q) {}


Length SAPath::get_length() const {
    return _length;
}


Quantity SAPath::get_quantity() const {
    return _q;
}


const std::list<NodeId>& SAPath::get_nodes() const {
    return _path;
}

size_t SAPath::size() const {
    // No cuenta el deposito que figura 2 veces en _path
    return _path.size() - 2;
}

/** Devuelve diferencia en longitud del camino al añadir un nodo `node` entre
 * dos nodos apuntados por `it_r` y `it_s`. El negativo del resultado es la
 * diferencia de quitar un nodo `node` de entre `it_r` e `it_s`.
 *
 * Como la distancia entre nodos respeta la desigualdad triangular, se cumple
 * que la distancia directa entre los nodos `r` y `s` es menor o igual a la
 * distancia del camino que va `r->nodo->s`.
 * - Por lo tanto el delta de añadir un nodo es positivo.
 * - Por lo tanto el delta de quitar un nodo es negativo.
 *
 * Esta funcion devuelve el delta de añadir un nodo. El delta de quitar un nodo
 * es el negativo del delta de añadirlo.
 *
 * @complejidad O(1)
 */
template<typename It>
static LengthDelta get_delta(
        const NodeId node, const It it_r, const It it_s, const Instance* in) {

    const NodeId r = *it_r;
    const NodeId s = *it_s;

    const Length len_r_node = static_cast<Length>(in->getDistances()[r][node]);
    const Length len_node_s = static_cast<Length>(in->getDistances()[node][s]);
    const Length len_r_s    = static_cast<Length>(in->getDistances()[r][s]);

    return static_cast<LengthDelta>(len_r_node + len_node_s - len_r_s);

}

Length SAPath::size_after_insert(const NodeId node) const {

    // Va a querer insertar el nodo nuevo entre los dos nodos contiguos (r, s)
    // para los cuales sea mínimo el aumento de longitúd.

    auto it_r = begin(_path);
    auto it_s = next(it_r);
    const auto last = end(_path);

    // Si la lista tiene solo el deposito
    if (_path.size() < 3) { return numeric_limits<Length>::max(); }

    auto best_it_r         = it_r; // Punto optimo a partir del cual insertar;
    LengthDelta best_delta = get_delta(node, it_r, it_s, _in);

    it_r++;
    it_s++;
    while (it_s != last) { // Por la cantidad de nodos en el camino

        const LengthDelta delta = get_delta(node, it_r, it_s, _in);
        if (delta < best_delta) {
            best_delta = delta;
            best_it_r  = it_r;
        }

        it_r++;
        it_s++;
    }

    return _length + static_cast<Length>(best_delta);

}


Length SAPath::size_after_delete(const NodeId node) const {

    // Quiero calcular el valor de longitud luego de quitar el nodo `node`

    auto it_r = begin(_path);
    while (* next(it_r) != node) { it_r++; } // O( _path.size() )
    const auto it_s = next(it_r, 2);

    LengthDelta neg_delta = get_delta(node, it_r, it_s, _in);
    return static_cast<Length>(static_cast<LengthDelta>(_length) - neg_delta);

}

Length SAPath::add_node(const NodeId node) {

    // Va a insertar el nodo nuevo entre los dos nodos contiguos (r, s) para
    // los cuales sea mínimo el aumento de longitúd.

    auto it_r = begin(_path);
    auto it_s = next(it_r);
    const auto last = end(_path);

    // Si la lista tiene solo el deposito
    if (it_s == last) { throw runtime_error("size < 2!!"); }

    auto best_it_s         = it_s; // Punto óptimo antes del cual insertar;
    LengthDelta best_delta = get_delta(node, it_r, it_s, _in);

    it_r++;
    it_s++;
    while (it_s != last) {

        const LengthDelta delta = get_delta(node, it_r, it_s, _in);
        if (delta < best_delta) {
            best_delta = delta;
            best_it_s  = it_s;
        }

        it_r++;
        it_s++;
    }

    // Inserta `node` en la mejor posición
    _path.insert(best_it_s, node);
    _q += _in->getNodes()[node].demand;
    _length += static_cast<Length>(best_delta);

    return _length;

}


Length SAPath::del_node(const NodeId node) {

    // Va a quitar el nodo `node` de entre los dos nodos contiguos (r, s)

    const auto it_node = std::find(std::begin(_path), std::end(_path), node);
    const auto it_r = std::prev(it_node);
    const auto it_s = std::next(it_node);

    LengthDelta neg_delta = get_delta(node, it_r, it_s, _in);
    _length -= static_cast<Length>(neg_delta);
    _q -= _in->getNodes()[node].demand;
    _path.erase(next(it_r));

    return _length;

}


bool SAPath::is_add_feasible(const NodeId node) const {

    const Quantity node_q = _in->getNodes()[node].demand;
    const Quantity vehicle_q = _in->getCapacity();

    return node_q + _q <= vehicle_q;

}

