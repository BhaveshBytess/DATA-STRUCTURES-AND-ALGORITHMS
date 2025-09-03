
## **785. Is Graph Bipartite?** #IS-BIPARTITE 

You are given an **undirected graph** represented by an adjacency list, where `graph[i]` is a list of nodes that node `i` is connected to.

Return **true** _if the graph is bipartite_. Otherwise, return **false**.

---

### **Example 1**

```
Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
Output: false
Explanation: The graph cannot be colored with two colors without conflicts.
```

### **Example 2**

```
Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: The graph is bipartite because we can split the nodes into two sets: {0,2} and {1,3}.
```

---

### **Constraints**

- `1 <= graph.length <= 100`
    
- `0 <= graph[i].length < graph.length`
    
- `0 <= graph[i][j] < graph.length`
    
- `graph[i][j] != i` (no self-loops)
    
- `graph[i]` does not contain duplicate values
    

---

### 🔹 **Definition**

A **bipartite graph** is a graph whose **nodes can be split into two disjoint sets (say, U and V)** such that:  
👉 Every edge connects one node from set **U** to one node from set **V**.  
👉 No edge exists between two nodes _within the same set_.

---

### 🔹 **Equivalent Way to Think**

It’s the same as saying:

- You can **color the graph with 2 colors** (say, Red and Blue)
    
- Such that **no two adjacent nodes have the same color**.
    

If such a coloring is possible → graph is bipartite.  
If not → it isn’t bipartite.

---

### 🔹 **Examples**

1. **Bipartite**
    

```
0 -- 1
|    |
3 -- 2
```

- This is a square (even cycle).
    
- You can color {0,2} as Red and {1,3} as Blue. ✅
    

2. **Not Bipartite**
    

```
0
| \
1--2
```

- This is a triangle (odd cycle).
    
- Try coloring → you’ll get a conflict (an adjacent edge where both nodes share same color). ❌
    

---

### 🔹 **Key Insight**

- **Even cycles** are bipartite.
    
- **Odd cycles** are not bipartite.
    

---

# MINI-NOTE : 

### 🔹 Problem

Given an undirected graph `graph` represented as an adjacency list, determine if the graph is **bipartite**.  
A graph is bipartite if we can split its nodes into **two sets** such that **no two adjacent nodes share the same set**.

---

### 🔹 Graph Type

- Undirected
    
- May be disconnected (multiple components)
    
- Represented as adjacency list
    

---

### 🔹 Technique

- **Graph Coloring** with **BFS or DFS**
    
- Use two colors (0, 1)
    
- Assign colors alternately while traversing
    
- If conflict arises → not bipartite
    

---

### 🔹 Core Template

```cpp
// BFS template
vector<int> color(n, -1);
for (int start = 0; start < n; start++) {
    if (color[start] == -1) {
        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int nei : graph[node]) {
                if (color[nei] == -1) {
                    color[nei] = 1 - color[node];
                    q.push(nei);
                } else if (color[nei] == color[node]) {
                    return false;
                }
            }
        }
    }
}
return true;
```

DFS version: same idea, recursion handles queue.

---

### 🔹 Pattern Tag

- **Graph Traversal** (BFS / DFS)
    
- **Graph Coloring**
    
- **Connected Components**
    
- **Cycle Detection (odd length cycles → not bipartite)**
    

---

### 🔸 Logic Summary

1. Initialize all nodes as uncolored (`-1`).
    
2. For each unvisited node (handle disconnected graph), start BFS/DFS.
    
3. Color start node `0`.
    
4. Traverse neighbors:
    
    - If uncolored → assign opposite color.
        
    - If already colored and matches current → conflict → not bipartite.
        
5. If traversal finishes without conflict → bipartite.
    

---

### 🔸 Trick

- **Odd cycle detection**: Graph is bipartite iff it has **no odd-length cycle**. Coloring implicitly checks this.
    
- For **LeetCode 785 constraints (`n ≤ 100`)**, recursion is safe; no stack overflow.
    
- No need to worry about self-loops or duplicates (guaranteed in constraints).
    

---

### 🔸 Why other approach won’t work

- **Union-Find (Disjoint Set)** could be adapted, but extra complexity without benefit here.
    
- **Adjacency Matrix** traversal possible, but wasteful for `n ≤ 100` adjacency list input.
    
- **Brute check of all partitions** = `O(2^n)` → impossible, even though `n` is small.
    

---

### 🔸 Final Insight

- Bipartiteness check boils down to **2-coloring using BFS/DFS**.
    
- Constraints tell us:
    
    - `n ≤ 100` → recursion safe, BFS/DFS both fine.
        
    - `O(V+E)` solution is more than enough.
        
    - Memory no issue (vector of size `n`).
        
- Core mental shortcut: _“If I can color graph with 2 colors without conflict → bipartite. Otherwise → not bipartite.”_
    

---

# SOLUTION (BFS)


```cpp
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
```

---

✅ **Key points in this code:**

1. We use `color[]` array to mark nodes (`-1` = not visited, `0/1` = two colors).
    
2. BFS traversal ensures neighbors always get opposite colors.
    
3. If any neighbor already has the same color, we return **false** immediately.
    
4. Works even if the graph is **disconnected** (we loop over all nodes).
    

---

# SOLUTION (DFS)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool dfs(int node, int color, vector<int>& colors, vector<vector<int>>& graph) {
        colors[node] = color;
        
        for (int nei : graph[node]) {
            if (colors[nei] == -1) {
                // assign opposite color
                if (!dfs(nei, 1 - color, colors, graph)) return false;
            } 
            else if (colors[nei] == color) {
                // conflict found
                return false;
            }
        }
        return true;
    }

    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> colors(n, -1); // -1 = uncolored

        for (int i = 0; i < n; i++) {
            if (colors[i] == -1) {
                if (!dfs(i, 0, colors, graph)) return false;
            }
        }
        return true;
    }
};
```

👉 Same idea as BFS, but recursion handles the "queueing".

- Each node is colored `0` or `1`.
    
- Neighbors get opposite color.
    
- If we ever find a neighbor with the same color, return `false`.
    
