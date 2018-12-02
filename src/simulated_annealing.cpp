#include <cstdint>
#include <algorithm>
#include <numeric>
#include <limits>

#include "simulated_annealing.h"
#include "aux/sa_defs.h"
#include "aux/sa_path.h"
#include "aux/sa_solution.h"
#include "savings.h"

/** revuelve un float en ~U(0,1) */
inline float rand_uniform() {
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return r;
}


PathList SimulatedAnneling::operator()(const Instance& in) const {

    const PathList pl = Savings()(in);

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
    while ( k  < args::max_iters ) {

        s.getNeighbors(neighbors);
        for ( const SASolution::NodeExchange& exc : neighbors ) {

            LengthDelta delta = s.delta(exc);

            if (delta < 0 or (- delta / t) < rand_uniform()) {

                s.acceptExchange(exc);
                if ( s.get_length() < s_best.get_length() ) {
                    s_best = s;
                }
                break;

            }
        }

        t = t * args::beta;
    }

    return s_best.to_pathlist();
}
