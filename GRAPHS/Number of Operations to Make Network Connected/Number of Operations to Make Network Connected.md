
### 1319. Number of Operations to Make Network Connected

You are given an integer `n` and a 2D array `connections` where `connections[i] = [ai, bi]` represents a connection between computer `ai` and computer `bi`.  
Any computer can reach any other computer directly or indirectly through the network of connections.

You can extract certain cables between two directly connected computers and place them between any pair of disconnected computers to make them directly connected.

Return _the minimum number of times you need to do this_ in order to make all the computers connected.  
If it is not possible, return `-1`.

---

#### Example 1:

```
Input: n = 4, connections = [[0,1],[0,2],[1,2]]
Output: 1
Explanation: Remove cable between [1,2] and place it between [1,3].
```

#### Example 2:

```
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
Output: -1
Explanation: There are not enough cables.
```

#### Example 3:

```
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[2,3],[4,5]]
Output: 1
```

---

#### Constraints:

- `1 <= n <= 10^5`
    
- `1 <= connections.length <= min(n * (n - 1) / 2, 10^5)`
    
- `0 <= ai, bi < n`
    
- `ai != bi`
    
- No repeated connections, no self-connections.
    

---


# CODE :

### DFS :

```cpp
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        // Step 1: Check if we have enough cables
        if (connections.size() < n - 1) {
            return -1;
        }

        // Step 2: Build adjacency list
        vector<vector<int>> adj(n);
        for (auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }

        // Step 3: Count connected components using DFS
        vector<bool> visited(n, false);
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited);
                components++;
            }
        }

        // Step 4: Return operations needed
        return components - 1;

    }

private:
    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited);
            }
        }
    }

};
```


### DSU :

```cpp
class Solution {
public:
    vector<int> parent, rank;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return; // already connected

        if (rank[rx] < rank[ry]) {
            parent[rx] = ry;
        } else if (rank[ry] < rank[rx]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rank[rx]++;
        }
    }

    int makeConnected(int n, vector<vector<int>>& connections) {
        if ((int)connections.size() < n - 1) return -1; // not enough edges

        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;

        for (auto &edge : connections) {
            unite(edge[0], edge[1]);
        }

        int components = 0;
        for (int i = 0; i < n; i++) {
            if (find(i) == i) components++;
        }

        return components - 1; 
    }
};
```

---

✅ **Time Complexity:**

- `find` and `unite` are almost O(1) (inverse Ackermann).
    
- So overall O(N + E).
    

✅ **Core Insight Recap:**

- If edges < n-1 → impossible.
    
- Otherwise → answer is `components - 1`.




