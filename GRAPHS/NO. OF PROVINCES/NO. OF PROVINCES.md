# NO_OF_PROVINCES 

----

## Problem: **Number of Provinces (LeetCode 547)**

You're given an `n x n` **adjacency matrix** `isConnected`, where:

- `isConnected[i][j] = 1` means city `i` is directly connected to city `j`.
    
- You need to return the **number of provinces**.
    

### What's a "province"?

It's just a **connected component** in the graph.

- So, if 3 cities are all connected directly or indirectly, they form **1 province**.
    
- Unconnected cities form their own province.
    

---

## Approach: DFS

We’ll:

1. Treat `isConnected` as an **adjacency matrix**.
    
2. Track which nodes (cities) we’ve visited.
    
3. For each unvisited node, launch a DFS — and count that as a **new province**.
    

---

Absolutely Bhavesh! Here's your **mini note** for **"Number of Provinces"** — written in your custom revision format, clean and concise for Obsidian, GitHub, or quick revision.

---

### **Mini Note**

🔹 **Problem:** Number of Provinces (Leetcode 547)
🔹 **Graph Type:** Undirected Graph (Adjacency Matrix)
🔹 **Technique:** DFS / BFS Traversal over matrix
🔹 **Core Template:** Treat matrix as implicit adjacency list, traverse unvisited nodes
🔹 **Pattern Tag:** #ConnectedComponents #AdjacencyMatrix

---

🔸 **Logic Summary:**

* Matrix represents direct connections: `isConnected[i][j] == 1` means city `i` and `j` are directly connected
* Convert the matrix into traversal logic: for each `i`, if `isConnected[i][j] == 1`, it's an edge
* Keep a `visited[]` array to avoid reprocessing
* For each unvisited node, do DFS/BFS → count each such traversal as a province

---

🔸 **Trick:**

* Even though it’s an adjacency matrix, the logic of finding connected components is the same as using an adjacency list.
* The matrix form may confuse at first — but treat each `1` as an edge and proceed normally.

---

🔸 **Why Union Find can be used here:**

* Union-Find is an alternate efficient solution, especially when edge updates are frequent
* Helps in quickly merging components and querying their roots

---

🔸 **Final Insight:**
This is **the matrix-version twin** of “Number of Connected Components.”
Great practice for learning how to traverse graphs when no adjacency list is given.


---
## C++ Code (DFS):

```cpp
class Solution {
public:
    void dfs(int node, vector<vector<int>>& isConnected, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor = 0; neighbor < isConnected.size(); neighbor++) {
            if (isConnected[node][neighbor] == 1 && !visited[neighbor]) {
                dfs(neighbor, isConnected, visited);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, isConnected, visited);
                provinces++;  // One full component is explored
            }
        }

        return provinces;
    }
};
```

---

## Dry Run Example

Input:

```cpp
isConnected = {
  {1,1,0},
  {1,1,0},
  {0,0,1}
}
```

- City 0 → connected to 1 → visited both in one DFS
    
- City 2 → unconnected → another DFS call
    

⏱️ Result: `2 provinces`

---

## Next Steps:

If you're good with this one, we can now do the **BFS version** too (same logic, just queue-based), or move to the next problem like:

- **Graph Valid Tree**
    
- **Number of Connected Components in Undirected Graph**
    
- **Flood Fill**
    
- or your pick!
    

Let me know!


---

## BFS VERSION 

Perfect, Bhavesh. Let’s now implement the **BFS version** of the **Number of Provinces** problem (LeetCode 547) using the standard approach — no custom constraints, just the base version.

---

### Problem Summary:

You are given an adjacency matrix `isConnected` of size `n x n`, where `isConnected[i][j] == 1` means city `i` and city `j` are directly connected. Return the **number of provinces** (i.e., connected components).

---

### BFS Logic:

- Initialize a `visited` array of size `n`, all false.
    
- Loop through each node:
    
    - If it hasn’t been visited, it means we found a new province.
        
    - Start BFS from that node and mark all reachable nodes as visited.
        
- Count how many times BFS is initiated — that’s the number of provinces.
    

---

### C++ Code Using BFS:

```cpp
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                provinces++;
                bfs(i, isConnected, visited);
            }
        }

        return provinces;
    }

    void bfs(int start, vector<vector<int>>& isConnected, vector<bool>& visited) {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor = 0; neighbor < isConnected.size(); ++neighbor) {
                if (isConnected[node][neighbor] == 1 && !visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
};
```

---

### Key Points:

- We’re using the adjacency **matrix** directly — no need to convert to an adjacency list.
    
- BFS ensures all cities in the same province are visited before moving to the next.
    
- **Time Complexity**: `O(n²)` — worst-case scan of the matrix.
    

---

Want to now convert this to an **adjacency list version using BFS** as well, or jump to another BFS/DFS graph problem?
