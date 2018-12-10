#include <cstdint>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cmath>

#include "simulated_annealing.h"
#include "aux/sa_defs.h"
#include "aux/sa_path.h"
#include "aux/sa_solution.h"
#include "lib/args.h"
#include "savings.h"
#include "goloso.h"
#include "2_opt.h"
#include "sweep_tspGoloso.h"

/** revuelve un float en ~U(0,1) */
inline float rand_uniform() {
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return r;
}


SimulatedAnneling::SimulatedAnneling(const Args& args) : _args(args) {}


Algorithm getInitialAlgorithm(const string& name) {
    if (name == "savings") {
        return Savings();
    } else if (name == "goloso") {
        return Goloso();
    } else if (name == "sweep") {
        return Sweep();
    } else if (name == "2-opt") {
        return TwoOpt();
    } else {
        throw std::runtime_error(
                "No existe el la heuristica inicial especificada.");
    }
}


PathList SimulatedAnneling::operator()(const Instance& in) const {
    const Algorithm f = getInitialAlgorithm(_args.initial_algorithm_name);
    const PathList pl = f(in);

    SASolution s(in, pl);
    SASolution s_best(s); // Mejor solución conocida hasta el momento

    std::vector<SASolution::NodeExchange> neighbors;
    s.getNeighbors(neighbors);

    auto it_max_delta = std::max_element(neighbors.begin(), neighbors.end(),
        [&s](const auto& exc_a, const auto& exc_b){
            return s.delta(exc_a) < s.delta(exc_b);
        });
    float t = static_cast<float>(s.delta(*it_max_delta));

    uint32_t k = 0;
    while ( k  < _args.max_iters ) {

        s.getNeighbors(neighbors);
        for ( const SASolution::NodeExchange& exc : neighbors ) {

            float delta = static_cast<float>(s.delta(exc));

            if (delta < 0 or std::exp(-delta / t) < rand_uniform()) {

                s.acceptExchange(exc);
                if ( s.get_length() < s_best.get_length() ) {
                    s_best = s;
                }
                break;

            }
        }

        t = t * _args.beta;

        k++;
    }

    return s_best.to_pathlist();
}
