#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for(int i = 0; i<m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int leng = (1 << n);
    vector<vector<int>> dp(leng, vector<int> (n, 0));
    vector<vector<int>> node(leng, vector<int>(n, -1));
    
    dp[1][0] = 1;
    for(int i = 1; i<leng; i++){
        for(int j = 0; j<n; j++){
            if(dp[i][j] == 0){
                continue;
            }
            if((i & (1 << j)) == 0){
                continue;
            }
            
            for(auto it : graph[j]){
                if((i & (1 << it)) != 0){
                    continue;
                }
                if(dp[i | (1 << it)][it] == 0){
                    dp[i | (1 << it)][it] = 1;  
                    node[i | (1 << it)][it] = j;
                }

            }
        }
    }
    
    bool ans = false;
    int end = -1;
    for(int i = 1; i<n; i++){
        if(dp[leng - 1][i] == 1){
            bool checker = false;
            for (auto neighbor : graph[i]) {
                if (neighbor == 0) {
                    checker = true;
                    break;
                }
            }
            if(checker){
                ans = true;
                end = i;
                break;
            }
        }
    }
    
    if(ans == false){
        cout << "-1";
    }
    
    else{
        cout << "1" << endl;
        vector<int> path;
        int mask = leng - 1;
        int check = end;
        while (check != -1) {
            path.push_back(check);
            int prev = node[mask][check];
            mask ^= (1 << check);
            check = prev;
        }
        
        reverse(path.begin(), path.end());
        path.push_back(0);
        for (auto it : path){
            cout << it << " ";
        }
        cout << endl;

    }
    
    
    return 0;
}
