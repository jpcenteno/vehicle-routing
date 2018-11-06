#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <tuple>
#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>
#include <list>
#include <climits>
#include <queue>
#include <math.h> 
#include "lib/data.h"
#include "savings.h"

using namespace std;

void calcularDist(MatrizDist &grafo, vector<Node>& nodos){
    int n = nodos.size();
    int distM;
    //inicialmente toda la matriz tiene ceros, que luego quedaran en la diagonal unicamente
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            distM = round(sqrt(pow((nodos[i].x - nodos[j].x),2) + pow((nodos[i].y - nodos[j].y),2)));
            grafo[i][j] = distM;	//La matriz de distancias es simetrica, y tiene ceros en la diagonal
            grafo[j][i] = distM;
        }
    }

}


int FIXME_main(){

	//const Instance instance;

	/*creo matriz distancias*/
	int n = instance.size();
	MatrizDist dist(n, vector<int>(n, 0));
	vector<Node> nodos = instance.getNodes();
	//vector<Node> nodos = {{40,40,0,true},{22,22,18,false},{36,26,26,false},{21,45,11,false},{45,35,30,false},{55,20,21,false},{55,45,16,false},{26,59,29,false},{55,65,37,false}};
	calcularDist(dist, nodos);

	/*Calcular savings */
	priority_queue<Saving, vector<Saving>> savings_pq;

	int s;
	for(int i = 0; i<n; i++){
		for(int j = i+1; j<n; j++){
			s = dist[i][0] + dist[0][j] - dist[i][j];
			savings_pq.push({i,j,s});	
		}	
	} 



	vector<int> nro_ruta(n, -1);
	vector<Ruta> rutas;
	vector<int> noFactibles;
	int C = instance.getCapacity();
	/*Salida de prueba para savings*/
	while(!savings_pq.empty()){
		Saving sav = savings_pq.top();
		savings_pq.pop();

		if(nodos[sav.i].demand + nodos[sav.j].demand > C){	//Saving descartado
			continue;
		}

		if(nro_ruta[sav.i] > -1 && nro_ruta[sav.j] > -1){ //ver bien!
			continue;
		}

		if(nro_ruta[sav.i] == -1 && nro_ruta[sav.j] == -1){
			Ruta cluster;
			cluster.camino.push_back(sav.i);
			cluster.camino.push_back(sav.j);
			cluster.capacidad = nodos[sav.i].demand + nodos[sav.j].demand;
			rutas.push_back(cluster);
			nro_ruta[sav.i] = rutas.size()-1;
			nro_ruta[sav.j] = rutas.size()-1;
		}else if(nro_ruta[sav.i] > -1 && nro_ruta[sav.j] == -1){

			if (nodos[sav.j].demand + rutas[nro_ruta[sav.i]].capacidad > C) 
				continue;

			if(rutas[nro_ruta[sav.i]].camino.front() == sav.i){
				rutas[nro_ruta[sav.i]].camino.push_front(sav.j);
				nro_ruta[sav.j] = nro_ruta[sav.i];
	
			}else if(rutas[nro_ruta[sav.i]].camino.back() == sav.i){
				rutas[nro_ruta[sav.i]].camino.push_back(sav.j);
				nro_ruta[sav.j] = nro_ruta[sav.i];
			}
		
		}else{
			if (nodos[sav.i].demand + rutas[nro_ruta[sav.j]].capacidad > C) 
				continue;
			if(rutas[nro_ruta[sav.j]].camino.front() == sav.j){
				rutas[nro_ruta[sav.j]].camino.push_front(sav.i);
				nro_ruta[sav.i] = nro_ruta[sav.j];
	
			}else if(rutas[nro_ruta[sav.j]].camino.back() == sav.j){
				rutas[nro_ruta[sav.j]].camino.push_back(sav.i);
				nro_ruta[sav.i] = nro_ruta[sav.j];
			}
		
		}
	}


	return 0;
}


