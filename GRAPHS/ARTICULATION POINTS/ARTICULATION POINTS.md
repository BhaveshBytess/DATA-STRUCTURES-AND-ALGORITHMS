
## 🔹 **Articulation Points (Cut Vertices)**

 **Definition:**  
In a connected undirected graph, an **articulation point** (cut vertex) is a vertex such that removing it (and its incident edges) increases the number of connected components.

---

## Question (LeetCode-style)

**Find Articulation Points in a Graph**

Given an undirected graph with `n` nodes (`0 … n-1`) and an edge list `connections`, return all the articulation points.

---

### Example:

```
Input:
n = 5
connections = [[0,1],[1,2],[2,0],[1,3],[1,4]]

Graph:
    0
   / \
  1---2
  |
  +--3
  |
  +--4
```

**Output:**

```
[1]
```

Because removing `1` disconnects `{3,4}` from `{0,2}`.

---

### DOUBTS : #ARTICULATION-POINTS


---


# SOLUTION : 

 Let’s write the **LeetCode-style solution for Articulation Points** (a.k.a. cut vertices).

We’ll use **Tarjan’s Algorithm** idea again (like in bridges) but with slightly different conditions:

- Track `disc[u]` (discovery time) and `low[u]` (earliest reachable time).
    
- For a **root node** (DFS starting point), it’s an articulation point if it has **two or more children**.
    
- For a **non-root node `u`**, it’s an articulation point if there exists a child `v` such that `low[v] >= disc[u]`.
    

---

###  C++ Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> articulationPoints(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> disc(n, -1), low(n, -1), parent(n, -1);
        vector<bool> isAP(n, false);
        int time = 0;

        function<void(int)> dfs = [&](int u) {
            disc[u] = low[u] = time++;
            int children = 0;

            for (int v : adj[u]) {
                if (disc[v] == -1) {
                    parent[v] = u;
                    children++;
                    dfs(v);

                    low[u] = min(low[u], low[v]);

                    // Case 1: Non-root node
                    if (parent[u] != -1 && low[v] >= disc[u]) {
                        isAP[u] = true;
                    }

                    // Case 2: Root node
                    if (parent[u] == -1 && children > 1) {
                        isAP[u] = true;
                    }
                }
                else if (v != parent[u]) {
                    // back edge
                    low[u] = min(low[u], disc[v]);
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) dfs(i);
        }

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (isAP[i]) result.push_back(i);
        }
        return result;
    }
};

int main() {
    int n = 5;
    vector<vector<int>> edges = {
        {0,1}, {0,2}, {2,1}, {0,3}, {3,4}
    };

    Solution sol;
    vector<int> ans = sol.articulationPoints(n, edges);

    cout << "Articulation Points: ";
    for (int x : ans) cout << x << " ";
    cout << endl;

    return 0;
}

```

---

### 🔑 Key Notes:

1. **Root rule:** Root is AP if it has ≥2 independent children in DFS tree.
    
2. **Non-root rule:** If `low[v] >= disc[u]`, `u` is AP (because child `v` cannot reach above `u`).
    
3. Works in **O(V+E)**.
    
4. Handles multiple components.
    

---

# IMPT : 

### 🔹 Reminder of Bridges intuition

We said:

- Edge `(u, v)` is a **bridge** if `v`’s subtree cannot “climb back” to `u` or any ancestor of `u`.
    
- Condition: `low[v] > disc[u]`.
    

This means: remove that edge, and the graph splits.

---

### 🔹 Articulation Point intuition

Now instead of removing an edge, we ask: _what if we remove a node?_

If removing node `u` disconnects the graph, then `u` is an articulation point (cut vertex).

---

#### Case 1: **Root node**

- Imagine DFS starts at `u` (root).
    
- If root has **two or more independent DFS children**, then if you remove the root, all those children’s subtrees get separated.
    
- Condition: `rootChildren >= 2 → root is articulation point`.
    

---

#### Case 2: **Non-root node**

- Suppose you are at node `u` with child `v`.
    
- You already know `low[v] = the earliest discovery time reachable from v’s subtree (by back-edges)`.
    
- Now ask: “Can `v`’s subtree reach `u` or any ancestor of `u` without using `u` itself?”
    

If `low[v] >= disc[u]`, it means:

- `v`’s subtree cannot go above `u`.
    
- If we remove `u`, then `v`’s whole subtree gets cut off → **disconnection happens**.
    

So:

```
if (low[v] >= disc[u] && u is not root) → u is articulation point
```

---

### 🔹 Putting it in words

- **Bridge** = one edge that, if removed, disconnects graph → check `low[v] > disc[u]`.
    
- **Articulation point** = one vertex that, if removed, disconnects graph → check `low[v] >= disc[u]` (non-root) or root has 2+ children.
    

---
