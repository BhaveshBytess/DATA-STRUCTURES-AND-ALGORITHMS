Here’s the **LeetCode-style problem statement** for **695. Max Area of Island**, followed by the **mini note** in your requested format.

---

## **LeetCode-Style Question**

**695. Max Area of Island**  
**Medium**

---

**Description**  
You are given an `m x n` binary matrix `grid`. An island is a group of `1`'s (representing land) connected **4-directionally** (horizontal or vertical). You may assume all four edges of the grid are surrounded by water.

The **area** of an island is the number of cells with a value `1` in the island.

Return the **maximum area** of an island in `grid`. If there is no island, return `0`.

---

**Example 1:**

```
Input: grid = [
  [0,0,1,0,0,0,0,1,0,0,0,0,0],
  [0,0,0,0,0,0,0,1,1,1,0,0,0],
  [0,1,1,0,1,0,0,0,0,0,0,0,0],
  [0,1,0,0,1,1,0,0,1,0,1,0,0],
  [0,1,0,0,1,1,0,0,1,1,1,0,0],
  [0,0,0,0,0,0,0,0,0,0,1,0,0],
  [0,0,0,0,0,0,0,1,1,1,0,0,0],
  [0,0,0,0,0,0,0,1,1,0,0,0,0]
]
Output: 6
Explanation: The answer is not 11 because the island must be connected 4-directionally.
```

**Example 2:**

```
Input: grid = [
  [0,0,0,0,0,0,0,0]
]
Output: 0
```

---

**Constraints:**

- `m == grid.length`
    
- `n == grid[i].length`
    
- `1 <= m, n <= 50`
    
- `grid[i][j]` is either `0` or `1`.
    

---

## **Mini Note — Max Area of Island**

🔹 **Problem**  
Find the largest connected component of `1`s in a 2D grid using **4-directional** adjacency.

🔹 **Graph Type**  
Grid Graph (Undirected, Unweighted, Binary)

🔹 **Technique**  
DFS/BFS traversal to explore each island and count its size.

🔹 **Core Template**

```python
def dfs(r, c):
    if out_of_bounds or grid[r][c] == 0:
        return 0
    grid[r][c] = 0  # mark visited
    area = 1
    for dr, dc in directions:
        area += dfs(r + dr, c + dc)
    return area

max_area = 0
for i in range(m):
    for j in range(n):
        if grid[i][j] == 1:
            max_area = max(max_area, dfs(i, j))
return max_area
```

🔹 **Pattern Tag**  
Connected Components in Grid, Flood Fill, DFS/BFS

🔸 **Logic Summary**  
Iterate over each cell, when `1` found → explore connected island, count size, update max.

🔸 **Trick**  
Mark visited land as `0` to avoid extra visited array → saves space.

🔸 **Why DP/Greedy won’t work**  
Island discovery requires **global exploration**; DP would need to recompute overlapping regions and greedy can't ensure counting complete connected components.

🔸 **Final Insight**  
A direct application of flood fill; maximum area is found by **exploring and summing connected nodes** in all directions.

---

If you want, I can also give you a **space-optimized BFS + DFS hybrid** template that works for _all_ grid connected-component problems, so you don’t have to re-code logic every time. This way, your future grid graph questions like “number of islands”, “rotten oranges”, etc., will just be 3–4 lines of customization. Would you like me to do that?


---


## FINAL CODE 


```CPP
class Solution {
public:
    void dfs(int i, int j, vector<vector<int>>& grid, int& count) {
        int n = grid.size();
        int m = grid[0].size();
        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != 1) return;
        
        grid[i][j] = -1; // mark visited
        count++;
        
        dfs(i + 1, j, grid, count);
        dfs(i - 1, j, grid, count);
        dfs(i, j + 1, grid, count);
        dfs(i, j - 1, grid, count);
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int max_area = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    int count = 0;
                    dfs(i, j, grid, count);
                    max_area = max(max_area, count);
                }
            }
        }
        return max_area; 
    }
};

```