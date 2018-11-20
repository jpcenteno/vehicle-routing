#include "goloso.h"


PathList Goloso::operator()(const Instance& instance) const { 
	PathList rutas;
	size_t n = instance.size();
	vector<Node> nodos = instance.getNodes();
	MatrizDist dist = instance.getDistances();
	vector<bool> visitados(n, false); 
	size_t cant_nodos = 1;
	int costo = 0;
	unsigned int carga;
	size_t indice_min, i;
    float min;
	unsigned int C = instance.getCapacity();


	while(cant_nodos < n){
		vector<size_t> camino;
		carga = 0;
		indice_min = 0;
		min = 0;
		while(((carga + nodos[indice_min].demand) <= static_cast<unsigned int>(C)) && (cant_nodos < n)){ 
			carga += nodos[indice_min].demand;
			camino.push_back(indice_min);
			visitados[indice_min] = true;
			costo += min; 
		
			if(indice_min != 0) cant_nodos++;   //Para no sumar el cero cada vez
			min = INT_MAX;
			i = indice_min;

			for(size_t j=0; j<n; j++){
				if(i != j && !visitados[j] && dist[i][j] < min && nodos[j].demand <= C){
					min = dist[i][j];
					indice_min = j;

				}else if(nodos[j].demand > C){		//si era infactible lo pongo como vistado para no volverlo a visitar otra vez.
					visitados[j] = true;
				}
			}
		} 
	
		costo += dist[camino.back()][0];
		camino.push_back(0);
		if(camino.size() > 2){		//Evito agregar caminos de tipo (0,0) cuando en el medio hubo infactibles por ejemplo.
			rutas.first.push_back(camino);
		}	
	}
		
		rutas.second = costo;
		return rutas;
		
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
		



