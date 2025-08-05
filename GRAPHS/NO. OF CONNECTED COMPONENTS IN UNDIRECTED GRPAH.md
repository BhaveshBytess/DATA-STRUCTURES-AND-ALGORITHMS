Here’s the **final C++ code** for **"Number of Connected Components in an Undirected Graph"**, using **DFS** and your preferred learning style (simple, readable, and clean):

```cpp
class Solution {
public:
    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited);
            }
        }
    }

    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n); // adjacency list

        // Build graph
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u); // because undirected
        }

        vector<bool> visited(n, false);
        int components = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                components++;        // new component found
                dfs(i, adj, visited);
            }
        }

        return components;
    }
};
```

---

### 🧠 Quick Intuition Recap:

- Each unvisited node → start of a new component.
    
- DFS marks all reachable nodes from it.
    
- Every time you enter DFS from the main loop, that’s a new component.
    

Let me know when you’re ready to do the **BFS version** or move to the next graph problem like **Rotten Oranges** or **Cycle Detection**.