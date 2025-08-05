
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

📘 **MINI NOTE**

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


### ✅ Final C++ Code for [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/)

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

### 💡 Summary of What Makes a Valid Tree:

- ✅ **No Cycles** (handled by DFS and parent check)
    
- ✅ **Fully Connected** (all nodes visited)
    
- ✅ **Exactly n - 1 edges** (quick pre-check)
    
