#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool dfs(int node, int d, int n, vector<vector<int>> &graph, vector<int> &path, vector<int> &vis){
    vis[node] = 1;
    path.push_back(node);
    
    if(d == n){
        for(auto it : graph[node]){
            if(it == 0){
                path.push_back(0);
                return true;
            }
        }
        vis[node] = 0;
        path.pop_back();
        return false;
    }
    
    
    for(auto it : graph[node]){
        if(vis[it] == 0){
           if(dfs(it, d + 1, n, graph, path, vis)){
               return true;
           }
        }
    }
    
    vis[node] = 0;
    path.pop_back();
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    vector<int> path;
    vector<int> vis(n, 0);
    
    for(int i = 0; i<m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    bool check = dfs(0, 1, n, graph, path, vis);
    if(!check){
        cout << "-1" << endl;
    }
    else{
        cout << "1" << endl;
        for(int i = 0; i<=n; i++){
            cout << path[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
