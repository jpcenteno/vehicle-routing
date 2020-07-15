Vehicle Routing Algorithms
===========================

This project contains four heuristics for the Capacitated Vehicle Routing Problem (CVRP).

The implemented heuristics are:
- Clarke and Wright _Savings_.
- _Greedy algorithm_.
- _Cluster First / Route second_ + _Sweep Algorithm_.
- _Cluster First / Route second_ + _2-opt_.
- _Simulated Annealing_.

This was made as part of our "Algorithms and Data Structures III" course, taught during the first semester of 2019 at the Faculty of Natural and Exact Sciences, University of Buenos Aires.

Compilar
--------

```
make clean && make
```

Ejecutar el programa
---------------------

Para ver un mensaje de ayuda:

```
./build/vrp --help
```

Para ejecutar uno de los algoritmos:

```
cat data/CASO_DE_PRUEBA.vrp | ./build/vrp --algo ALGORITMO
```
