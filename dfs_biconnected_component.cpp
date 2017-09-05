#include <bits/stdc++.h>

using namespace std;

#define f(in,to) for (int i = in; i < to; i++)

int num = 0;
vector<vector<int> > vertices;
set<int> articulation_points;
int *low, *d, *vis;

int criar_arvore(int v, int tam, int raiz) {
    vis[v] = 1;
    f(0,vertices[v].size()) {
        if (vis[vertices[v][i]] == -1) { 
            if (vertices[v].size() > 1 && i + 1 < vertices[v].size()) criar_arvore(vertices[v][i], vertices[v].size(), v);
            else criar_arvore(vertices[v][i], tam, raiz);
        }
    }
    cout << raiz << " " << tam << endl;
    if (vertices[v].size() <= 1 && raiz != -1) {
        cout << v + 1 << " back" << endl;
        vertices[v].push_back(raiz);
        vertices[raiz].push_back(v);
    }

    vis[v] = 2;
}

int dfs(int v, int pai, int raiz) {
    low[v] = d[v] = num++;
    vis[v] = 1;
    f(0,vertices[v].size()) {
        if (vis[vertices[v][i]] == -1) { 
            dfs(vertices[v][i], v, raiz);
            low[v] = min(low[v], low[vertices[v][i]]);
            if (low[vertices[v][i]] >= d[v] && v != raiz) {
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
    vis[v] = 1;
    f(0,vertices[v].size()) {
        if (vis[vertices[v][i]] == -1) {           
            if (vertices[vertices[v][i]].size() <= 1) {
                component.insert(vertices[v][i] + 1);
            }
            biconnect(vertices[v][i], v, raiz);
            component.insert(v+1);
            if (articulation_points.find(v) != articulation_points.end()) {
                component.insert(v + 1);
                for (set<int>::iterator it = component.begin(); it!=component.end();it++) {
                    cout << *it << endl;
                }
                cout << endl;
                component.clear();
                component.insert(v + 1);
            }
        }
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
        if (vertices[root].size() > 1) {
            criar_arvore(root, vertices[root].size(), root);
        } else {
            criar_arvore(root, 0, -1);
        }
        f(0,v) {
            vis[i] = -1;
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