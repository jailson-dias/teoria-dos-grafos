#include <bits/stdc++.h>

using namespace std;

#define f(in,to) for (int i = in; i < to; i++)

int num = 0;
vector<vector<int> > vertices; 
set<int> articulation_points; // conjunto com os pontos de articulação do grafo
/*
    low = low do vertice, ex: low[5] = 0
    d = numero do vertice na DFS, ex: d[5] = 5
    vis = variavel para saber se o vertice já foi visitado, -1 para ainda não visitado, 1 para visitando e 2 para já visitado
*/
int *low, *d, *vis;

bool root_articulation(int v) {
    // utilizado para saber se a raiz é um ponto de articulação
    int art = 0;
    f(0, vertices[v].size()) {
        art += low[vertices[v][i]];
    }
    // a raiz é um ponto de articulação apenas se tiver pelo menos vertice vizinho a ela com low diferente do low da raiz
    return art != (low[v]*vertices[v].size());
}

int dfs(int v, int pai, int raiz) {
    // DFS para encontrar os pontos de articulação do grafo
    low[v] = d[v] = num++;
    vis[v] = 1;
    f(0,vertices[v].size()) {
        // utilizado para visitar todas os vertices que tem arestas saindo de v
        if (vis[vertices[v][i]] == -1) {
            dfs(vertices[v][i], v, raiz);
            low[v] = min(low[v], low[vertices[v][i]]);
            cout << "(" << v+1 << ", " << vertices[v][i] + 1 << ")" << endl;
            if ((low[vertices[v][i]] >= d[v] && v != raiz) || (v == raiz && root_articulation(v))) {
                // verificando se o vertice é um ponto de articulação
                articulation_points.insert(v);
                cout << endl;
            }
        } else if(vis[vertices[v][i]] == 2){
            cout << "(" << v+1 << ", " << vertices[v][i] + 1 << ")" << endl;
            if(vertices[v][i] != pai){
                low[v] = min(low[v], d[vertices[v][i]]);
            }
        } else if(vertices[v][i] != pai){
            low[v] = min(low[v], d[vertices[v][i]]);
        }
    }
    vis[v] = 2;
}

set<int> component;

int biconnect(int v, int pai) {
    // utilizado para encontrar os componentes biconexos
    vis[v] = 1;
    f(0,vertices[v].size()) {
        // utilizado para visitar todos os vertices que tem arestas saindo de v
        if (vis[vertices[v][i]] == -1) {           
            // if (vertices[vertices[v][i]].size() <= 1) {
                // cout << vertices[v][i] + 1 << endl;
                // component.insert(vertices[v][i] + 1);
            // }
            biconnect(vertices[v][i], v);
            // component.insert(v+1);
            cout << "(" << v+1 << ", " << vertices[v][i] + 1 << ")" << endl;
            if (articulation_points.find(v) != articulation_points.end()) {
                // se v for um ponto de articulação, então v vai está nos dois componentes biconexos
                // e já pode imprimir os vertices do componente biconexo
                // component.insert(v + 1);
                // for (set<int>::iterator it = component.begin(); it!=component.end();it++) {
                //     cout << *it << endl;
                // }
                cout << endl;
                // component.clear();
                // component.insert(v + 1);
            }
        }
        else if(vis[vertices[v][i]] == 2){
           cout << "(" << v+1 << ", " << vertices[v][i] + 1 << ")" << endl;
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
        f(0, v) {
            low[i] = d[i] = vis[i] = -1;
        }
        int root = -1;
        f(0,e) {
            int u, v;
            cin >> u >> v;
            if (root == -1) root = u - 1;
            vertices[u-1].push_back(v-1);
            vertices[v-1].push_back(u-1);
        }
        dfs(root, -1, root);
        if (root_articulation(root)) articulation_points.insert(root);
        cout << "pontos: " << articulation_points.size() << endl;

        f(0,v) {
            vis[i] = -1;
        }
        // biconnect(root, -1);

        vertices.clear();
        // if(component.size() > 1) {
        //     for (set<int>::iterator it = component.begin(); it!=component.end();it++) {
        //         cout << *it << endl;
        //     }
        // }
        component.clear();
        articulation_points.clear();
    }
}