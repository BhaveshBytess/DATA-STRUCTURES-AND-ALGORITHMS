class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        vector<int> indegree(numCourses, 0);
        
        // Build adjacency list and compute indegrees
        for (auto& pre : prerequisites) {
            int u = pre[1], v = pre[0];
            adj[u].push_back(v);
            indegree[v]++;
        }
        
        // Push all nodes with indegree 0 into queue
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }
        
        vector<int> topoOrder;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topoOrder.push_back(node);
            
            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }
        
        // If all courses are not included, return empty
        if (topoOrder.size() != numCourses)
            return {};
        
        return topoOrder;
    }
};
