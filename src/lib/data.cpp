#include <iostream>
#include <string>

#include "data.h"

// -- Instance ---------------------------------------------------------------

/** Devuelve true si la str empieza con la keyword */
static bool findKeyword(const std::string &str, const char *keyword) {
    return (str.find(keyword, 0) != std::string::npos);
}

/**
 * ⚠️  Supuestos:
 *
 * - Se asume que la entada es correcta con respecto a la especificación dada
 *   por [TSPLIB95].
 *
 * - Puntualmente que no se redefinen campos de los datos.
 *
 * - Se parsea solamente lo necesario para el scope de este trabajo práctico.
 *
 * - Se respeta el invariante que garantiza que al momento de procesar un dato,
 *   se encuentran disponibles los datos de los cuales depende para su correcta
 *   lectura.
 *
 */
Instance::Instance() {

    std::string line;
    while ( std::getline(std::cin, line) ) {

        if ( findKeyword(line, "DIMENSION") ) {

            std::sscanf(line.data()+12, "%u", &dimension);
            nodes.resize(dimension);

        } else if (findKeyword(line, "CAPACITY")) {

            std::sscanf(line.data()+11, "%d", &capacity);

        } else if ( findKeyword(line, "NODE_COORD_SECTION") ) {

            for ( size_t i = 0; i < dimension; ++i) {

                size_t id;
                unsigned int x, y;
                std::cin >> id >> x >> y;

                nodes[id - 1].x = x;
                nodes[id - 1].y = y;

            }

        } else if ( findKeyword(line, "DEMAND_SECTION") ) {

            for ( size_t i = 0; i < dimension; ++i) {

                size_t id;
                unsigned int d;
                std::cin >> id >> d;

                nodes[id - 1].demand = d;

            }

        } else if ( findKeyword(line, "DEPOT_SECTION") ) {

            std::getline(std::cin, line);
            while ( ! findKeyword(line, "-1") ) {

                size_t id;
                std::sscanf(line.data(), "%zu", &id);

                nodes[id - 1].is_depot = true;

                std::getline(std::cin, line);

            }

        }

        // Se lee solamente los campos con datos útiles. Se ignora el resto.

    }
}

size_t Instance::size() const {
    return dimension;
}

const std::vector<Node> & Instance::getNodes() const {
    return nodes;
}
