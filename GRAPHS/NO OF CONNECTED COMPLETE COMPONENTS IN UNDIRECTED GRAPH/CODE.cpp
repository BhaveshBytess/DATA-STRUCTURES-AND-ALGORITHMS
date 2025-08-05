class Solution {

public:

    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited,int& edges,int& nodes){

        visited[node] = true;

        nodes++;

        edges += adj[node].size();

        for(int neighbor : adj[node]){

            if(!visited[neighbor]){

                dfs(neighbor,adj,visited,edges,nodes);

            }

        }

    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        vector<vector<int>> adj(n);

        for(auto edge : edges){

            int u = edge[0];

            int v = edge[1];

            adj[u].push_back(v);

            adj[v].push_back(u);

        }

  

        vector<bool> visited(n,false);

        int count = 0;

        for(int i=0;i<n;i++){

            if(!visited[i]){

                int edges = 0;

                int nodes = 0;

  

                dfs(i,adj,visited,edges,nodes);

  

                edges = edges/2;

                if(edges == nodes*(nodes-1)/2){

                    count++;

                }

                else{

                    continue;

                }

            }

        }

  

        return count;

    }

};
