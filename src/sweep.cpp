#include <cmath>
#include "lib/data.h"


using namespace std;

typedef std::vector<std::vector<int>> Dist;

Dist initDistancesMatrix(std::vector<Node>& nodos) {
    size_t n = nodos.size();
    Dist distances(n,std::vector<int>(n,0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            float x_i = (float) nodos[i].x;
            float y_i = (float) nodos[i].y;
            float x_j = (float) nodos[j].x;
            float y_j = (float) nodos[j].y;
            distances[i][j] =
                    (int) round(std::sqrt(std::pow(x_i - x_j, 2) + std::pow(y_i - y_j, 2)));  //agrugue el round de la libreria math.h
        }
    }

    return distances;
}


std::vector<std::vector<Angular>> sweep(const std::vector<Node>& nodos, unsigned int C){
    std::vector<std::vector<Angular>> clusteres;
    size_t n = nodos.size();
    int carga = 0;
    long double alfa;

    /*vector<Angular> es la estructura sobre la que se arma la priority queue*/
    priority_queue<Angular, vector<Angular>, greater<Angular>> sweptPoints;
    Angular punto;
    Angular deposito;
    deposito.p = nodos[0];   //Lo demas esta seteado en el struct alfa = 0, id =0
    for(size_t i = 1; i<n; i++){
        int dif_x = nodos[i].x - nodos[0].x;
        int dif_y = nodos[i].y - nodos[0].y;
        alfa = atan2(dif_y, dif_x);
        if(alfa < 0){
            alfa = 2*M_PI + alfa;
        }
        punto.alfa = alfa;
        punto.p = nodos[i];
        punto.id = i;
        sweptPoints.push(punto);
    }

    vector<Angular> cluster;
    while(!sweptPoints.empty()){
        punto = sweptPoints.top();
        if(punto.p.demand + carga <= C){
            cluster.push_back(punto);
            carga+= punto.p.demand;
            sweptPoints.pop();
        }else{
            if(punto.p.demand > C){   //es un infactible lo salteo
                sweptPoints.pop();
                continue;
            }
            // aca el punto es factible y no lo popeo para que en la siguiente iteracion sea agregado a otro cluster
            if(cluster.size() != 0){

                cluster.push_back(deposito); //En todos los clusteres tiene que estar el deposito
                clusteres.push_back(cluster);
                cluster.clear();
                carga = 0;
            }


        }
    }
    if(cluster.size() > 0){  //caso unico cluster o ultimo cluster armado hasta vaciar la cola
        cluster.push_back(deposito);
        clusteres.push_back(cluster);
    }

    return clusteres;
}



std::pair<std::vector<int>, int> tspGoloso(std::vector<Angular>& cluster, Dist& dist) {

    size_t n = cluster.size();
    vector<bool> visitados(n, false);
    size_t cant_nodos = 0;
    int costo = 0;
    int indice_min = cluster.size() - 1; //El deposito se agrego siempre como ultimo elemento del cluster
    int min = 0;
    int i;
    std::vector<int> camino;
    while(cant_nodos < n){
        camino.push_back(cluster[indice_min].id);
        visitados[indice_min] = true;
        costo += min;
        cant_nodos++;
        min = INT_MAX;
        i = indice_min;

        for(size_t j=0; j<n; j++){
            if(cluster[i].id != cluster[j].id && !visitados[j] && dist[cluster[i].id][cluster[j].id] < min){
                min = dist[cluster[i].id][cluster[j].id];
                indice_min = j;
            }
        }
        camino.push_back(cluster[indice_min].id);
    }

    costo += dist[camino.back()][0];
    camino.push_back(0);

    return {camino, costo};
}



PathList ruteo(std::vector<vector<Angular> >& clusters, std::vector<Node>& nodos){
    Dist dist = initDistancesMatrix(nodos);
    PathList rutas;
    rutas.second = 0;
    pair<vector<int>, int> tsp;
    for (size_t i = 0; i < clusters.size(); ++i) {
        tsp = tspGoloso(clusters[i], dist);
        rutas.first.push_back(tsp.first);
        rutas.second += tsp.second;
    }
    return rutas;
}



PathList rutear(std::vector<Node>& nodos, int C) {
    vector<vector<Angular>> clusters = sweep(nodos, C);
    PathList res = ruteo(clusters, nodos);
    return res;
}

int main(){

    int C= 100;

    vector<Node> nodos = {{40,40,0,true},{50,40,60,false},{45,45,20,false},{55,50,120,false},{40,55,15,false},{35,45,10,false},{35,40,30,false},{35,30,70,false},{40,20,5,false},{45,30,5,false}};

    PathList res = rutear(nodos, C);
    cout<< res.first.size() << endl;

    for(size_t i=0; i<res.first.size(); i++){
        for(size_t j = 0; res.first[i].size(); j++){
            cout << res.first[i][j] << " ";
        }
        cout << endl;
    }
    cout << "costo total" << res.second << endl;


    return 0;
}
