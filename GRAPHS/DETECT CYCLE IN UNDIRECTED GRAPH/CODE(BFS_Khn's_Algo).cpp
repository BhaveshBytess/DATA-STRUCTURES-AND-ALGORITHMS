class Solution {
public:
    bool canFinish(int n, vector<vector<int>>& edges) {
        vector<int> adj[n];
        vector<int> indegree(n, 0);

        // Build adjacency list and indegree array
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            indegree[v]++;
        }

        // Queue for nodes with indegree 0
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0)
                q.push(i);
        }

        int count = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++;

            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }

        // If we processed all nodes, no cycle
        return count == n;
    }
};
