#include <bits/stdc++.h>

using namespace std;

#define f(in,to) for (int i = in; i < to; i++)

int num = 0;
vector<vector<int> > vertices;
set<int> articulation_points;
int *low, *d, *vis;

int dfs(int v, int pai, int raiz) {
    low[v] = d[v] = num++;
    // cout << num << " num " << low[v] << endl;
    vis[v] = 1;
    f(0,vertices[v].size()) {
        // cout << low[v] << " " << v + 1 << " antes 1" << endl;
        if (vis[vertices[v][i]] == -1) {           
            // if (vertices[vertices[v][i]].size() <= 1) {
            //     cout << vertices[v][i] + 1 << endl;
            // }
            dfs(vertices[v][i], v, raiz);
            // cout << v + 1 << endl;
            low[v] = min(low[v], low[vertices[v][i]]);
            if (low[vertices[v][i]] >= d[v] && v != raiz) {
                // cout << low[v] << " " << low[vertices[v][i]] << " depois" << v + 1<< endl;
                // cout << endl << v + 1 << endl;
                articulation_points.insert(v);
            }
        } else if(vertices[v][i] != pai){
            low[v] = min(low[v], d[vertices[v][i]]);
        }
    }
    vis[v] = 2;
}

set<int> component;

int biconnect(int v, int pai, int raiz) {
    // low[v] = d[v] = num++;
    // cout << num << " num " << low[v] << endl;
    vis[v] = 1;
    f(0,vertices[v].size()) {
        // cout << low[v] << " " << v + 1 << " antes 1" << endl;
        if (vis[vertices[v][i]] == -1) {           
            if (vertices[vertices[v][i]].size() <= 1) {
                // cout << vertices[v][i] + 1 << endl;
                component.insert(vertices[v][i] + 1);
            }
            biconnect(vertices[v][i], v, raiz);
            // cout << v + 1 << endl;
            component.insert(v+1);
            // low[v] = min(low[v], low[vertices[v][i]]);
            if (articulation_points.find(v) != articulation_points.end()) {
                // cout << low[v] << " " << low[vertices[v][i]] << " depois" << v + 1<< endl;
                // cout << endl << v + 1 << endl;
                component.insert(v + 1);
                for (set<int>::iterator it = component.begin(); it!=component.end();it++) {
                    cout << *it << endl;
                }
                cout << endl;
                component.clear();
                component.insert(v + 1);
            }
        } 
        // else if(vertices[v][i] != pai){
        //     low[v] = min(low[v], d[vertices[v][i]]);
        // }
    }
    vis[v] = 2;
}

bool root_articulation(int v) {
    int art = 0;
    f(0, vertices[v].size()) {
        art += low[vertices[v][i]];
    }
    return art != (low[v]*vertices[v].size());
}

int main() {
    int v, e;
    while (cin >> v >> e, v!=0) {
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
        biconnect(root, -1, root);

        f(0,v) {
            // cout << i + 1 << ": low=" << low[i] << ", d=" << d[i] << endl;
            vertices[i].clear();
        }
        if(component.size() > 1) {
            for (set<int>::iterator it = component.begin(); it!=component.end();it++) {
                cout << *it << endl;
            }
        }
        component.clear();
        articulation_points.clear();
    }
}