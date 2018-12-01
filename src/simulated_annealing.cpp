#include <cstdint>
#include <algorithm>
#include <numeric>
#include <limits>


#include "simulated_annealing.h"
#include "savings.h"

/** Tira una "moneda" aleatoria con una probabilidad dada */
inline bool rand(float probability) {

    // genera r ~ U(0, 1)
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return r < probability;

}


PathList SimulatedAnneling::operator()(Instance&,
                        uint32_t n_resets = 3,
                        float t           = 10,
                        float beta        = static_cast<float>(0.7));
