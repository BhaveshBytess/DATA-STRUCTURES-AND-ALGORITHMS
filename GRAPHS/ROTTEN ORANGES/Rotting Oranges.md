## **LeetCode 994: Rotting Oranges**

**Difficulty**: Medium  
**Topics**: Graph, Grid, Breadth-First Search (BFS), Queue

---

### Problem Statement

You are given an `m x n` **grid** where each cell can have one of three values:

- `0`: empty cell
    
- `1`: fresh orange
    
- `2`: rotten orange
    

Every minute, **any fresh orange** that is **4-directionally adjacent** to a rotten orange becomes rotten.

Return the **minimum number of minutes** that must elapse until **no fresh orange remains**.  
If it is **impossible** to rot all the fresh oranges, return `-1`.

---

### Input

- `grid`: `vector<vector<int>>`, a 2D grid of integers (size `m x n`)
    
    - Each cell is either: `0`, `1`, or `2`.
        

---

### Output

- Return a single integer:
    
    - Minimum number of minutes to rot all oranges, or
        
    - `-1` if it’s impossible.
        

---

### Example

**Input:**

```
grid = [
  [2,1,1],
  [1,1,0],
  [0,1,1]
]
```

**Output:**

```
4
```

---

### Constraints

- `m == grid.length`
    
- `n == grid[i].length`
    
- `1 <= m, n <= 10`
    
- `grid[i][j]` is `0`, `1`, or `2`.


---

# MINI-NOTE : 

Here’s your structured **Mini Note** for the **Rotten Oranges** problem (`Leetcode 994`) following your revision format:

---
🔹 **Problem:** Rotten Oranges (Leetcode 994)  
🔹 **Graph Type:** Implicit Grid Graph (2D Matrix)  
🔹 **Technique:** Multi-Source BFS  
🔹 **Core Template:** BFS from all initially rotten oranges (queue of coordinates)  
🔹 **Pattern Tag:** #GridBFS #MultiSourceBFS #ShortestPath #RottingSpread

---

🔸 **Logic Summary:**

- Treat the **grid as a graph** where each orange is a node.
    
- Rotten oranges (value `2`) are **starting points**, push all of them into queue with `time=0`.
    
- For every minute (level in BFS), infect adjacent fresh oranges (`value = 1`).
    
- Use a visited matrix or mark directly in grid by changing 1 → 2.
    
- Track maximum time and number of fresh oranges turned rotten.
    
- At the end, if **any fresh orange remains**, return `-1`.  
    Else, return the **maximum time taken** (i.e., total minutes).
    

---

🔸 **Trick:**

- Use **direction array**: `dx[4] = {-1,0,1,0}`, `dy[4] = {0,1,0,-1}` for 4 directions.
    
- Push `(i, j, time)` into queue — no need to track level separately.
    
- Count total fresh oranges initially and reduce it on infection → for final check.
    

---

🔸 **Why DFS or Single Source BFS won’t work:**

- Infection spreads from **multiple rotten oranges at once** → **multi-source BFS** is needed.
    
- DFS won't give correct **minimum time** as it explores one path too deep.
    

---

🔸 **Final Insight:**

This is a **classic simulation + BFS** over 2D grid where **level = minutes**.  
Whenever a problem involves **spread, infection, fire, signal**, etc. from **multiple sources**, use **multi-source BFS**.


---


Here is the **final, correct C++ solution** to the **Rotting Oranges** problem using **BFS (level-order traversal)** — the only correct approach for simulating time (minutes):

---

### Problem Recap (LeetCode style):

> **Every minute**, any **fresh orange** (`1`) that is **4-directionally adjacent** to a **rotten orange** (`2`) becomes rotten.  
> Return the **minimum number of minutes** that must elapse until **no cell has a fresh orange**.  
> If this is impossible, return `-1`.

---

### Final Code (C++ – BFS with time simulation):

```cpp
#include <vector>
#include <queue>
using namespace std;

int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0;

    // Step 1: Push all initially rotten oranges & count fresh ones
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            } else if (grid[i][j] == 1) {
                fresh++;
            }
        }
    }

    // If no fresh oranges at all
    if (fresh == 0) return 0;

    // Directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int minutes = 0;

    // Step 2: BFS traversal
    while (!q.empty()) {
        int size = q.size();
        bool rottedThisMinute = false;

        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                // If valid and fresh orange
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;        // Rot it
                    fresh--;                 // One less fresh orange
                    q.push({nx, ny});        // Add to queue for next minute
                    rottedThisMinute = true; // At least one orange rotted
                }
            }
        }

        if (rottedThisMinute) minutes++;  // Increase time only if something rotted
    }

    return (fresh == 0) ? minutes : -1;   // If fresh oranges still left, return -1
}
```

---

### Key Concepts:

- **Multi-source BFS**: Start BFS from all rotten oranges simultaneously.
    
- **Time = Levels of BFS**: Each level of BFS = 1 minute passed.
    
- **Visited Grid Not Needed**: You mark visited by converting `1 → 2`.
    

---

### Time & Space Complexity:

- **Time**: `O(n * m)` — we visit each cell at most once.
    
- **Space**: `O(n * m)` — for queue storage in worst case.
    
