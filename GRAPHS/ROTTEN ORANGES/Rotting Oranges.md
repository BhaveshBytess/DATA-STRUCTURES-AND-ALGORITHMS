Absolutely — here’s **LeetCode-Style Stage 3: Rotting Oranges**, no hints, no solutions — just the raw problem. Let’s grind. 💪

---

## 🧩 **LeetCode 994: Rotting Oranges**

**Difficulty**: Medium  
**Topics**: Graph, Grid, Breadth-First Search (BFS), Queue

---

### 🔔 Problem Statement

You are given an `m x n` **grid** where each cell can have one of three values:

- `0`: empty cell
    
- `1`: fresh orange
    
- `2`: rotten orange
    

Every minute, **any fresh orange** that is **4-directionally adjacent** to a rotten orange becomes rotten.

Return the **minimum number of minutes** that must elapse until **no fresh orange remains**.  
If it is **impossible** to rot all the fresh oranges, return `-1`.

---

### 📥 Input

- `grid`: `vector<vector<int>>`, a 2D grid of integers (size `m x n`)
    
    - Each cell is either: `0`, `1`, or `2`.
        

---

### 📤 Output

- Return a single integer:
    
    - Minimum number of minutes to rot all oranges, or
        
    - `-1` if it’s impossible.
        

---

### 🧪 Example

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

### 📎 Constraints

- `m == grid.length`
    
- `n == grid[i].length`
    
- `1 <= m, n <= 10`
    
- `grid[i][j]` is `0`, `1`, or `2`.
    

---

When you’re ready, start grinding it out.  
You know the pact: **no spoon-feeding**, only nudging — whenever you say “nudge”, I’ll walk with you.


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




![[Pasted image 20250729185809.png]]

![[Pasted image 20250729185831.png]]


Great job writing this out so early in the grind — your effort is on point. 💯  
Now let’s **analyze it deeply** and do a **Reality Check**, just like we always do:

---

### ✅ **What You Got Right**

- You're clearly using a **DFS-style approach** — good instinct.
    
- You’ve already written the boundary check, grid value checks (`== 0`, `== 2`) — clean thinking.
    
- You're modifying grid values (`grid[i][j] = 2`) — that’s key.
    
- You’re visiting **4 directions**: top, bottom, left, right — that’s exactly how it should be.
    

So structurally, you're in the **right territory**.

---

### ❌ **Where It Falls Apart**

This is **not a pure DFS problem**. Here's why your code will **not give correct results** on LeetCode:

#### 🔻 1. You're using DFS — but **time is not being tracked**.

This is not just about **reaching** oranges.  
It's about:

> **How many minutes** it takes for fresh oranges to rot from the source rotten ones.

You need to model **time flow** — DFS doesn’t naturally handle that.  
You need **level-by-level traversal** (i.e., **BFS**) — where every level = 1 minute.

#### 🔻 2. DFS rots all connected oranges **instantly** #ROTTEN_ORANGES 

In your DFS, when you call:

```cpp
dfs(i+1, j, grid);
```

That orange is **instantly** rotted, which contradicts the problem — **rotting should take time per level**.

---

### 🔄 So What Needs to Change?

- You need to switch from DFS → **BFS** (Breadth First Search).
    
- Use a **queue** to store rotten oranges with their time.
    
- At each step (minute), rot all 4-directionally adjacent fresh oranges and push them into the queue with `time + 1`.
    

---

### Summary: Your Code Status

|Criteria|Status|
|---|---|
|Logic Structure|✅ Good Start|
|Time Tracking|❌ Missing|
|Correct Result|❌ Will fail on time-sensitive test cases|
|Core Algorithm Match|❌ DFS not ideal here, needs BFS|

---

### 🔥 Bhavesh-style Verdict:

- You're **thinking clearly** and following patterns — great.
    
- But here, you need to **ditch DFS** and go **full BFS**, because this is not just a traversal — this is **simulating real-time spread**.
    

Let me know if you want to write the **BFS version together**, or if you want just a **nudge** and you'll grind it solo.

Your move. 🧠👊


---


Here is the **final, correct C++ solution** to the **Rotting Oranges** problem using **BFS (level-order traversal)** — the only correct approach for simulating time (minutes):

---

### ✅ Problem Recap (LeetCode style):

> **Every minute**, any **fresh orange** (`1`) that is **4-directionally adjacent** to a **rotten orange** (`2`) becomes rotten.  
> Return the **minimum number of minutes** that must elapse until **no cell has a fresh orange**.  
> If this is impossible, return `-1`.

---

### ✅ Final Code (C++ – BFS with time simulation):

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

### 🧠 Key Concepts:

- **Multi-source BFS**: Start BFS from all rotten oranges simultaneously.
    
- **Time = Levels of BFS**: Each level of BFS = 1 minute passed.
    
- **Visited Grid Not Needed**: You mark visited by converting `1 → 2`.
    

---

### ✅ Time & Space Complexity:

- **Time**: `O(n * m)` — we visit each cell at most once.
    
- **Space**: `O(n * m)` — for queue storage in worst case.
    

---

Let me know if you want this converted to **Java or Python**, or want a **step-by-step dry run** for a sample grid.