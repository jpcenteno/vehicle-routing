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
#include <deque>
#include <math.h> 
#include "lib/data.h"

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


deque<Saving> cluster;
 

/*Salida de prueba para savings
while(!savings_pq.empty()){
	deque<Saving> cluster;
	
	Saving sav = savings_pq.top();
	cluster.push(sav.i);
	cluster.push(sav.j);
	cout << sav.s << endl;
	savings_pq.pop();
}

*/

return 0;
}


