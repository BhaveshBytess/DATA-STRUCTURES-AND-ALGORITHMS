
### 📌 Problem: Network Delay Time

You are given a network of `n` nodes, labeled from `1` to `n`.  
You are also given `times`, a list of travel times as directed edges `times[i] = (u, v, w)`,  
where `u` is the source node, `v` is the target node, and `w` is the time it takes for a signal to travel from `u` to `v`.

We send a signal from a given node `k`.

Return the **minimum time** it takes for **all the `n` nodes** to receive the signal.  
If it is impossible for all the nodes to receive the signal, return **-1**.

---

### 🔹 Example 1:

**Input:**

```
times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
```

**Output:**

```
2
```

---

### 🔹 Example 2:

**Input:**

```
times = [[1,2,1]], n = 2, k = 1
```

**Output:**

```
1
```

---

### 🔹 Example 3:

**Input:**

```
times = [[1,2,1]], n = 2, k = 2
```

**Output:**

```
-1
```

---

### 🔹 Constraints:

- `1 <= k <= n <= 100`
    
- `1 <= times.length <= 6000`
    
- `times[i].length == 3`
    
- `1 <= u, v <= n`
    
- `u != v`
    
- `0 <= w <= 100`
    

---

# MINI-NOTE :

🔹 **Problem**  
Find the time it takes for a signal sent from a starting node `k` to reach all nodes in a directed weighted graph. If any node is unreachable, return `-1`.

🔹 **Graph Type**  
Directed, weighted graph (positive weights).

🔹 **Technique**  
Shortest path → Dijkstra’s Algorithm (or Bellman–Ford if negative edges allowed, but here weights are positive).

🔹 **Core Template**

1. Build adjacency list from edges.
    
2. Run Dijkstra from source `k`.
    
3. Get shortest distance to all nodes.
    
4. Answer = `max(dist[])` if all reachable, else `-1`.
    

🔹 **Pattern Tag**

- Single-source shortest path
    
- “Broadcast / Spread time” problems
    
- Graph traversal with weights
    

---

🔸 **Logic Summary**

- Each `dist[i]` tells how long it takes for the signal to reach node `i`.
    
- The last node to get the signal determines total delay.
    
- Hence `max(dist[])` across all reachable nodes is the result.
    

🔸 **Trick**

- Don’t confuse with min:
    
    - `min(dist[])` → earliest node to receive signal
        
    - `max(dist[])` → last node to receive signal (correct answer).
        

🔸 **Why BFS/DFS won’t work**

- BFS works only for **unit weights** (unweighted graph).
    
- Here edges have weights, so we must use Dijkstra (efficient for positive weights).
    

🔸 **Final Insight**

- Problem is basically: **“Find the time when the farthest node (in terms of shortest path) receives the signal.”**
    
- That’s why we take `max` at the end, not `min`.
    

---

# SOLUTION : 


##  Approach (Dijkstra’s Algorithm)

- Build adjacency list from `times`.
    
- Use **priority queue (min-heap)** to always expand the shortest path node first.
    
- Keep a `dist[]` array initialized with `∞`, except `dist[k] = 0`.
    
- For each popped node, relax its neighbors.
    
- At the end:
    
    - If some `dist[i] == ∞` → return `-1`.
        
    - Else return `max(dist[1..n])`.
        

⏱️ Time Complexity → `O(E log V)`  
📦 Space Complexity → `O(V + E)`

---

## 3. Code (C++ Implementation)

```cpp
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
```

---

## 4. Dry Run (Example 1)

**Input:**

```
times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
```

**Step 1: Graph**

- 2 → 1 (1)
    
- 2 → 3 (1)
    
- 3 → 4 (1)
    

**Step 2: dist init**

```
dist = [∞, ∞, 0, ∞, ∞]   (1-based index)
```

**Step 3: PQ starts with (0,2)**

- Pop (0,2) → Relax:
    
    - dist[1] = 1, push (1,1)
        
    - dist[3] = 1, push (1,3)
        
- PQ = [(1,1), (1,3)]
    
- Pop (1,1) → no neighbors
    
- Pop (1,3) → Relax:
    
    - dist[4] = 2, push (2,4)
        
- PQ = [(2,4)]
    
- Pop (2,4) → no neighbors
    

**Final dist = [∞, 1, 0, 1, 2]**

**Answer = max(1,0,1,2) = 2 ✅**

---

