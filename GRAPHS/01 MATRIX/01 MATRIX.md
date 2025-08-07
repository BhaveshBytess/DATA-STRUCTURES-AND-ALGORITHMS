Sure! Here’s the **01 Matrix problem** in **LeetCode-style** — **no hints, no solutions**, just the problem statement crafted for your grind-style focus. 

---

## LeetCode-Style Problem: **01 Matrix**

> **Given** an `m x n` binary matrix `mat`, return the **distance of the nearest 0 for each cell**.

Each cell contains either a `0` or a `1`.  
For **each cell** with a `1`, compute the **distance to the nearest 0** in the matrix.

---

### Input:

- A 2D matrix `mat` of size `m x n` consisting only of `0`s and `1`s.
    

---

### Output:

- Return a matrix of the same size where each cell contains the **distance to the nearest 0**.
    

---

### Constraints:

- `1 <= m, n <= 10⁴`
    
- `0 <= mat[i][j] <= 1`
    
- The distance between two adjacent cells is `1`.
    

---

### Example:

#### Input:

```
mat = [
  [0,0,0],
  [0,1,0],
  [1,1,1]
]
```

#### Output:

```
[
  [0,0,0],
  [0,1,0],
  [1,2,1]
]
```

---



Here's the **final clean C++ code** for the **01 Matrix** problem using **multi-source BFS**, optimized and ready for submission:

---

### Problem:

For each cell containing `1`, find the **shortest distance** to the **nearest cell containing `0`**.  
Return the resulting matrix of distances.

---


# MINI-NOTE :

🔹 **Problem:** 01 Matrix (Leetcode 542)  
🔹 **Graph Type:** Implicit Grid Graph (2D Matrix)  
🔹 **Technique:** Multi-Source BFS  
🔹 **Core Template:**

```cpp
queue<pair<int, int>> q;
// Step 1: push all 0s into queue, set 1s as INT_MAX
while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (4 directions) {
        if (valid && new_dist < mat[ni][nj]) {
            mat[ni][nj] = new_dist;
            q.push({ni, nj});
        }
    }
}
```

🔹 **Pattern Tag:** #GridBFS #MultiSourceBFS #ShortestDistance #MatrixPropagation

---

🔸 **Logic Summary:**

- You’re given a matrix of `0`s and `1`s.
    
- Goal: For every cell with `1`, compute the **shortest distance to the nearest `0`**.
    
- Push all `0`s into the queue initially → perform **multi-source BFS**.
    
- For each cell popped from the queue, update its 4-directional neighbors **only if the current path gives a shorter distance**.
    

---

🔸 **Trick:**

- Start BFS from **all zeroes** (multi-source), and treat them as level 0.
    
- For all `1`s → initialize as `INT_MAX` or `-1` (if using a visited array separately).
    
- Distance increases level by level during BFS traversal.
    

---

🔸 **Why DP or DFS alone won’t work:**

- DP Top-Down fails due to circular dependencies (a 1 may depend on another 1).
    
- DFS can't guarantee **shortest path** in all directions simultaneously.
    

---

🔸 **Final Insight:**

This is a **distance-to-nearest-source problem** in a grid, and hence **multi-source BFS** is the best approach.  
Whenever the shortest path from multiple sources is needed, think of **BFS with initial multi-start nodes**.


---

### Final Code (C++ - BFS):

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();
    
    queue<pair<int, int>> q;
    vector<vector<int>> dist(n, vector<int>(m, -1)); // -1 means unvisited

    // Step 1: Push all 0s into the queue and set their distance to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                q.push({i, j});
                dist[i][j] = 0;
            }
        }
    }

    // 4-directional movement
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Step 2: Multi-source BFS
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            // Check bounds and if not visited yet
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return dist;
}
```

---

### Key Points Recap:

- You start BFS from all cells that are already `0`.
    
- Each `1` will get updated to the distance from the nearest `0`.
    
- You **don’t need DFS** or to manually track `step++` globally — it's automatically managed per level in BFS.
    
