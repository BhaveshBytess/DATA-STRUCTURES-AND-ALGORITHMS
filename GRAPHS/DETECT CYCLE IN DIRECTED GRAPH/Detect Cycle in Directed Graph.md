Great 🔥 Let's now move to the **next graph stage**: #CYCLE_DIRECTED_GRAPH 

---

### 🔗 **LeetCode-Style Question: Detect Cycle in a Directed Graph**

> 🔢 **Question Name**: Detect Cycle in a Directed Graph  
> 🟦 **Difficulty**: Medium  
> 📘 **Concepts**: DFS, Graph, Cycle Detection, Recursion Stack

---

### ❓ Problem Statement

You are given a **directed graph** with `n` nodes labeled from `0` to `n - 1` and a list of directed edges `edges`, where `edges[i] = [u, v]` represents a **directed edge from `u` to `v`**.

Return `true` **if the graph contains a cycle**, and `false` otherwise.

---

### 📥 Input

- `n`: Integer, number of nodes. (1 ≤ n ≤ 10⁵)
    
- `edges`: List of directed edges. (0 ≤ edges.length ≤ 10⁵)
    

---

### 📤 Output

- Return `true` if a cycle exists, otherwise return `false`.
    

---

### 🧠 Example

```cpp
Input:
n = 4
edges = [[0,1],[1,2],[2,3],[3,1]]

Output:
true
Explanation: There is a cycle: 1 → 2 → 3 → 1
```

```cpp
Input:
n = 4
edges = [[0,1],[1,2],[2,3]]

Output:
false
Explanation: No cycles.
```

---

Let me know when you want to start grinding this question. Stick to our rule: **no solution**, only light nudges when asked. 🧠⚔️

---

# MINI-NOTE : 

🔹 **Problem:** Detect Cycle in Directed Graph  
🔹 **Graph Type:** Directed Graph (Adjacency List)  
🔹 **Technique:** DFS with Recursion Stack  
🔹 **Core Template:** DFS(node) with `visited[]` and `recStack[]`  
🔹 **Pattern Tag:** #CycleDetection #DirectedGraph #DFSRecStack

---

🔸 **Logic Summary:**

- Use two arrays:
    
    - `visited[]` → marks if node has been visited at all.
        
    - `recStack[]` → marks if node is part of current DFS path (recursion stack).
        
- For each unvisited node, run DFS:
    
    - Mark as visited and add to recStack.
        
    - For each neighbor:
        
        - If unvisited → DFS call
            
        - If visited **and still in recStack** → cycle exists
            
    - Remove node from recStack when DFS ends
        

---

🔸 **Trick:**

- The presence of a cycle is detected by encountering a node that is **already in the current recursion path**.
    
- This is like detecting a **back edge** in the DFS tree.
    

---

🔸 **Why Undirected Logic Fails:**

- Parent-check logic from undirected graphs fails in directed graphs because **edges are one-way** — the notion of a parent doesn’t help here.
    
- Need to track the full DFS path instead.
    

---

🔸 **Final Insight:**  
Cycle detection in directed graphs is all about detecting **back edges** — a revisit to an ancestor node still in the recursion path.  
This is a **core building block** for:

- Course Schedule I (Detect Cycle)
    
- Course Schedule II (Topo Sort)
    
- Deadlock detection
    
- Compiler dependency resolution
    

----

Yes, Bhavesh, you're **very close** to cracking the core difference between cycle detection in **undirected vs directed graphs**. Let’s lock in that understanding:

---

### ✅ You're Right About:

- **No need for `parent`** in **directed graphs**:  
    In directed graphs, cycles are not about "going back to the parent" but rather **revisiting a node that's already in the current path of recursion**.
    

---

### 🚨 But One Crucial Insight:

You **can’t** rely solely on a single `visited[]` array.

Instead, you need **two** things:

1. `visited[]` — To mark if a node was _ever_ visited.
    
2. `pathVisited[]` — To mark if a node is _currently in the recursion stack_.
    

Because a cycle in a **directed graph** means:

> A node we are visiting again is **already part of the current DFS path** (i.e., present in recursion stack).

---

### ⛓️ So Your Modified Flow Should Be:

```cpp
bool dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& pathVisited) {
    visited[node] = true;
    pathVisited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, adj, visited, pathVisited)) return true;
        }
        else if (pathVisited[neighbor]) {
            return true; // Found cycle
        }
    }

    pathVisited[node] = false; // Backtrack
    return false;
}
```

Want to go ahead and write this yourself with just this nudging? Or do you want me to compile the whole clean code when you're ready?

---


Sure Bhavesh! Here's the **clean, LeetCode-style C++ code** to detect a **cycle in a directed graph** using DFS, implementing everything we just discussed:

---

### ✅ **LeetCode Style: Detect Cycle in a Directed Graph**

```cpp
class Solution {
public:
    bool dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& pathVisited) {
        visited[node] = true;
        pathVisited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, adj, visited, pathVisited)) 
                    return true;
            }
            else if (pathVisited[neighbor]) {
                return true; // Cycle found
            }
        }

        pathVisited[node] = false; // Backtrack
        return false;
    }

    bool hasCycle(int V, vector<vector<int>>& edges) {
        vector<vector<int>> adj(V);
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v); // Directed edge
        }

        vector<bool> visited(V, false);
        vector<bool> pathVisited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, adj, visited, pathVisited)) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

---

### ✅ Example Usage (Main or LeetCode-style wrapper)

If this were a LeetCode problem like:

> **Given number of nodes `n` and a list of directed edges `edges`, return `true` if the graph has a cycle, otherwise `false`.**

Then your function would be:

```cpp
bool hasCycle(int n, vector<vector<int>>& edges);
```

---

### 🚀 Time and Space Complexity

- **Time:** `O(V + E)` — Standard DFS traversal.
    
- **Space:** `O(V)` for visited and recursion stack arrays.
    

---

Let me know when you're ready for the next graph grind or if you want to implement **BFS-based cycle detection for directed graphs (Kahn’s algorithm)** next.


---


Absolutely Bhavesh, let’s dry run the **cycle detection in directed graph using DFS** — step by step — on a simple example.

---

### 🔍 Test Case

Let’s take a directed graph with a cycle:

```
Input:
V = 4
edges = [
  [0, 1],
  [1, 2],
  [2, 3],
  [3, 1]  // <-- back edge forming a cycle
]
```

This forms a cycle: `1 → 2 → 3 → 1`

---

### 🔁 Step-by-Step Dry Run

We’ll track:

- `visited[]`: nodes we've ever visited
    
- `pathVisited[]`: nodes in **current DFS call stack**
    
- `adj[]`: adjacency list
    

---

#### ✅ **Adjacency List Created**

```cpp
adj[0] = {1}
adj[1] = {2}
adj[2] = {3}
adj[3] = {1}
```

---

#### 🔄 Loop through all nodes

- `visited = [F, F, F, F]`
    
- `pathVisited = [F, F, F, F]`
    

##### ➤ `i = 0` → not visited → call `dfs(0)`

1. Mark `visited[0] = true`, `pathVisited[0] = true`
    
2. Go to neighbor `1` → not visited → call `dfs(1)`
    

---

##### ➤ `dfs(1)`

1. Mark `visited[1] = true`, `pathVisited[1] = true`
    
2. Go to neighbor `2` → not visited → call `dfs(2)`
    

---

##### ➤ `dfs(2)`

1. Mark `visited[2] = true`, `pathVisited[2] = true`
    
2. Go to neighbor `3` → not visited → call `dfs(3)`
    

---

##### ➤ `dfs(3)`

1. Mark `visited[3] = true`, `pathVisited[3] = true`
    
2. Go to neighbor `1` → visited **AND** `pathVisited[1] = true` ⇒ **CYCLE FOUND**
    
    - return `true`
        

This `true` bubbles up to all previous calls, and ultimately `hasCycle()` returns `true`.

---

### 🧠 What Made It Work?

- The `pathVisited[]` array tracks the _current recursion path_. If you revisit a node that’s _still in the current call stack_, you’ve found a **cycle**.
    
- If it were only in `visited[]` but not in `pathVisited[]`, it just means we finished processing that branch — not a cycle.
    

---

Would you like a dry run of **non-cyclic case** too for clarity?