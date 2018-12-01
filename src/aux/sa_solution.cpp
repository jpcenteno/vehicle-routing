#include <vector>
#include <algorithm>
#include <numeric>

#include "sa_solution.h"

SASolution::SASolution(const Instance& in, const PathList& pl)
        : _in(&in) {

    _paths.clear();
    std::transform(pl.first.begin(), pl.first.end(), _paths.begin(),
        [&in](const std::vector<NodeId>& vec){
            return SAPath(in, vec);
        });

    _length = std::accumulate(_paths.begin(), _paths.end(), 0u,
        [](const Length& acc, const SAPath& path){
            return acc + path.get_length();
        });

}

SASolution::SASolution(const SASolution& other)
        : _in(other._in), _length(other._length) {

    _paths.clear();
    std::copy(other._paths.begin(), other._paths.end(), _paths.begin());

}

void SASolution::getNeighbors(
        std::vector<SASolution::NodeExchange>& neighbors) const {

    neighbors.clear();
    for (PathId src_path = 0; src_path < _paths.size(); ++src_path) {
        for (PathId dst_path = 0; dst_path < _paths.size(); ++dst_path) {
            if (src_path == dst_path) { continue; }

            for (const NodeId src_node : _paths[src_path].get_nodes()) {
                if (src_node == 0) { continue; }

                // FIXME pushear solo si es factible!!
                const NodeExchange exc(src_path, dst_path, src_node);
                if (not isFeasible(exc)) { continue; }
                neighbors.push_back(exc);

            }
        }
    }

    std::random_shuffle(neighbors.begin(), neighbors.end());

}

bool SASolution::delta(const SASolution::NodeExchange& exc) const {

    const Length prev_len_src_path = _paths[exc.src_path].get_length();
    const Length prev_len_dst_path = _paths[exc.dst_path].get_length();

    const Length post_len_src_path =
        _paths[exc.src_path].size_after_delete(exc.src_node);

    const Length post_len_dst_path =
        _paths[exc.dst_path].size_after_insert(exc.src_node);

    return _length
        - prev_len_src_path + post_len_src_path
        - prev_len_dst_path + post_len_dst_path;

}

void SASolution::acceptExchange(const SASolution::NodeExchange& exc) {

    const Length prev_len_src_path = _paths[exc.src_path].get_length();
    const Length prev_len_dst_path = _paths[exc.dst_path].get_length();

    const Length post_len_src_path =
        _paths[exc.dst_path].del_node(exc.src_path);

    const Length post_len_dst_path =
        _paths[exc.dst_path].add_node(exc.src_path);

    _length = _length
        - prev_len_src_path + post_len_src_path
        - prev_len_dst_path + post_len_dst_path;

}

bool SASolution::isFeasible(const SASolution::NodeExchange& exc) const {

    return _paths[exc.dst_path].is_add_feasible(exc.src_node);

}


Length SASolution::get_length() const {
    return _length;
}


PathList SASolution::to_pathlist() const {

    PathList pl;

    pl.second = static_cast<int>(_length);

    pl.first.resize(_paths.size());
    for (PathId i = 0; i < _paths.size(); ++i) {
        std::copy(
            _paths[i].get_nodes().begin(),
            _paths[i].get_nodes().end(),
            pl.first[i].begin());
    }

    return pl;
}