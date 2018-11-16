#include "sweep_tspGoloso.h"




vector<vector<Node>> sweep(const vector<Node>& nodos, int C){
	vector<vector<Node>> clusteres;	
	int n = nodos.size();
	int carga = 0;
	priority_queue<Angular, vector<Angular>, greater<Angular>> sweptPoints;  //vector<Angular> es la estructura sobre la que se arma la priority queue
	Angular punto;
	for(uint i = 1; i<n; i++){
		int dif_x = nodos[i].x - nodos[0].x;
		int dif_y = nodos[i].y - nodos[0].y;
		if(dif_x >= 0 && dif_y>=0){   //Primer cuadrante			
			punto.alfa = atan(abs(dif_y/dif_x));		 
		}else if(dif_x < 0 && dif_y >= 0){		//segundo cuadrante
			punto.alfa = M_PI - atan(abs(dif_y/dif_x));
		}else if(dif_y < 0 && dif_x<=0){		//tercer cuadrante
			punto.alfa = M_PI + atan(abs(dif_y/dif_x));
		}else{
			punto.alfa = 2*M_PI - atan(abs(dif_y/dif_x));
		}
		punto.p = nodos[i];
		sweptPoints.push(punto);
	}

		vector<Node> cluster;
		while(!sweptPoints.empty()){	
			punto = sweptPoints.top();
			if(punto.p.demand + carga <= C){
				cluster.push_back(punto.p);
				carga+= punto.p.demand;
				sweptPoints.pop();
			}else{
				if(punto.p.demand > C){   //es un infactible lo salteo
					sweptPoints.pop();
					continue;
				}	
				if(cluster.size() != 0){	// aca el punto es factible y no lo popeo para que en la siguiente iteracion sea agregado a 												otro cluster
					cluster.push_back(nodos[0]);	//En todos los clusteres tiene que estar el punto del deposito					
					clusteres.push_back(cluster);
					cluster.clear();
					carga = 0;
				}	
	
					
			} 
		}
		if(cluster.size() > 0 && clusteres.size() == 0){  //caso unico cluster
			cluster.push_back(nodos[0]);				
			clusteres.push_back(cluster);
		}
	
		return clusteres;
}


pair<vector<int>, int> Sweep::tspGoloso(vector<Node>& cluster, const Instance & instance) const{
	int n = instance.size();
	MatrizDist dist = instance.getDistances();
	vector<bool> visitados(n, false); 
	int cant_nodos = 0;
	int costo = 0;
	int indice_min = 0; 
	int min = 0;
	int i;
	vector<int> camino;
	while(cant_nodos < n){ 
		camino.push_back(indice_min);
		visitados[indice_min] = true;
		costo += min; 
		cant_nodos++;   
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

	return {camino, costo};	
}

 
PathList Sweep::ruteo(vector<vector<Node> >& clusters, const Instance& instance) const{
	PathList rutas;
	rutas.second = 0;
	pair<vector<int>, int> tsp;
	for (int i = 0; i < clusters.size(); ++i) {
		tsp = tspGoloso(clusters[i], instance); 	
		rutas.first.push_back(tsp.first);
		rutas.second += tsp.second; 
	}
	return rutas;
}
	

PathList Sweep::operator()(const Instance& instance) const {
	vector<vector<Node>> clusters = sweep(instance.getNodes(), instance.getCapacity());
	PathList res = ruteo(clusters, instance);
	return res;
}

int main(){
return 0;
}
