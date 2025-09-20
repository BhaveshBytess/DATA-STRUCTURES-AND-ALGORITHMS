
### 1584. Min Cost to Connect All Points

You are given an array `points` representing integer coordinates of some points on a 2D-plane, where `points[i] = [xi, yi]`.

The cost of connecting two points `[xi, yi]` and `[xj, yj]` is the **Manhattan distance** between them:

∣xi−xj∣+∣yi−yj∣

Return the **minimum cost** to make all points connected.  
All points are connected if there is exactly one simple path between any two points.

---

#### Example 1:

**Input:**  
`points = [[0,0],[2,2],[3,10],[5,2],[7,0]]`

**Output:**  
`20`

---

#### Example 2:

**Input:**  
`points = [[3,12],[-2,5],[-4,1]]`

**Output:**  
`18`

---

#### Constraints:

- `1 <= points.length <= 1000`
    
- `-10^6 <= xi, yi <= 10^6`
    
- All points are unique
    



This is basically a **Minimum Spanning Tree (MST)** problem — you want to connect all points with minimum total cost using **Kruskal’s or Prim’s algorithm**.

---

Perfect 👌 Let’s go step by step and really **understand MST (Minimum Spanning Tree)** before we attack this problem.

---

## 🔹 Step 1: What is MST?

- We are given a graph with **nodes (points)** and **edges (connections with weights/costs)**.
    
- A **spanning tree** is a subset of edges that:
    
    1. Connects **all nodes**.
        
    2. Contains **no cycles** (it’s a tree).
        
- A **minimum spanning tree (MST)** is the spanning tree where the sum of edge weights is **minimum possible**.
    

👉 Example:

```
   (0)----1----(1)
    |          /
    4       2
    |      /
   (2)----
```

- Possible spanning trees:
    
    - Use edges {1,2} → cost = 3
        
    - Use edges {1,4} → cost = 5
        
    - Use edges {2,4} → cost = 6
        

✅ MST = edges {1,2}, cost = 3

---

## 🔹 Step 2: Two Main MST Algorithms

### 1. **Kruskal’s Algorithm** (Greedy, Edge-based)

- Sort all edges by weight (smallest first).
    
- Start picking edges in that order:
    
    - Add the edge **if it doesn’t form a cycle** (use Union-Find / DSU to check).
        
- Stop when we have `n-1` edges (tree formed).
    

👉 Characteristics:

- Works best when **graph edges are few (sparse graph)**.
    
- Needs **sorting edges** → Time = `O(E log E)`.
    

---

### 2. **Prim’s Algorithm** (Greedy, Node-based)

- Start from any node.
    
- Repeatedly add the **cheapest edge** from the current tree to a new node not in the tree.
    
- Continue until all nodes are included.
    

👉 Characteristics:

- Works well with **dense graphs** (like this problem, where `E ≈ n²`).
    
- Time = `O(E log V)` with priority queue.
    

---

## 🔹 Step 3: Which one for our problem?

- Here, each point is connected to every other point (complete graph).
    
- Number of edges = `n * (n-1) / 2` (≈ 500k when n=1000).
    
- That’s **too many edges** → Kruskal (sorting half a million edges) is slower.
    
- **Prim’s Algorithm** is better here.
    

✅ So the _optimal solution_ uses **Prim’s Algorithm** with a priority queue (min-heap).

---

# SOLUTION : 

## 🔹 Optimized Prim’s Algorithm in C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        
        // Min-heap {cost, node}
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        
        vector<bool> inMST(n, false); // whether node is included in MST
        int edgesUsed = 0;
        int result = 0;

        pq.push({0, 0}); // start with node 0, cost 0

        while (edgesUsed < n) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (inMST[u]) continue; // already added
            inMST[u] = true;
            result += cost;
            edgesUsed++;

            // Update all edges from u to others
            for (int v = 0; v < n; v++) {
                if (!inMST[v]) {
                    int newCost = abs(points[u][0] - points[v][0]) + 
                                  abs(points[u][1] - points[v][1]);
                    pq.push({newCost, v});
                }
            }
        }

        return result;
    }
};
```

---

## ⚡ Complexity

- **Time Complexity:** O(n2log⁡n)O(n^2 \log n)
    
    - Each node can push up to nn edges into the heap.
        
- **Space Complexity:** O(n2)O(n^2) in the worst case (heap stores many edges).
    

This is still **optimal for the constraints** (up to 1000 points → ~1e6 edges max).

---


# KRUSKALS'S ( IF NODES WERE LESS)

## 🔹 When to use Kruskal’s Algorithm

- Kruskal’s is **edge-based**:
    
    - Sort all edges by weight.
        
    - Pick the smallest edge that doesn’t form a cycle (using **Disjoint Set Union (DSU/Union-Find)**).
        
- It works very well when **edges < nodes²** (i.e. graph is sparse).
    
- In our problem (complete graph of points), edges = n2n^2, so **Prim’s is better**.
    
- But if **nodes were small (say ≤ 200)**, Kruskal’s would still be fine.
    

---

## 🔹 Kruskal’s Algorithm Implementation (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false; // cycle detected

        // union by rank
        if (rank[rootX] < rank[rootY]) swap(rootX, rootY);
        parent[rootY] = rootX;
        if (rank[rootX] == rank[rootY]) rank[rootX]++;
        return true;
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<array<int, 3>> edges; // {cost, u, v}

        // Build all edges (O(n^2))
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int cost = abs(points[i][0] - points[j][0]) +
                           abs(points[i][1] - points[j][1]);
                edges.push_back({cost, i, j});
            }
        }

        // Sort edges by cost (O(E log E))
        sort(edges.begin(), edges.end());

        DSU dsu(n);
        int result = 0, edgesUsed = 0;

        for (auto& e : edges) {
            int cost = e[0], u = e[1], v = e[2];
            if (dsu.unite(u, v)) { // if u,v are not already connected
                result += cost;
                edgesUsed++;
                if (edgesUsed == n - 1) break; // MST complete
            }
        }

        return result;
    }
};
```

---

## ⚡ Complexity

- **Build edges:** O(n2)O(n^2)
    
- **Sort edges:** O(Elog⁡E)O(E \log E), where E=n2E = n^2 → O(n2log⁡n2)O(n^2 \log n^2).
    
- **DSU operations:** ~O(Eα(n))O(E \alpha(n)), almost linear.
    
- **Space:** O(E)O(E).
    

So if nn is **small (≤ 200)**, Kruskal’s is perfectly fine.  
But if n=1000n = 1000, then E≈500kE ≈ 500k, sorting that is costly → **Prim’s wins**.

---

# DRY-RUN

Nice — let’s **walk Prim’s algorithm step-by-step** on Example 1 and watch the MST build in slow motion. I’ll show the distance matrix, the priority/key updates, which vertex we pick each step, the edge chosen, and the running total.

---

# Prim’s Dry Run — Example 1

Points (index → coordinates):
0: (0,0)
1: (2,2)
2: (3,10)
3: (5,2)
4: (7,0)

Manhattan distance $ = |x_i-x_j| + |y_i-y_j|$.

## 1) Distance matrix (Manhattan)

```
      0   1   2   3   4
 0 [  0,  4, 13,  7,  7 ]
 1 [  4,  0,  9,  3,  7 ]
 2 [ 13,  9,  0, 10, 14 ]
 3 [  7,  3, 10,  0,  4 ]
 4 [  7,  7, 14,  4,  0 ]
```

(Entry (i,j) is distance from point i to point j.)

---

## 2) Initialization

* Start at node `0` (JFK-style start; any start works for Prim).
* `MST = {0}` initially.
* `key[]` = min cost to connect each non-MST node to the current MST:

  * key\[0] = 0 (already in MST)
  * key\[1] = 4  (dist(0,1))
  * key\[2] = 13 (dist(0,2))
  * key\[3] = 7  (dist(0,3))
  * key\[4] = 7  (dist(0,4))
* total\_cost = 0

We pick the smallest key among nodes not in MST each iteration.

---

## 3) Iteration 1 — pick node 1

* Smallest key (outside MST): node `1` with key = **4**.
* Add edge chosen: **(0 — 1)** with cost **4**.
* total\_cost = 0 + 4 = **4**
* MST now `{0,1}`

**Update keys using node 1:**

* For each v not in MST:

  * v=2: current key 13, dist(1,2)=9 → update key\[2]=9, parent\[2]=1
  * v=3: current key 7, dist(1,3)=3  → update key\[3]=3, parent\[3]=1
  * v=4: current key 7, dist(1,4)=7  → key\[4] stays 7

Keys now: key = \[0, 4, 9, 3, 7]

---

## 4) Iteration 2 — pick node 3

* Smallest key: node `3` with key = **3**.
* Add edge chosen: **(1 — 3)** with cost **3** (we use parent information).
* total\_cost = 4 + 3 = **7**
* MST now `{0,1,3}`

**Update keys using node 3:**

* v=2: current key 9, dist(3,2)=10 → 10 > 9 → no change
* v=4: current key 7, dist(3,4)=4  → update key\[4]=4, parent\[4]=3

Keys now: key = \[0,4,9,3,4]

---

## 5) Iteration 3 — pick node 4

* Smallest key: node `4` with key = **4**.
* Add edge chosen: **(3 — 4)** with cost **4**.
* total\_cost = 7 + 4 = **11**
* MST now `{0,1,3,4}`

**Update keys using node 4:**

* remaining node is `2`: current key 9, dist(4,2)=14 → no change.

Keys now: key = \[0,4,9,3,4]

---

## 6) Iteration 4 — pick node 2

* Only remaining node: node `2` with key = **9**.
* Add edge chosen: **(1 — 2)** with cost **9** (parent\[2]=1).
* total\_cost = 11 + 9 = **20**
* MST now `{0,1,2,3,4}` — all nodes included → stop.

---

## 7) Final MST edges and cost

Edges chosen (with costs):

* (0 — 1) : 4
* (1 — 3) : 3
* (3 — 4) : 4
* (1 — 2) : 9

Total minimum cost = **4 + 3 + 4 + 9 = 20**

This matches the expected output.

---

## Why Prim here?

* The complete graph (every pair of points has an edge with Manhattan cost) is dense: \~n² edges.
* Building all edges and sorting (Kruskal) would be expensive.
* Prim grows the MST using only O(n²) distance checks (or O(n log n) with heap + efficient updates) — ideal for this problem.

---

## Complexity notes

* Straightforward Prim with an array of keys (no heap) is `O(n^2)` and often simplest for `n ≤ 1000`.
* Using a binary heap / priority queue can give `O(E log V)` but for dense complete graphs `E ≈ V²` so that is not asymptotically better; practical choice depends on constants and language.

---


