class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);     // Adjacency list
        vector<int> indegree(numCourses, 0);     // Indegree for each course

        // Build the graph
        for (auto& pre : prerequisites) {
            int course = pre[0];
            int prereq = pre[1];
            adj[prereq].push_back(course);
            indegree[course]++;
        }

        // Queue for BFS
        queue<int> q;

        // Add all nodes with indegree 0
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int visitedCount = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            visitedCount++;

            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // If we visited all courses, no cycle exists
        return visitedCount == numCourses;
    }
};
