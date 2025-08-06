class Solution {
public:
    bool dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& pathVisited, stack<int>& st) {
        visited[node] = true;
        pathVisited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (!dfs(neighbor, adj, visited, pathVisited, st))
                    return false;
            } else if (pathVisited[neighbor]) {
                // cycle found
                return false;
            }
        }
        
        pathVisited[node] = false; // backtrack
        st.push(node); // topo sort
        return true;
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        
        for (auto& edge : prerequisites) {
            adj[edge[1]].push_back(edge[0]); // u -> v (take u before v)
        }
        
        vector<bool> visited(numCourses, false);
        vector<bool> pathVisited(numCourses, false);
        stack<int> st;
        
        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {
                if (!dfs(i, adj, visited, pathVisited, st)) {
                    return {}; // cycle detected
                }
            }
        }
        
        vector<int> topoOrder;
        while (!st.empty()) {
            topoOrder.push_back(st.top());
            st.pop();
        }
        return topoOrder;
    }
};
