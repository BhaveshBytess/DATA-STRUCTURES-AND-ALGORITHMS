Perfect Bhavesh. You're now entering **Stage 2 of Graph Mastery** — tackling **Cycle Detection in Undirected Graphs**, a **core DFS pattern** used in:

- Tree validation
    
- Disjoint Set Union (Union Find)
    
- Graph-based interview challenges
    

Let’s jump straight into it — your **Leetcode-style grinding setup**, no fluff, only what’s essential for your process:

---

### 🔥 Leetcode-Style Problem:

**Title**: Detect Cycle in an Undirected Graph  
**Difficulty**: Medium  
**Topic**: Graph, DFS, Cycle Detection

#### 🧾 Problem Statement:

You are given an **undirected graph** with `n` nodes labeled from `0` to `n - 1`, and a list of `edges` where each edge is a pair `[u, v]` indicating an undirected connection between node `u` and node `v`.

Write a function to **detect if the graph contains a cycle**.  
Return `true` if there is a cycle, `false` otherwise.

---

### 🧠 Your Function Signature (C++):

```cpp
bool hasCycle(int n, vector<vector<int>>& edges);
```

---

### 💡 Constraints:

- `1 <= n <= 10^5`
    
- `0 <= edges.length <= 10^5`
    
- `0 <= u, v < n`
    
- Graph may be **disconnected**
    
- **Undirected**, no self-loops
    


---

# MINI-NOTE : 


Absolutely Bhavesh! Here's your **mini note** for **Detect Cycle in an Undirected Graph** — structured exactly in your format for clarity and long-term revision.

---

### ✅ **Mini Note**

🔹 **Problem:** Detect Cycle in Undirected Graph  
🔹 **Graph Type:** Undirected Graph (Adjacency List)  
🔹 **Technique:** DFS with parent tracking  
🔹 **Core Template:** DFS(node, parent)  
🔹 **Pattern Tag:** #CycleDetection #UndirectedGraph #DFSwithParent

---

🔸 **Logic Summary:**

- For each unvisited node, run DFS.
    
- During DFS, for each neighbor:
    
    - If the neighbor is unvisited → recurse with `parent = current node`
        
    - If the neighbor is visited **and** not the parent → **cycle exists**
        
- Continue checking all components (the graph might be disconnected)
    

---

🔸 **Trick:**

- The key idea is that in **undirected graphs**, every edge is two-way.
    
- So encountering a visited node is only a cycle **if it's not the parent** of the current node.
    

---

🔸 **Why BFS Won’t Work Directly:**

- BFS can be used, but DFS with parent check is cleaner and more intuitive for detecting cycles in undirected graphs.
    
- BFS approach needs extra logic with `(node, parent)` tracking in the queue.
    

---

🔸 **Final Insight:**  
Cycle detection in undirected graphs hinges on recognizing **back-edges to non-parent nodes**.  
A must-know building block for:

- Graph Valid Tree
    
- Disjoint Set Union (DSU)-based solutions
    
- Spanning Trees
    

---

Let me know if you want the **C++ DFS code** version here or if you’re ready to log the next one, Bhavesh 🚀




---

### 🔗 LeetCode-Style: Detect Cycle in an Undirected Graph

```cpp
class Solution {
public:
    bool dfs(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, node, adj, visited)) {
                    return true; // cycle found in recursion
                }
            } else if (neighbor != parent) {
                return true; // back edge found → cycle
            }
        }

        return false;
    }

    bool hasCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        vector<bool> visited(n, false);

        // Create adjacency list
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Check each component
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(i, -1, adj, visited)) {
                    return true; // cycle detected
                }
            }
        }

        return false; // no cycle in any component
    }
};
```

---

### 📘 Example Usage:

In LeetCode, you’d be given:

```cpp
int n = 5;
vector<vector<int>> edges = {{0,1},{1,2},{2,3},{1,3}};
Solution sol;
bool hasCycle = sol.hasCycle(n, edges); // Output: true
```

---

Let me know when you’re ready to move to **cycle detection in a _directed_ graph**, which is different logic (uses visited + recursion stack).


---

# KAHN'S ALGO (BFS)

Perfect. Let's now solve **Cycle Detection in a Directed Graph using BFS**, which is **Kahn’s Algorithm** — a classic topological sort-based method.

---

### ✅ **Problem (LeetCode Style)**

> Given a **directed graph** with `n` nodes (0 to n-1) and a list of edges, return **true if the graph does NOT contain a cycle**, otherwise return **false**.
> 
> This is essentially checking if the graph is a **Directed Acyclic Graph (DAG)** using **Kahn’s Algorithm**.

---

### ✅ **Approach (Kahn’s Algorithm - Topological Sort)**

1. Build an **adjacency list** and compute the **in-degree** of every node.
    
2. Push all nodes with **in-degree 0** into a queue.
    
3. Do BFS:
    
    - Pop a node from the queue and add to `count` (topo sort result size).
        
    - Decrease in-degree of its neighbors.
        
    - If any neighbor's in-degree becomes 0, push it into the queue.
        
4. After BFS:
    
    - If `count == n`, then graph has **no cycle**.
        
    - Else, graph has a **cycle**.
        

---

### ✅ **C++ Code (Clean & Simple)**

```cpp
class Solution {
public:
    bool canFinish(int n, vector<vector<int>>& edges) {
        vector<int> adj[n];
        vector<int> indegree(n, 0);

        // Build adjacency list and indegree array
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            indegree[v]++;
        }

        // Queue for nodes with indegree 0
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0)
                q.push(i);
        }

        int count = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++;

            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }

        // If we processed all nodes, no cycle
        return count == n;
    }
};
```

---

### 💡 Example

```txt
Input:
n = 4
edges = [[0,1],[1,2],[2,3]]

→ Output: true (No cycle, we can finish)

Input:
n = 3
edges = [[0,1],[1,2],[2,0]]

→ Output: false (Cycle exists)
```

---

Want to dry-run this with an example or jump to a follow-up question (like Course Schedule II or Topo Sort list)?