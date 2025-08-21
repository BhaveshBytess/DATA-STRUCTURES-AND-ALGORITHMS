
## **1631. Path With Minimum Effort**

You are a hiker preparing for an expedition across a rectangular grid of heights represented by a 2D array `heights`.

- `heights[r][c]` represents the height of cell `(r, c)`.
    
- You can move up, down, left, or right (4 directions) to an adjacent cell.
    
- The **effort** of a path is the **maximum absolute difference in heights** between two consecutive cells along the path.
    

Return the **minimum effort** required to travel from the top-left cell `(0, 0)` to the bottom-right cell `(rows-1, cols-1)`.

---

**Example 1:**

Input:

```
heights = [[1,2,2],[3,8,2],[5,3,5]]
```

Output:

```
2
```

Explanation:  
Path `[1 → 2 → 2 → 2 → 5 → 5]` has max difference = 2.

---

**Example 2:**

Input:

```
heights = [[1,2,3],[3,8,4],[5,3,5]]
```

Output:

```
1
```

Explanation:  
Path `[1 → 2 → 3 → 4 → 5]` has max difference = 1.

---

**Example 3:**

Input:

```
heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
```

Output:

```
0
```

Explanation:  
Path goes through only cells with same height, so max diff = 0.

---

**Constraints:**

- `rows == heights.length`
    
- `cols == heights[i].length`
    
- `1 <= rows, cols <= 100`
    
- `1 <= heights[i][j] <= 10^6`
    

---


# MINI-NOTE : 


🔹 **Problem:**  

You are given a `rows x cols` grid of heights. You start at `(0,0)` and want to reach `(rows-1, cols-1)` by moving in 4 directions.  
The **effort** of a path is the **maximum absolute difference in heights between consecutive cells**. Find the **minimum effort required** to reach the destination.

🔹 **Graph Type:**

- Weighted, undirected implicit graph (grid)
    
- Nodes = cells
    
- Edge weight = `abs(height[u] - height[v])`
    

🔹 **Technique:**

- Dijkstra algorithm using a **priority queue**
    
- Use `max(current_effort, edge_weight)` instead of sum
    

🔹 **Core Template:**

```cpp
priority_queue<pair<int,pair<int,int>>, vector<...>, greater<>> pq;
vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
effort[0][0] = 0;
pq.push({0, {0,0}});

while(!pq.empty()){
    auto [cur_effort, cell] = pq.top(); pq.pop();
    if(cell == destination) return cur_effort;

    for(all neighbors){
        int next_effort = max(cur_effort, abs(height_diff));
        if(next_effort < effort[nx][ny]){
            effort[nx][ny] = next_effort;
            pq.push({next_effort, {nx, ny}});
        }
    }
}
```

🔹 **Pattern Tag:**

- Dijkstra on grid
    
- Path optimization with max edge cost
    

🔸 **Logic Summary:**

- Instead of summing weights, maintain the **maximum weight along the path**.
    
- Priority queue always explores paths with **smaller maximum edge** first.
    
- BFS-style neighbor traversal works, but must **relax using max**.
    

🔸 **Trick:**

- Don’t use simple BFS distance array; **max operation is key**.
    
- Early exit as soon as destination is popped from PQ.
    

🔸 **Why BFS alone fails:**

- BFS finds **minimum steps**, not **minimum maximum edge**.
    
- Max edge along path may be larger in shorter step paths.
    

🔸 **Final Insight:**

- Treat grid as weighted graph where weight = height difference.
    
- Path minimum effort = **minimum of the maximum edge along path**.
    
- Dijkstra with max relaxation guarantees correctness.
    

---

# SOLUTION : 


```cpp
#include <bits/stdc++.h>
using namespace std;

int minimumEffortPath(vector<vector<int>>& heights) {
    int rows = heights.size();
    int cols = heights[0].size();

    // Directions: right, left, down, up
    vector<int> dx = {0, 0, 1, -1};
    vector<int> dy = {1, -1, 0, 0};

    // Effort matrix initialized to INF
    vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
    effort[0][0] = 0;

    // Min-heap priority queue: {effort_so_far, {x, y}}
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<>> pq;
    pq.push({0, {0,0}});

    while(!pq.empty()) {
        auto [curEffort, cell] = pq.top();
        pq.pop();
        int x = cell.first;
        int y = cell.second;

        // Destination reached
        if(x == rows - 1 && y == cols - 1) return curEffort;

        // Explore neighbors
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                int nextEffort = max(curEffort, abs(heights[x][y] - heights[nx][ny]));

                if(nextEffort < effort[nx][ny]) {
                    effort[nx][ny] = nextEffort;
                    pq.push({nextEffort, {nx, ny}});
                }
            }
        }
    }

    return 0; // unreachable (problem guarantees path exists)
}

int main() {
    vector<vector<int>> heights = {{1,2,2},{3,8,2},{5,3,5}};
    cout << minimumEffortPath(heights) << endl; // Output: 2
    return 0;
}
```

✅ **Key Points in Code:**

1. Priority queue ensures **smallest effort path is explored first**.
    
2. `nextEffort = max(curEffort, abs(height diff))` → **critical Dijkstra modification**.
    
3. Early exit when destination cell is popped.
    

---

# DRY RUN : 

### Grid Example:

```
heights = [[1, 2, 2],
           [3, 8, 2],
           [5, 3, 5]]
```

We want to get from `(0,0)` → `(2,2)` with **minimum maximum effort**.

---

### Step 1: Initialize

- `rows = 3, cols = 3`
    
- `effort[r][c]` = minimum effort to reach `(r,c)`  
    Initially:
    

```
effort = [[0, ∞, ∞],
          [∞, ∞, ∞],
          [∞, ∞, ∞]]
```

- Priority Queue (min-heap) stores `(effort, x, y)`  
    Initially: `pq = [(0,0,0)]`
    

---

### Step 2: Pop from PQ → `(0,0)` with effort 0

- Neighbors: `(0,1)` and `(1,0)`
    
- Calculate edge effort:
    
    - `(0,0)` → `(0,1)`: `abs(1-2)=1` → new effort = `max(0,1)=1`  
        Update effort: `effort[0][1] = 1` → push `(1,0,1)`
        
    - `(0,0)` → `(1,0)`: `abs(1-3)=2` → new effort = `max(0,2)=2`  
        Update effort: `effort[1][0] = 2` → push `(2,1,0)`
        

Effort grid now:

```
[[0, 1, ∞],
 [2, ∞, ∞],
 [∞, ∞, ∞]]
```

PQ: `[(1,0,1), (2,1,0)]`

---

### Step 3: Pop `(0,1)` with effort 1

- Neighbors: `(0,0)`, `(0,2)`, `(1,1)`
    
- `(0,0)` already has 0 → skip
    
- `(0,2)`: `abs(2-2)=0` → new effort = `max(1,0)=1` → update `effort[0][2]=1` → push `(1,0,2)`
    
- `(1,1)`: `abs(2-8)=6` → new effort = `max(1,6)=6` → update `effort[1][1]=6` → push `(6,1,1)`
    

Effort grid:

```
[[0, 1, 1],
 [2, 6, ∞],
 [∞, ∞, ∞]]
```

PQ: `[(1,0,2), (2,1,0), (6,1,1)]`

---

### Step 4: Pop `(0,2)` with effort 1

- Neighbors: `(0,1)`, `(1,2)`
    
- `(0,1)` already 1 → skip
    
- `(1,2)`: `abs(2-2)=0` → new effort = `max(1,0)=1` → update `effort[1][2]=1` → push `(1,1,2)`
    

Effort grid:

```
[[0, 1, 1],
 [2, 6, 1],
 [∞, ∞, ∞]]
```

PQ: `[(1,1,2), (2,1,0), (6,1,1)]`

---

### Step 5: Pop `(1,2)` with effort 1

- Neighbors: `(0,2)`, `(1,1)`, `(2,2)`
    
- `(0,2)` already 1 → skip
    
- `(1,1)`: `abs(2-8)=6` → new effort = `max(1,6)=6` → effort[1][1] already 6 → no change
    
- `(2,2)`: `abs(2-5)=3` → new effort = `max(1,3)=3` → update `effort[2][2]=3` → push `(3,2,2)`
    

Effort grid:

```
[[0, 1, 1],
 [2, 6, 1],
 [∞, ∞, 3]]
```

PQ: `[(2,1,0), (6,1,1), (3,2,2)]`

---

### Step 6: Pop `(2,2)` with effort 3 → **destination reached**

- Minimum maximum effort = **3** ✅
    

---

### Step 7: Done

- The **path with minimum effort** would be:  
    `(0,0) → (0,1) → (0,2) → (1,2) → (2,2)`
    
- Maximum height difference along the path = `3`
    

---

### ✅ Observations

1. The **priority queue ensures** we always explore the path with least “effort-so-far” first.
    
2. The **edge relaxation** uses `max(current_effort, abs(height_diff))` instead of `current_effort + weight`.
    
3. BFS style looping works for neighbors, but **Dijkstra logic ensures correctness** for max edge cost paths.
    
4. As soon as destination pops from PQ → answer found.
    

---
