#include <limits>
#include "args.h"

Args::Args() {

    // Valores por defecto:

    max_iters = std::numeric_limits<uint32_t>::max();
    beta = 0.7f;
    initial_algorithm_name = "savings";

    // Inicializa el parser de argumentos:

    app.add_option("-a,--algo", algorithm_name,
            "Algoritmo. Puede ser `savings`, `goloso`, `sweep`, `2-opt`, `annealing`")
       ->required()
       ->expected(1);

    exp_flag = app.add_flag("--exp,-e", "Mostrar tiempo de ejecución");

    todo_flag = app.add_flag("--todo,-t", "Mostrar resultado y tiempo de ejecución");

    app.add_option("--max-iters,-k", max_iters,
            "Cantidad máxima de iteraciones en Simulated Annealing.");

    app.add_option("--beta,-b", beta,
            "Cantidad máxima de iteraciones en Simulated Annealing.");

    app.add_option("-i,--inicial", initial_algorithm_name,
            "Algoritmo inicial para simulated annealing. Puede ser `savings`,"
            "`goloso`, `sweep`, `2-opt`")
       ->expected(1);

}
