#pragma once

#include <string>
#include "CLI11.hpp"

/**
 * No es la manera mas elegante de resolver el problema, pero creo que la más
 * sencilla de permitir a los algoritmos acceder a sus parámetros específicos
 * pasados en forma de argumentos sin modificar demasiado la estructura del
 * programa.
 */

class Args {

public:

    Args();

    CLI::App app {"TP3 - Aed3"};

    // -- Flags generales ---------------------------------------------------

    /** Nombre del algoritmo a usar */
    std::string algorithm_name;

    /** Flag "experimentación" */
    CLI::Option* exp_flag;

    /** Flag "todo" Imprime experimentación a STDERR y resultado a STDOUT */
    CLI::Option* todo_flag;

    // -- Simulated Annealing -----------------------------------------------

    /** Cantidad máxima de iteraciones para simulated annealing */
    uint32_t max_iters;

    /** Factor de reducción de temperatura */
    float    beta;

    /** Nombre del algoritmo inicial a usar. no puede ser simulated annealing
     */
    std::string initial_algorithm_name;

};
