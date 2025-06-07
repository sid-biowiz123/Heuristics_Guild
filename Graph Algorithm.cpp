#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

bool hasCycle(int n, const vector<vector<pair<int, int>>>& adj) {
    // starts by calculating indegree
    vector<int> indegree(n, 0);
    for(int node = 0; node<n; node++){
        for(auto it = adj[node]){
            int connected_node = it.first;
            int weight = it.second;
            indegree[connected_node]++;
        }
    }
    // need to find nodes with zero incoming nodes 
    queue<int> q;
    for(int i = 0; i<n; i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }

    int count = 0;
    while(!q.empty()){
        int check_node = q.front(); 
        q.pop();
        count++;
        for(auto it : adj[check_node]){
            int connected_node = it.first;
            indegree[connected_node]--; // removing the connected node
            if(indegree[connected_node] == 0){
                q.push(connected_node);
            }
        }

    }

    if(count == n){
        return false; // as in no cycle basically, if the func has to detect cycles, then returns false
    }

    return true; 
}

int dijkstra(int n, int source, int target, const vector<vector<pair<int, int>>>& adj) {
    vector<int> distance(n, INF);
    distance[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min-heap
    pq.push({0, source});

    while(!pq.empty()){
        auto it = pq.top();
        pq.pop();
        int dist = it.first;
        int prim_node = it.second;
        if(dist > distance[prim_node]){
            continue; // why replace if dist is more than shortest dist
        }

        for(auto node : adj[it.second]){
            auto [connected_node, weight] = node;
            if(distance[connected_node] > distance[prim_node] + weight){
                distance[connected_node] = distance[prim_node] + weight;
                pq.push({distance[connected_node], connected_node});
            }
        } // updating shortest distance and parent node of new node
    }
    
    if(distance[target] = INF){
        return -1;
    }

    return distance[target]; // shortest distance of target node
}

// DSU helper function ultimate parent
int find(int u, vector<int>& parent) {
    if (parent[u] != u)
        parent[u] = find(parent[u], parent); // path comp
    return parent[u];
}

// Rank func
bool union_sets(int u, int v, vector<int>& parent, vector<int>& rank) {

    int pu = find(u, parent);
    int pv = find(v, parent);
    
    if (pu == pv) return false; 

    if (rank[pu] < rank[pv]) {
        parent[pu] = pv;
    } else if (rank[pu] > rank[pv]) {
        parent[pv] = pu;
    } else {
        parent[pv] = pu;
        rank[pu]++;
    }

    return true;
}

// Krushkals'
int kruskalMST(int n, vector<array<int, 3>>& edges){
    sort(edges.begin(), edges.end());
    vector<int> parent(n);
    vector<int> rank(n, 0);
    for(int i = 0; i<n; i++){
        parent[i] = i; // every node is its own parent
    }

    int mst_weight_cost = 0;
    int edges_counted = 0;

    for(auto edge : edges){
        int weight = edges[0];
        int og_node = edges[1];
        int conn_node = edges[2];
        // need to check if components are connected
        if(union_sets(og_node, conn_node, parent, rank) == true){
            mst_weight_cost += weight;
            edges_counted++;
            // ideal num of edges (n - 1, cause n nodes)
            if(edges == n - 1){
                break;
            }
        }
    }
    
    return mst_weight_cost; // min sum of edges in spanning tree
    
}

// SSC DAG TOPO Starts Here

void dfs1(int u, const vector<vector<int>>& g, vector<bool>& vis, stack<int>& finish) {
    vis[u] = true;
    for (int v : g[u]) {
        if (!vis[v]) dfs1(v, g, vis, finish);
    }
    finish.push(u);
}

void dfs2(int u, const vector<vector<int>>& rg, vector<int>& comp, int scc_id) {
    comp[u] = scc_id;
    for (int v : rg[u]) {
        if (comp[v] == -1) dfs2(v, rg, comp, scc_id);
    }
}


pair<vector<vector<int>>, vector<int>> getSCCDAGandTopo(
    int n, const vector<vector<pair<int, int>>>& adj) {
    
    vector<vector<int>> g(n);  
    vector<vector<int>> revg(n)
    for (int u = 0; u<n; u++) {
        for (auto [v, w] : adj[u]) {
            g[u].push_back(v);
            revg[v].push_back(u);
        }
    }

    // DFS to store finishing times/order
    vector<bool> vis(n, false);
    stack<int> finish;
    for (int i = 0; i<n; i++) {
        if (vis[i] == false){
            dfs1(i, g, vis, finish);
        } 
    }

    DFS to rev graph and find SCC's through reversing edges
    vector<int> comp(n, -1);
    int scc_id = 0;
    while (!finish.empty()) {
        int u = finish.top(); 
        finish.pop();
        if (comp[u] == -1) {
            dfs2(u, rg, comp, scc_id);
            scc_id++;
        }
    }

    // Buidling the ScC DAG after identifing SSC's
    vector<vector<int>> dag(scc_id);
    set<pair<int, int>> added;
    for (int u = 0; u<n; u++) {
        for (int v : g[u]) {
            int cu = comp[u]
            int cv = comp[v];
            if (cu != cv && !added.count({cu, cv})) {
                dag[cu].push_back(cv);
                added.insert({cu, cv});
            }
        }
    }

    // topo sort
    vector<int> indeg(scc_id, 0);
    for (int u = 0; u<scc_id; u++) {
        for (int v : dag[u]){
            indeg[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i<scc_id; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        topo.push_back(u);
        for (int v : dag[u]) {
            if (indeg[v]-- == 0){
                q.push(v);
            }
        }
    }
    return {dag, topo};
}




int main() {
    int n, m; 
    vector<array<int, 3>> edges;
    vector<vector<pair<int, int>>> adjList(n); 
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v}); // trust me, helps with simplifyin Kruskal's durin sortinzz
        adjList[u].push_back({v, w}); 
    }

    // sykle detection
    bool cycle = hasCycle(n, adjList);
    if(cycle == true){
        cout << "Cycle is Present" << endl;
    }
    else{
        cout << "Cycle is not Present" << endl;
    }

    // shortest path(plehs no negative weights):- hence dijkstra's
    int u, v;
    cin >> u >> v;
    int shortest = dijkstra(n, u, v, adjList);
    cout << "Shortest path from " << u << " to " << v << "is " << shortest << endl;

    // MST value
    int mstWeight = kruskalMST(n, edges);
    cout << "MST Value: " << mstWeight << endl;

    // Strongly Conn Comps and a DAG creation and Topo sorting it
    auto [SCCs, topoOrder] = getSCCDAGandTopo(n, adjList);
    cout << "Topological sort of SCC DAG:" << endl;
    for (int node : topoOrder){
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
