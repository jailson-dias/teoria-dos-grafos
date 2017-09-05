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
            // cout << low[v] << " " << v + 1 << " antes" << endl;
            dfs(vertices[v][i], v, raiz);
            low[v] = min(low[v], low[vertices[v][i]]);
            if (low[vertices[v][i]] >= d[v] && v != raiz) {
                // cout << low[v] << " " << low[vertices[v][i]] << " depois" << v + 1<< endl;
                articulation_points.insert(v);
            }
        } else if(vertices[v][i] != pai){
            // cout << "else" << endl;
            low[v] = min(low[v], d[vertices[v][i]]);
        }
    }
    vis[v] = 2;
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
        // cout << "articulation points" << endl;
        cout << articulation_points.size() << endl;
        // for(set<int>::iterator i = articulation_points.begin();i!=articulation_points.end();i++) {
        //     cout << *i << endl;
        // }
        // cout << "low" << endl;

        f(0,v) {
            // cout << i + 1 << ": low=" << low[i] << ", d=" << d[i] << endl;
            vertices[i].clear();
        }
        articulation_points.clear();
        // free(low);
        // free(d);
        // free(vis);
        // free(vertices);
        // cout << articulation_points.size() << endl;
    }
}