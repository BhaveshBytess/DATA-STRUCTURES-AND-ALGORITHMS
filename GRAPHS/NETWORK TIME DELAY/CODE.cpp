#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Step 1: Build adjacency list (u -> {v, w})
        vector<vector<pair<int,int>>> adj(n+1);
        for (auto &edge : times) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].push_back({v, w});
        }

        // Step 2: Distance array (initialize with INF)
        vector<int> dist(n+1, INT_MAX);
        dist[k] = 0;

        // Step 3: Min-heap (priority queue -> {time, node})
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, k});

        while (!pq.empty()) {
            auto [time, node] = pq.top();
            pq.pop();

            if (time > dist[node]) continue; // Skip outdated entry

            // Step 4: Relax neighbors
            for (auto &[next, wt] : adj[node]) {
                if (dist[next] > time + wt) {
                    dist[next] = time + wt;
                    pq.push({dist[next], next});
                }
            }
        }

        // Step 5: Find max distance
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX) return -1; // unreachable node
            ans = max(ans, dist[i]);
        }

        return ans;
    }
};
