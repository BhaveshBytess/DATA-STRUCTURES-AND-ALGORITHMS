
## Problem Statement

You are given a 2D grid `heights` of size `rows x cols`, where `heights[r][c]` represents the height of cell `(r, c)`.

You start at the top-left cell `(0,0)` and want to reach the bottom-right cell `(rows-1, cols-1)`.

You may move in four directions: up, down, left, or right.

---

## Effort Definition

The **effort of a path** is defined as:

```
maximum absolute difference in heights
between two consecutive cells along the path
```

We must return the **minimum possible effort** required to travel from start to destination.

---

## Constraints

- `1 <= rows, cols <= 100`
    
- `1 <= heights[i][j] <= 10^6`
    

---

# Key Insight (Transformation)

We are NOT computing effort for all paths.

Instead, we transform the problem:

> For a given effort limit `x`, can we reach the destination using only edges whose height difference is `<= x`?

This converts the problem into:

- Binary Search on Answer (effort)
    
- - Graph connectivity check (BFS/DFS)
        

---

# Binary Search Setup

## Core Variable

`x = maximum allowed effort between adjacent cells`

We want to **minimize x**.

---

## Answer Space

Minimum effort = `0`

Maximum effort = `1e6` (safe upper bound based on constraints)

Search space:

```
[0 … 1e6]
```

---

## Decision Function — isPossible(x)

For a given `x`:

1. Start from `(0,0)`.
    
2. Use BFS (or DFS).
    
3. From a cell `(r,c)`, you may move to `(nr,nc)` only if:
    

```
abs(heights[r][c] - heights[nr][nc]) <= x
```

4. If you can reach `(rows-1, cols-1)`, return `true`.
    
5. Otherwise return `false`.
    

This is a pure graph connectivity check under constraint.

---

## Monotonicity

If effort `x` allows a valid path,  
then any effort `> x` will also allow a path.

Why?  
Because increasing `x` only adds more allowed edges.

So feasibility looks like:

```
false false false true true true
```

We search for the **smallest true**.

---

# C++ Implementation

```cpp
class Solution {
public:

    bool isPossible(vector<vector<int>>& heights, int maxEffort) {
        int rows = heights.size();
        int cols = heights[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        queue<pair<int,int>> q;

        q.push({0, 0});
        visited[0][0] = true;

        int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == rows - 1 && c == cols - 1)
                return true;

            for (auto &d : dirs) {
                int nr = r + d[0];
                int nc = c + d[1];

                if (nr >= 0 && nr < rows &&
                    nc >= 0 && nc < cols &&
                    !visited[nr][nc] &&
                    abs(heights[r][c] - heights[nr][nc]) <= maxEffort) {

                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        return false;
    }

    int minimumEffortPath(vector<vector<int>>& heights) {
        int low = 0;
        int high = 1e6;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isPossible(heights, mid))
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};
```

---

# Time Complexity

- `isPossible(x)` = O(rows × cols)
    
- Binary Search = O(log(1e6)) ≈ 20
    

Total:

```
O((rows × cols) × log(1e6))
```

---

# Space Complexity

```
O(rows × cols)
```

---

# Common Mistakes

- Trying to compute effort of each path directly
    
- Forgetting visited matrix
    
- Mixing effort tracking inside BFS
    
- Using wrong boundary (largest true vs smallest true)
    

---

# Final Insight

> Binary Search controls which edges are allowed.  
> BFS checks whether the destination is reachable under that constraint.

This is the core pattern of Binary Search + Graph problems.

---

_(Phase 4 — Binary Search + Graph Hybrid)_


---


# MINI-NOTE : 

🔹 Problem  
Given a grid of heights, move from (0,0) to (rows-1, cols-1).  
Effort of a path = maximum absolute height difference between consecutive cells.  
Return the minimum possible effort.

---

🔹 Graph Type  
Grid Graph (4-directional)  
Binary Search on Answer + BFS/DFS connectivity

---

🔹 Technique  
Binary Search on effort  
For each candidate effort x → BFS to check reachability

---

🔹 Core Template

Binary Search:

- low = 0
    
- high = 1e6 (max possible difference)
    
- while (low < high)
    
    - mid
        
    - if isPossible(mid) → high = mid
        
    - else → low = mid + 1
        

isPossible(x):

- BFS from (0,0)
    
- Move only if abs(height difference) ≤ x
    
- If destination reachable → true
    

---

🔹 Pattern Tag  
#BinarySearchOnAnswer  
#GraphConnectivity  
#SmallestTrue

---

🔸 Logic Summary  
We are not computing path effort directly.  
We restrict edges with diff ≤ x and check if the graph remains connected.  
If reachable for x, it will also be reachable for any x'>x.

---

🔸 Trick

- Use visited matrix
    
- Never track path effort inside BFS
    
- Binary search controls allowed edge weight
    

---

🔸 Why Other Approach Won’t Work

- Enumerating all paths → exponential
    
- Greedy path choice → fails
    
- Plain BFS without constraint → ignores effort
    

---

🔸 Boundary  
Smallest x such that destination becomes reachable.

---

🔸 Final Insight  
Binary Search decides which edges are allowed.  
BFS checks if start and end remain connected under that constraint.

---

(Phase 4 – Binary Search + Graph Hybrid)
