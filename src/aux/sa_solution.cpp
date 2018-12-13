#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <cassert>

#include "sa_solution.h"

SASolution::SASolution(const Instance& in, const PathList& pl)
        : _in(&in) {

    _paths.clear();
    std::transform(pl.first.begin(), pl.first.end(), std::back_inserter(_paths),
        [&in](const std::vector<NodeId>& vec){
            return SAPath(in, vec);
        });


    _length = std::accumulate(_paths.begin(), _paths.end(), 0u,
        [](const Length& acc, const SAPath& path){
            return acc + path.get_length();
        });

    check();
}

SASolution::SASolution(const SASolution& other)
        : _in(other._in), _length(other._length) {

    _paths.clear();
    std::transform( other._paths.begin(), other._paths.end(),
                    std::back_inserter(_paths),
                    [](const SAPath& x){ return SAPath(x); });

    check();

}

void SASolution::getNeighbors(
        std::vector<SASolution::NodeExchange>& neighbors) const {
    check();

    neighbors.clear();
    for (PathId src_path = 0; src_path < _paths.size(); ++src_path) {
        for (PathId dst_path = 0; dst_path < _paths.size(); ++dst_path) {
            if (src_path == dst_path) { continue; }

            const std::list<NodeId>& src_nodes = _paths[src_path].get_nodes();
            for (const NodeId src_node : src_nodes) {
                if (src_node == 0) { continue; }

                // FIXME pushear solo si es factible!!
                const NodeExchange exc(src_path, dst_path, src_node);
                if (isFeasible(exc)) {
                    neighbors.push_back(exc);
                }

            }
        }
    }

    std::random_shuffle(neighbors.begin(), neighbors.end());

}

LengthDelta SASolution::delta(const SASolution::NodeExchange& exc) const {
    check();

    const Length prev_len_src_path = _paths[exc.src_path].get_length();
    const Length prev_len_dst_path = _paths[exc.dst_path].get_length();

    const Length post_len_src_path =
        _paths[exc.src_path].size_after_delete(exc.src_node);

    const Length post_len_dst_path =
        _paths[exc.dst_path].size_after_insert(exc.src_node);

    return - static_cast<LengthDelta>(prev_len_src_path)
           + static_cast<LengthDelta>(post_len_src_path)
           - static_cast<LengthDelta>(prev_len_dst_path)
           + static_cast<LengthDelta>(post_len_dst_path);

}

void SASolution::acceptExchange(const SASolution::NodeExchange& exc) {
    check();

    const Length prev_len_src_path = _paths[exc.src_path].get_length();
    const Length prev_len_dst_path = _paths[exc.dst_path].get_length();

    const Length post_len_src_path =
        _paths[exc.src_path].del_node(exc.src_node);

    const Length post_len_dst_path =
        _paths[exc.dst_path].add_node(exc.src_node);

    _length = _length
        - prev_len_src_path + post_len_src_path
        - prev_len_dst_path + post_len_dst_path;

    check();
}

bool SASolution::isFeasible(const SASolution::NodeExchange& exc) const {
    check();

    return _paths[exc.dst_path].is_add_feasible(exc.src_node);

}


Length SASolution::get_length() const {
    check();
    return _length;
}


PathList SASolution::to_pathlist() const {
    check();

    PathList pl;

    pl.second = static_cast<int>(_length);

    pl.first.resize(_paths.size());
    for (PathId i = 0; i < _paths.size(); ++i) {
        std::copy(
            _paths[i].get_nodes().begin(),
            _paths[i].get_nodes().end(),
            std::back_inserter(pl.first[i]));
    }

    return pl;
}

/** Verifica el estado interno del objeto */
void SASolution::check() const {

    // verifica c/u path
    std::for_each(begin(_paths), end(_paths), [](const auto& path){
        path.check();
    });

    // verifica que cada nodo pertenezca a uno solo de los paths
    std::set<NodeId> visitados;
    std::for_each(begin(_paths), end(_paths), [&visitados](const auto& path){
        for (const NodeId node : path.get_nodes()) {
            if (node == 0) {continue;}
            assert( visitados.find(node) == end(visitados) );
            visitados.insert(node);
        }
    });

    // Verifica que cantidad de nodos sea n
    size_t n_posta = std::accumulate(begin(_paths), end(_paths), 1u,
            [](const size_t acc, const SAPath& path){ return acc + path.size(); });
    assert( n_posta == _in->size() );

    // Verifica que la length sea la posta
    Length length_posta = std::accumulate(begin(_paths), end(_paths), 0,
            [](const Length acc, const SAPath& path){ return acc + path.get_length();});
    assert( length_posta == _length );


}

