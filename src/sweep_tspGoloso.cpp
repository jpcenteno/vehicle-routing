#include "sweep_tspGoloso.h"


std::vector<std::vector<Angular>> sweep(const std::vector<Node>& nodos, uint C){
    std::vector<std::vector<Angular>> clusteres;
    size_t n = nodos.size();
    unsigned int carga = 0;
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

pair<vector<size_t>, int> tspGoloso(vector<Angular>& cluster, const MatrizDist& dist){
	size_t n = cluster.size();
    vector<bool> visitados(n, false);
    size_t cant_nodos = 0;
    int costo = 0;
    size_t indice_min = cluster.size() - 1; //El deposito se agrego siempre como ultimo elemento del cluster
    unsigned int min = 0;
    size_t i;
    std::vector<size_t> camino;
    while(cant_nodos < n){
        camino.push_back(cluster[indice_min].id);
        visitados[indice_min] = true;
        costo += min;
        cant_nodos++;
        min = INT_MAX;
        i = indice_min;

        for(size_t j=0; j<n; j++) {
            if (cluster[i].id != cluster[j].id && !visitados[j] && dist[cluster[i].id][cluster[j].id] < min) {
                min = dist[cluster[i].id][cluster[j].id];
                indice_min = j;
            }
        }
    }

    costo += dist[camino.back()][0];
    camino.push_back(0);

    return {camino, costo};
}


PathList ruteo(vector<vector<Angular> >& clusters, const MatrizDist& dist){
    PathList rutas;
    rutas.second = 0;
    pair<vector<size_t>, int> tsp;
    for (size_t i = 0; i < clusters.size(); ++i) {
        tsp = tspGoloso(clusters[i], dist);
        rutas.first.push_back(tsp.first);
        rutas.second += tsp.second;
    }
    return rutas;
}
	

PathList Sweep::operator()(const Instance& instance) const {
	vector<vector<Angular>> clusters = sweep(instance.getNodes(), instance.getCapacity());
	PathList res = ruteo(clusters, instance.getDistances());
	return res;
}

/* Salida dado un pathlist*/
/* PathList res <- sweep;
    cout<< res.first.size() << endl;

    for(int i=0; i<res.first.size(); i++){
        int tam_i = (res.first)[i].size();
        for(int j = 0;j < tam_i; j++){
            cout << (res.first)[i][j] << " ";
        }
        cout << endl;
    }
    cout << res.second << endl;
*/
