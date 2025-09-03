#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1); // -1 = uncolored, 0 = red, 1 = blue

        for (int start = 0; start < n; start++) {
            if (color[start] == -1) { 
                queue<int> q;
                q.push(start);
                color[start] = 0;

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    for (int neigh : graph[node]) {
                        if (color[neigh] == -1) {
                            color[neigh] = 1 - color[node]; // alternate color
                            q.push(neigh);
                        } 
                        else if (color[neigh] == color[node]) {
                            return false; // same color conflict
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    Solution sol;

    // Example 1
    vector<vector<int>> graph1 = {{1,2,3}, {0,2}, {0,1,3}, {0,2}};
    cout << (sol.isBipartite(graph1) ? "true" : "false") << endl; // Output: false

    // Example 2
    vector<vector<int>> graph2 = {{1,3}, {0,2}, {1,3}, {0,2}};
    cout << (sol.isBipartite(graph2) ? "true" : "false") << endl; // Output: true

    return 0;
}
