
## **Swim in Rising Water**

You are given an `n x n` integer matrix `grid` where each value `grid[i][j]` represents the **elevation** at that point `(i, j)`.

Initially, the water level is at time `t = 0`. At any time `t`, you can **swim** from a cell to another **4-directionally adjacent cell** if and only if the elevation of both cells is **at most t**.

You can swim infinite distance but only to adjacent cells under this condition.  
Return the **minimum time `t`** such that you can swim from the top-left cell `(0, 0)` to the bottom-right cell `(n-1, n-1)`.

---

### **Example 1**

**Input:**

```
grid = [
  [0,2],
  [1,3]
]
```

**Output:**

```
3
```

**Explanation:**  
At `t = 3`, we can reach `(1,1)` from `(0,0)` following the path `0 → 1 → 3`.

---

### **Example 2**

**Input:**

```
grid = [
  [0,1,2,3,4],
  [24,23,22,21,5],
  [12,13,14,15,16],
  [11,17,18,19,20],
  [10,9,8,7,6]
]
```

**Output:**

```
16
```

---

### **Constraints**

- `n == grid.length == grid[i].length`
    
- `1 <= n <= 50`
    
- `0 <= grid[i][j] < n^2`
    
- All values of `grid[i][j]` are **unique**
    

---

# MINI-NOTE : 

Here’s the **mini note** for **“Swim in Rising Water”** with **high verbosity**:

---

## 🔹 Problem

You are given an `n x n` grid where each cell represents the time at which water rises to that level.  
You start at `(0,0)` and must reach `(n-1,n-1)`.  
At time `t`, you can only enter cells with elevation ≤ `t`.  
Return the minimum `t` such that a path exists.

---

## 🔹 Graph Type

- Implicit Graph (grid-based).
    
- Nodes = cells `(i,j)`.
    
- Edges = 4-directional moves (up, down, left, right).
    
- Weighted graph → weight is **max height encountered so far**.
    

---

## 🔹 Technique

- **Dijkstra’s Algorithm / Min-Heap Priority Queue**.
    
- Each step: choose the "least costly" (lowest elevation so far) cell to expand.
    

---

## 🔹 Core Template (PQ-Dijkstra on Grid)

```cpp
int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    priority_queue<pair<int, pair<int,int>>, 
                   vector<pair<int, pair<int,int>>>, 
                   greater<>> pq;

    dist[0][0] = grid[0][0];
    pq.push({grid[0][0], {0,0}});
    vector<int> dirs = {0,1,0,-1,0};

    while (!pq.empty()) {
        auto [t, pos] = pq.top(); pq.pop();
        int x = pos.first, y = pos.second;

        if (x == n-1 && y == n-1) return t;

        for (int k = 0; k < 4; k++) {
            int nx = x + dirs[k], ny = y + dirs[k+1];
            if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                int newT = max(t, grid[nx][ny]);
                if (newT < dist[nx][ny]) {
                    dist[nx][ny] = newT;
                    pq.push({newT, {nx, ny}});
                }
            }
        }
    }
    return -1; // should never reach here
}
```

---

## 🔹 Pattern Tag

- Graph → Shortest Path
    
- Dijkstra Variant (minimize _max weight_, not sum)
    
- Grid + PQ
    

---

## 🔸 Logic Summary

- Normally, Dijkstra minimizes sum of weights.
    
- Here, we minimize the **maximum elevation encountered so far**.
    
- Use priority queue to always expand the lowest possible "time".
    
- Answer = when `(n-1,n-1)` is popped, since it’s guaranteed minimum.
    

---

## 🔸 Trick

- Don’t confuse with BFS → BFS fails since weights vary.
    
- PQ ensures correct order of exploring increasing elevation.
    
- The `max()` is the key idea: "effort = bottleneck height so far".
    

---

## 🔸 Why Other Approaches Fail

- **DFS/Greedy**: May trap in high elevation path early.
    
- **Plain BFS**: Can’t handle weighted nature.
    
- **Binary Search + BFS** works but is `O(n^2 log n)` (slower than PQ-Dijkstra).
    

---

## 🔸 Final Insight

- This is **Dijkstra in disguise**.
    
- Replace “sum of weights” with “max of elevations so far.”
    
- PQ guarantees first arrival at target cell = optimal.
    
- Time complexity: **O(n² log n)**, optimal for this problem.
    

---

# SOLUTION : 

```cpp
class Solution {

public:

int swimInWater(vector<vector<int>>& grid) {

    int n = grid.size();

  

    vector<vector<int>> best(n, vector<int>(n, INT_MAX));

    best[0][0] = grid[0][0];

  

    // Min-heap: {time, {x,y}}

    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<>> pq;

    pq.push({grid[0][0], {0,0}});

  

    vector<int> dx = {0,0,1,-1};

    vector<int> dy = {1,-1,0,0};

  

    while(!pq.empty()){

        auto [time, cell] = pq.top(); pq.pop();

        int x = cell.first, y = cell.second;

  

        // reached destination

        if(x == n-1 && y == n-1) return time;

  

        for(int i=0; i<4; i++){

            int nx = x + dx[i], ny = y + dy[i];

            if(nx>=0 && nx<n && ny>=0 && ny<n){

                int nextTime = max(time, grid[nx][ny]);

                if(nextTime < best[nx][ny]){

                    best[nx][ny] = nextTime;

                    pq.push({nextTime, {nx,ny}});

                }

            }

        }

    }

    return -1; // never happens

}

};
```