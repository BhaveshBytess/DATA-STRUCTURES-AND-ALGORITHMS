
### **261. Graph Valid Tree**

**Medium**  
**Companies**: Google, Facebook, Amazon  
**Topic**: Graphs (DFS/BFS, Union-Find)

You are given a graph with `n` nodes labeled from `0` to `n - 1` and a list of **undirected** edges. Each edge is a pair of nodes `[a, b]` indicating a bidirectional connection between node `a` and node `b`.

**Return `true` if the edges form a valid tree, and `false` otherwise.**

---

### **Example 1:**

**Input:**  
`n = 5`, `edges = [[0,1],[0,2],[0,3],[1,4]]`  
**Output:**  
`true`

**Explanation:**  
All nodes are connected and there are no cycles — this is a valid tree.

---

### **Example 2:**

**Input:**  
`n = 5`, `edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]`  
**Output:**  
`false`

**Explanation:**  
There is a cycle between 1-2-3 — this is **not** a valid tree.

---

### **Constraints:**

- `1 <= n <= 2000`
    
- `0 <= edges.length <= 5000`
    
- `0 <= a, b < n`
    
- No duplicate edges
    
- No self-loops (`a != b`)


---

# MINI-NOTE :

Here’s your **Mini Note** for **Graph Valid Tree** (a classic Amazon-style question):

---

**MINI NOTE**

🔹 **Problem**: Graph Valid Tree (Leetcode 261)  
🔹 **Graph Type**: Undirected Graph (Adjacency List)  
🔹 **Technique**: DFS/BFS for Cycle Detection + Component Check  
🔹 **Core Template**: DFS with parent tracking **OR** Union Find  
🔹 **Pattern Tag**: #TreeCheck #DFS #UnionFind #CycleAndConnected

---

🔸 **Logic Summary**:

- A graph is a **valid tree** if:
    
    1. It has **n−1 edges**
        
    2. It is **fully connected**
        
    3. It contains **no cycles**
        
- Method 1 (DFS):
    
    - Traverse from node 0, track visited nodes and parent.
        
    - If a back edge to a visited node ≠ parent → cycle.
        
    - After DFS, check if all nodes are visited.
        
- Method 2 (Union Find):
    
    - For every edge, try to unite the two nodes.
        
    - If they already belong to the same set → cycle.
        
    - At the end, all nodes should be part of one connected component.
        

---

🔸 **Trick**:

- Use `if(edges.size() != n-1)` **before** doing any traversal → quick elimination.
    
- DFS parent check is essential in undirected graphs to avoid false cycles.
    

---

🔸 **Why Other Approaches Won’t Work Alone**:

- Only checking for cycle isn't enough → might be disconnected.
    
- Only checking connectivity isn’t enough → might have cycles.
    

---

🔸 **Final Insight**:  
A tree is **acyclic and connected** with exactly **n−1 edges** — any graph meeting these three conditions is a valid tree.


---


### Final C++ Code for [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/)

```cpp
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
```

---

### Summary of What Makes a Valid Tree:

- **No Cycles** (handled by DFS and parent check)
    
- **Fully Connected** (all nodes visited)
    
- **Exactly n - 1 edges** (quick pre-check)

---

## DSU METHOD

Perfect 💯 Bhavesh! Let’s grind **Valid Tree (LeetCode 261)** using the **TST framework** (Think → Structure → Test).

---

## 🔹 Step 1: Problem Statement (Think)

You are given `n` nodes labeled from `0` to `n - 1` and a list of edges.  
Write a function to check if these edges form a **valid tree**.

👉 A valid tree must satisfy **2 conditions**:

1. **Connected** → All nodes must be reachable from any other node.
    
2. **Acyclic** → No cycle should exist.
    

📌 Input:

- `n` (number of nodes)
    
- `edges` (list of edge pairs)
    

📌 Output:

- `true` if it’s a valid tree
    
- `false` otherwise
    

---

## 🔹 Step 2: Structure (Approach via DSU)

### DSU Arsenal here:

We can use **Union-Find (DSU)** to detect cycles and ensure connectivity.

- If while adding an edge `(u, v)`, we see `find(u) == find(v)` → **cycle detected** ❌
    
- At the end, check if the number of edges = `n - 1`.
    
    - Why? Because a tree with `n` nodes always has exactly `n - 1` edges.
        

So conditions:

1. If number of edges != n - 1 → **Not a tree**
    
2. If cycle detected during DSU union → **Not a tree**
    
3. Otherwise → **Tree** ✅
    

---

## 🔹 Step 3: Code (Union by Rank / Path Compression)

```cpp
class DSU {
public:
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }
    
    bool unionSet(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return false; // cycle detected
        
        if (rank[pu] < rank[pv]) {
            parent[pu] = pv;
        } else if (rank[pv] < rank[pu]) {
            parent[pv] = pu;
        } else {
            parent[pu] = pv;
            rank[pv]++;
        }
        return true;
    }
};

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;
        
        DSU dsu(n);
        for (auto &edge : edges) {
            if (!dsu.unionSet(edge[0], edge[1])) 
                return false;
        }
        return true;
    }
};
```

---

## 🔹 Step 4: Test (Dry Run)

### Example 1:

```
n = 5
edges = [[0,1],[0,2],[0,3],[1,4]]
```

- Number of edges = 4 = n-1 ✅
    
- Add (0,1) → ok
    
- Add (0,2) → ok
    
- Add (0,3) → ok
    
- Add (1,4) → ok
    
- No cycle, edges = n-1 → **true (valid tree)** ✅
    

### Example 2:

```
n = 5
edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
```

- Number of edges = 5 ≠ 4 ❌ → immediately false.
    

---

So, DSU makes this problem super elegant — **O(E α(N)) ≈ O(E)**

    
