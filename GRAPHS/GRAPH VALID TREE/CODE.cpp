class Solution {
public:
    bool dfs(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (!dfs(neighbor, node, adj, visited)) {
                    return false;
                }
            } else if (neighbor != parent) {
                // Cycle detected
                return false;
            }
        }
        return true;
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false; // A valid tree must have exactly n - 1 edges

        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(n, false);

        if (!dfs(0, -1, adj, visited)) return false; // Start DFS from node 0

        for (bool v : visited) {
            if (!v) return false; // Not fully connected
        }

        return true; // No cycles and fully connected
    }
};
