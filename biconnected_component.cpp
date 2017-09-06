#include <bits/stdc++.h>

using namespace std;

#define f(in,to) for (int i = in; i < to; i++)
#define g(in,to) for (int j = in; j < to; j++)

int num = 0;
vector<vector<int> > vertices; // vetor com a lista de adjacencias dos vertices
set<int> articulation_points; // conjunto com os pontos de articulação do grafo
/*
    low = low do vertice, ex: low[5] = 0
    d = numero do vertice na DFS, ex: d[5] = 5
    vis = variavel para saber se o vertice já foi visitado, -1 para ainda não visitado, 1 para visitando e 2 para já visitado
*/
int *low, *d, *vis;

bool root_articulation(int v, int tam) {
    // utilizado para saber se a raiz é um ponto de articulação
    int art = 0;
    f(0, tam) {
        art += low[vertices[v][i]];
    }
    // a raiz é um ponto de articulação apenas se tiver pelo menos um vertice vizinho a ela com low diferente do low da raiz
    return art != (low[v]*tam);
}

int grafo(int v, int pai, int raiz) {
    // utilizado para encontrar os pontos de articulação e os componentes biconexos do grafo
    low[v] = d[v] = num++;
    vis[v] = 1;
    f(0,vertices[v].size()) {
        // utilizado para visitar todas os vertices que tem arestas saindo de v
        if (vis[vertices[v][i]] == -1) {
            grafo(vertices[v][i], v, raiz);
            low[v] = min(low[v], low[vertices[v][i]]);
            cout << "(" << v + 1 << ", " << vertices[v][i] + 1 << ") ";
            if (((low[vertices[v][i]] >= d[v] && v != raiz) || (v == raiz && root_articulation(v, i + 1))) && d[v] != low[vertices[v][i]]) {
                // verificando se o vertice é um ponto de articulação
                articulation_points.insert(v);
                cout << "." << endl;
            }
        } else if(vis[vertices[v][i]] == 2){
            // utilizado quando existe circulos no grafo
            cout << "(" << v+1 << ", " << vertices[v][i] + 1 << ") ";
            if (((low[vertices[v][i]] >= d[v] && v != raiz) || (v == raiz && root_articulation(v, i + 1)))) {
                // verificando se o vertice é um ponto de articulação
                articulation_points.insert(v);
                cout << "." << endl;
            }
            if(vertices[v][i] != pai){
                low[v] = min(low[v], d[vertices[v][i]]);
            }
        } else if(vertices[v][i] != pai){
            low[v] = min(low[v], d[vertices[v][i]]);
        }
    }
    vis[v] = 2;
}

int main() {
    int k;
    cin >> k;
    f(0,k) {
        // lendo as k instancias
        int v, e;
        cin >> e >> v;
        vertices.resize(v);
        low = (int*)malloc(v*sizeof(int));
        d = (int*)malloc(v*sizeof(int));
        vis = (int*)malloc(v*sizeof(int));
        num = 0;
        g(0, v) {
            low[j] = d[j] = vis[j] = -1;
        }
        int root = -1;
        g(0,e) {
            int u, v;
            cin >> u >> v;
            if (root == -1) root = u - 1;
            vertices[u-1].push_back(v-1);
            vertices[v-1].push_back(u-1);
        }
        cout << "O grafo " << i + 1 << " contém os seguintes componentes biconexos" << endl;
        grafo(root, -1, root);
        if (articulation_points.find(root) == articulation_points.end()) cout << "." << endl;
        cout << endl;
        cout << "O grafo " << i + 1 << " contém os seguintes vértices de articulação" << endl;
        
        for(set<int>::iterator it = articulation_points.begin();it!=articulation_points.end();it++) {
            // implimindo os pontos de articulação do grafo
            cout << *it  + 1 << endl;
        }
        cout << endl;

        g(0,v) {
            vis[j] = -1;
        }

        vertices.clear();
        articulation_points.clear();
    }
}