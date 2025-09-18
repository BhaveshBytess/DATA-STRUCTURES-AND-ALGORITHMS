
## 🔹 Problem — Critical Connections in a Network 

You are given a network of `n` servers, labeled from `0` to `n - 1`. They are connected by `connections`, where `connections[i] = [ai, bi]` represents a bidirectional connection between servers `ai` and `bi`.

A **critical connection** is a connection that, if removed, will make some servers unable to reach others.

Return all critical connections in the network in **any order**.

---

### Example 1:

```
Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: Removing edge [1,3] disconnects server 3.
```

### Example 2:

```
Input: n = 2, connections = [[0,1]]
Output: [[0,1]]
```

---

### Constraints:

- `2 <= n <= 10^5`
    
- `n - 1 <= connections.length <= 10^5`
    
- `0 <= ai, bi < n`
    
- `ai != bi`
    
- There are no repeated connections.
    

### HINT :  

## 🔹 What the problem is really asking

We need to find **bridges** in the graph.  
👉 A _bridge_ (aka critical connection) is an edge that, if removed, increases the number of connected components.

So this is not about finding SCCs like in Tarjan’s SCC algorithm.  
It’s about finding **edges that are the only path between two regions of the graph**.

---

## 🔹 Where Tarjan’s "low-link" comes in

Remember how in Tarjan’s SCC we tracked **the lowest discovery time reachable** from each node (`low[u]`)?  
We’re going to reuse the same trick here — but instead of grouping nodes into SCCs, we’ll use it to **detect whether an edge is a bridge**.

---

## 🔹 The Key Idea (Bridge Rule)

Suppose we are exploring edge `(u, v)` in DFS.

- Let `disc[u]` = discovery time of `u`.
    
- Let `low[v]` = the earliest discovery time `v` or its descendants can reach back (via tree edges + back edges).
    

Now:  
👉 If `low[v] > disc[u]`,  
then the edge `(u, v)` is a **bridge**, because `v` and everything below it cannot reach back to `u` or its ancestors.  
So removing `(u, v)` disconnects the graph.

---

## 🔹 Algorithm Steps

1. Run DFS from node `0` (or all unvisited nodes, since the graph may not be fully connected).
    
2. Keep:
    
    - `disc[u]`: discovery time when first visited.
        
    - `low[u]`: lowest discovery time reachable from `u`.
        
    - `time`: global clock that increments at each DFS visit.
        
3. For each neighbor `v` of `u`:
    
    - If `v` is not visited → recurse into `v`. After DFS, update `low[u] = min(low[u], low[v])`.
        
    - If `low[v] > disc[u]`, mark `(u, v)` as a bridge.
        
    - If `v` is already visited (and not the parent), update `low[u] = min(low[u], disc[v])`.
        

---

## 🔹 Why it works

- The **low-link checkpoint** lets you detect if a child `v` can climb back to `u` (or above).
    
- If it can’t (`low[v] > disc[u]`), then the edge `(u,v)` is a **single point of failure** — a critical connection.
    

---

## 🔹 Example Dry Run

Graph: `[[0,1],[1,2],[2,0],[1,3]]`

DFS order:

- Visit `0 (disc=0, low=0)`
    
    - Go to `1 (disc=1, low=1)`
        
        - Go to `2 (disc=2, low=2)`
            
            - Back edge from `2 → 0` → update `low[2] = min(2,0)=0`
                
        - After exploring `2`, `low[1] = min(1,0)=0`
            
        - Go to `3 (disc=3, low=3)` → no back edge → returns.
            
            - Check `low[3] (3) > disc[1] (1)` → edge `(1,3)` is a bridge.
                

So the answer is `[[1,3]]`. ✅




---



# MINI-NOTE : 










----


# SOLUTION : 

DOUBTS : #CRITICAL_CONNECTIONS


### Code (C++ – Tarjan’s Bridge Finder)

```cpp
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for (auto &edge : connections) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<int> disc(n, -1), low(n, -1);
        vector<vector<int>> bridges;
        int time = 0;
        
        function<void(int,int)> dfs = [&](int u, int parent) {
            disc[u] = low[u] = time++;
            
            for (int v : adj[u]) {
                if (v == parent) continue;  // don’t go back to parent
                
                if (disc[v] == -1) { // tree edge
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    
                    // bridge condition
                    if (low[v] > disc[u]) {
                        bridges.push_back({u, v});
                    }
                } else { // back edge
                    low[u] = min(low[u], disc[v]);
                }
            }
        };
        
        dfs(0, -1);
        return bridges;
    }
};
```

---

### ⚙️ Key points to lock in:

1. `disc[u]` → discovery time of `u`.
    
2. `low[u]` → lowest reachable discovery time from `u` (via DFS tree edges + back edges).
    
3. **Bridge condition:**
    
    ```
    if (low[v] > disc[u]) → edge (u,v) is a bridge
    ```
    
    Meaning: child `v` couldn’t reach `u` or any ancestor → removing this edge disconnects.
    

---

This code runs in **O(N + M)** time and is optimal 🚀.


---

# IMPT : 

## 1. First, recall what a **bridge** means

A bridge = an edge that, if removed, increases the number of connected components.  
👉 In other words: remove that edge → the graph disconnects.

So we want a test that detects whether an edge `(u,v)` is **the only way** to go from `v` (and all its descendants in DFS tree) back to `u` or earlier ancestors.

---

## 2. DFS intuition

- When we DFS from `u` to `v`, we make `(u,v)` a **tree edge**.
    
- Now, the subtree rooted at `v` will explore further.
    
- Question: _can that subtree somehow “climb back up” to `u` or an ancestor of `u` through some other route (a back edge)?_
    

---

## 3. The role of `low[v]`

- `low[v]` = the **earliest discovery time** reachable from `v` (through descendants + back edges).
    
- If `low[v] ≤ disc[u]`, then:
    
    - Subtree at `v` found a way back to `u` or earlier ancestor.
        
    - Removing `(u,v)` won’t disconnect — because `v`’s subtree has another path upward.
        
- If `low[v] > disc[u]`, then:
    
    - Subtree at `v` **cannot reach back** to `u` or any ancestor of `u`.
        
    - The only connection of that entire subtree to the graph above is the edge `(u,v)`.
        
    - So if we cut `(u,v)`, subtree becomes isolated → **bridge**. ✅
        

---

## 4. Why discovery time vs low?

Your earlier summary was close:

- For parent relation (tree edge) → after DFS, we compare **low[v] with disc[u]**.
    
- For back edges (to an ancestor, not parent) → we update `low[u] = min(low[u], disc[v])`.
    

---

## 5. How people “discovered” this

This comes from **graph theory & DFS tree analysis**.

- Mathematicians realized DFS tree edges + back edges fully capture cycles.
    
- The condition `low[v] > disc[u]` is just a formal way of saying _“subtree v cannot form a cycle that touches u or above”_.
    
- If no cycle exists → edge is critical → bridge.
    

So it’s not a random “thesis” but a direct logical consequence of cycle detection using DFS tree.

---

✅ Final summary:

> A tree edge `(u,v)` is a **bridge** if the subtree rooted at `v` cannot reach back to `u` or any ancestor of `u`. Formally, `low[v] > disc[u]`. This comes from the definition of bridges and the way DFS encodes connectivity via back edges.

---

