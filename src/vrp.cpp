#include <iostream>

#include "lib/CLI11.hpp"
#include "lib/data.h"
#include "lib/args.hpp"
#include "savings.h"
#include "goloso.h"
#include "2_opt.h"
#include "sweep_tspGoloso.h"
#include "simulated_annealing.h"



int getAlgorithm(const string& name, Algorithm& a) {
    if (name == "savings") {
        a = Savings();
    } else if (name == "goloso") {
        a = Goloso();
    } else if (name == "sweep") {
        a = Sweep();
    } else if (name == "2-opt") {
        a = TwoOpt();
    } else if (name == "annealing") {
        a = SimulatedAnneling();
    } else {
        return 0;
    }
    return 1;
}

void printPathList(const PathList& pl) {

    cout << pl.first.size() << endl;

    int route = 1;
    for (auto r :  pl.first) {
        cout << "#" << (route++) << ": ";
        for (size_t i = 0; i < r.size(); ++i) {
            cout << r[i] << " ";
        }
        cout << "\n";
    }

    cout << pl.second << "\n";
}

int main(int argc, char * argv[]) {

    // CLI
    PARSEARGS();

    Algorithm algo;
    getAlgorithm(args::algorithm_name, algo);

    // Lee STDIN
    const Instance instance;

    // Si se pasa el parámetro -e por consola se muestra el tiempo de ejecución
    if (*args::exp_flag) {
        double avg = 0;
        cout << instance.size();
        for (int k = 0; k < 3; k++) {
            auto start = chrono::steady_clock::now();
            algo(instance);
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            avg += chrono::duration <double, milli> (diff).count();
        }
        avg /= 3.0;
        cout << " " << avg << endl;
    } else { // Ejecuta el algoritmo
        const PathList result = algo(instance);
        printPathList(result);
    }


    return 0;

}
