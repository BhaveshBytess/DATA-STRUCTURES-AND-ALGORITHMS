
Absolutely! Here's the next graph BFS classic:

---

### 🧩 **286. Walls and Gates** — [Medium]

**LeetCode**  
**Topics:** Graph, BFS, Matrix  
**Company Tags:** Amazon, Facebook, Google, Microsoft

---

You are given an `m x n` 2D grid **rooms** initialized with these three possible values:

- `-1` represents a **wall or an obstacle**.
    
- `0` represents a **gate**.
    
- `INF` (2³¹ - 1) represents an **empty room**.
    

Fill each empty room with the **number of steps to its nearest gate**. If it is impossible to reach a gate, leave it as `INF`.

---

### 🔒 Constraints:

- Only move **up, down, left, right**.
    
- The grid may contain multiple gates.
    
- You **must update rooms in-place**.
    

---

### 🧾 Input Format:

```cpp
vector<vector<int>> rooms
```

Each `rooms[i][j]` is either `-1` (wall), `0` (gate), or `INF` (`2147483647`).

---

### 🧾 Output:

The grid should be **modified in-place**, where each empty room now contains the distance to its nearest gate.

---

### 🧪 Example:

```txt
Input:
rooms = [
  [2147483647, -1,  0, 2147483647],
  [2147483647, 2147483647, 2147483647, -1],
  [2147483647, -1, 2147483647, -1],
  [0, -1, 2147483647, 2147483647]
]

Output:
[
  [3, -1,  0,  1],
  [2,  2,  1, -1],
  [1, -1,  2, -1],
  [0, -1,  3,  4]
]
```

---

# MINI-NOTE : 


🔹 **Problem:** Walls and Gates (Leetcode 286)  
🔹 **Graph Type:** Implicit Grid Graph  
🔹 **Technique:** Multi-Source BFS  
🔹 **Core Template:**

```cpp
queue<pair<int, int>> q;
// Step 1: Push all gates (value 0) into the queue
while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (4 directions) {
        if (valid empty room && grid[ni][nj] == INF) {
            grid[ni][nj] = grid[i][j] + 1;
            q.push({ni, nj});
        }
    }
}
```

🔹 **Pattern Tag:** #MultiSourceBFS #GridBFS #ShortestDistance #MatrixPropagation

---

🔸 **Logic Summary:**

- You are given a grid with:
    
    - `-1` → wall
        
    - `0` → gate
        
    - `INF` (2³¹−1) → empty room
        
- Goal: Fill each empty room with the **distance to its nearest gate**.
    
- Perform **multi-source BFS** starting from all gates simultaneously.
    

---

🔸 **Trick:**

- Instead of BFS from each empty cell to find the nearest gate (TLE), **start BFS from all gates at once**.
    
- This ensures minimum steps (distance) is filled for each room in the shortest path fashion.
    

---

🔸 **Why DFS/DP won’t work well:**

- DFS doesn't guarantee shortest path in an unweighted graph.
    
- DP is hard due to potential cycles and multiple directions of influence.
    

---

🔸 **Final Insight:**

This is a **classic matrix propagation from multiple origins** → apply **multi-source BFS** from all gates.  
The moment an empty room is reached, it’s already guaranteed to have the **shortest distance** from any gate.




---







![[Pasted image 20250731160249.png]]
![[Pasted image 20250731160407.png]]



You're _very_ close, Bhavesh — the structure you've written follows the right logic for solving **Walls and Gates** (Leetcode 286) using **Multi-Source BFS**. 💯  
Let me walk you through your code and show you **minor issues + final clean code.**

---

### 🧠 Problem Recap: Walls and Gates (Leetcode 286)

You're given a grid of:

- `INF` (unreachable room)
    
- `0` (gate)
    
- `-1` (wall)
    

**Goal:**  
Fill each room with the _shortest distance to the nearest gate_ using **4-directional BFS**.

---

### ✅ What's Great in Your Code:

- ✅ You initialize queue with all gate positions (`0`) → that’s **multi-source BFS**!
    
- ✅ You use `dx` / `dy` arrays for 4-directional traversal.
    
- ✅ You update `rooms[nx][ny] = rooms[x][y] + 1` → **correct BFS step propagation**.
    
- ✅ Good use of early return if `er == 0` (no INF present) — optional but clever.
    

---

### 🔧 Small Fixes Needed:

#### 1. Typos:

- `rooms[x][y]` → typo written as `room[x][Y]` or `room(x)(y)` in places.
    
- `grid[nx][ny] == INF` → should be `rooms[nx][ny] == INF`
    
- `nx >= 0 && ny >= 0 && nx < n && ny < m` — bounds check corrected.
    
- Don't compare `rooms[i][j] == 0` inside `INF` check block; split conditions.
    

---

### ✅ Final Clean Code (C++ Style)

```cpp
vector<vector<int>> solve(vector<vector<int>>& rooms) {
    int n = rooms.size(), m = rooms[0].size();
    queue<pair<int, int>> q;

    // Step 1: Push all gates into the queue (Multi-Source BFS)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (rooms[i][j] == 0) {
                q.push({i, j});
            }
        }
    }

    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};

    // Step 2: BFS from all gates
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // Check bounds and if it's an empty room (INF)
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && rooms[nx][ny] == INT_MAX) {
                rooms[nx][ny] = rooms[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return rooms;
}
```

---

### 🧠 Why BFS Works Here?

- This is a **grid-based shortest distance** problem.
    
- Every edge (movement) has equal weight (distance = 1).
    
- You're starting from _multiple sources_ (all gates) and expanding outward → this is a **classic Multi-Source BFS** case.
    
- DFS fails here because it may explore one long path without guaranteeing shortest steps.
    

---

### 🎯 Tips for You

1. **Trust BFS for shortest path** in unweighted grids.
    
2. **Think in terms of waves** — gates infecting nearby cells in order.
    
3. **Avoid visited[][] in such problems** — the grid itself stores distance.
    
4. Practice variations like:
    
    - 01 Matrix
        
    - Rotten Oranges
        
    - Knight Moves
        
    - Shortest Bridge
        

---

Great question, Bhavesh!  
The `-1` value — the **wall** — represents a **block** where you **cannot go**, and hence it needs **special treatment**.

---

### 🧱 What to Do for `-1` (Walls)?

You **don’t push it into the queue**, and you **never walk into it** during BFS.

Here’s how it works in the full logic:

#### ✅ 1. **Initialization:**

Only push **gates (`0`)** into the queue. Ignore:

- `INF` (empty rooms)
    
- `-1` (walls)
    

```cpp
if (rooms[i][j] == 0) {
    q.push({i, j}); // Only gates
}
```

#### ✅ 2. **BFS Traversal:**

During BFS, only continue if:

- The next cell is **within bounds**
    
- The cell is an **empty room (INF)** — this is where you can propagate distance
    

So you **automatically skip** walls because:

```cpp
if (rooms[nx][ny] == INT_MAX) {
    rooms[nx][ny] = rooms[x][y] + 1;
    q.push({nx, ny});
}
```

No need to explicitly check for `-1`.  
Why? Because `rooms[nx][ny] == -1` will fail the `== INT_MAX` check and never be updated.

---

### 🔁 Example Walkthrough:

Let’s say grid is:

```
rooms = [
  [INF, -1,   0, INF],
  [INF, INF, INF, -1],
  [INF, -1, INF, -1],
  [0,   -1, INF, INF]
]
```

- The two `0`s are the gates → they go in the queue initially.
    
- BFS spreads step-by-step to adjacent INF rooms.
    
- Walls (`-1`) are skipped entirely because:
    
    - They are not `INT_MAX`
        
    - They are not pushed into the queue
        
    - They are not updated
        

---

### 🔒 Summary

|Cell Type|Push to Queue Initially?|Can be Traversed Into?|
|---|---|---|
|`0` (gate)|✅ Yes|🔁 No (already processed)|
|`INF`|❌ No|✅ Yes|
|`-1` (wall)|❌ No|❌ No|

---

Let me know if you want a dry run on a sample grid with walls to see how it flows 👇