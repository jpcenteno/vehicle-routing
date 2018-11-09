#include "goloso.h"


PathList Goloso::operator()(const Instance& instance) const { 
	vector<vector<int>> rutas;
	int n = instance.size();
	vector<Node> nodos = instance.getNodes();
	MatrizDist dist = instance.getDistances();
	vector<bool> visitados(n, false); 
	int cant_nodos = 1;
	int costo = 0;
	int carga;
	int indice_min, min, i;
	int C = instance.getCapacity();


	while(cant_nodos < n){
		vector<int> camino;
		carga = 0;
		indice_min = 0;
		min = 0;
		while(((carga + nodos[indice_min].demand) <= C) && (cant_nodos < n)){ 
			carga += nodos[indice_min].demand;
			camino.push_back(indice_min);
			visitados[indice_min] = true;
			costo += min; 
		
			if(indice_min != 0) cant_nodos++;   //Para no sumar el cero cada vez
			min = INT_MAX;
			i = indice_min;

			for(int j=0; j<n; j++){
				if(i != j && !visitados[j] && dist[i][j] < min){
					min = dist[i][j];
					indice_min = j;

				}
			}
		} 
	
		costo += dist[camino.back()][0];
		camino.push_back(0);
		rutas.push_back(camino);
	
	}
		/*Salida de Prueba*/
		/*cout << rutas.size() << endl;
		for(int i= 0; i<rutas.size();i++){
			for(int j= 0; j<rutas[i].size();j++){
			cout << rutas[i][j] << " " ;

			}
			cout << endl;
		}
		cout << costo <<endl;*/

}

//printear: 	cantidad de camiones rutas.size() 
//		caminos separados por una linea    for para cada camino de rutas
//		costo_total : costo	
		



