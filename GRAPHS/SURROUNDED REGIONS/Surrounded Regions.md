
## 130. Surrounded Regions

**Difficulty:** Medium

**Topics:** Array, Depth-First Search, Breadth-First Search, Union Find, Matrix

---

### Problem Description

You are given an `m x n` matrix `board` containing **letters** `'X'` and `'O'`, **capture regions** that are **surrounded**:

- **Connect**: A cell is connected to adjacent cells horizontally or vertically.
- **Region**: To form a region **connect every** `'O'` cell.
- **Surround**: The region is surrounded with `'X'` cells if you can **connect the region** with `'X'` cells and none of the region cells are on the edge of the `board`.

To capture a **surrounded region**, replace all `'O'`s with `'X'`s **in-place** within the original board. You do not need to return anything.

---

### Example 1:

```
Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
Explanation: Notice that an 'O' should not be flipped if:
- It is on the border, or
- It is adjacent to an 'O' that should not be flipped.
The bottom 'O' is on the border, so it is not flipped.
The other three 'O' form a surrounded region, so they are flipped.
```

### Example 2:

```
Input: board = [["X"]]
Output: [["X"]]
```

---

### Constraints:

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 200`
- `board[i][j]` is `'X'` or `'O'`.

---

### Function Signature:

```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        
    }
};
```

---


# MINI-NOTE :

🔹 **Problem:** Surrounded Regions  
🔹 **Matrix Type:** 2D Grid Traversal (nodes are cells, edges = 4-directional neighbors)  
🔹 **Technique:**

- **Reverse Thinking:** Instead of finding surrounded regions, find NON-surrounded ones
- **DFS/BFS from borders** to mark safe regions
- **Two-phase approach** with temporary marking

🔹 **Core Template:**

```cpp
void solve(vector<vector<char>>& board) {
    int n = board.size(), m = board[0].size();
    queue<pair<int,int>> q;
    
    // Phase 1: Add all border 'O's to queue and mark as safe ('S')
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if((i == 0 || i == n-1 || j == 0 || j == m-1) && board[i][j] == 'O') {
                board[i][j] = 'S';
                q.push({i, j});
            }
        }
    }
    
    // BFS to mark all connected 'O's as safe
    int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for(int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if(nx >= 0 && ny >= 0 && nx < n && ny < m && board[nx][ny] == 'O') {
                board[nx][ny] = 'S';  // Mark as safe
                q.push({nx, ny});
            }
        }
    }
    
    // Phase 2: Capture surrounded, restore safe
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 'O') board[i][j] = 'X';      // Surrounded → Capture
            else if(board[i][j] == 'S') board[i][j] = 'O'; // Safe → Restore
        }
    }
}
```

🔹 **Pattern Tag:** #DFS #BFS #Matrix #ReverseThinking #TwoPhase #BorderTraversal

---

### 🔸 Logic Summary:

- **Phase 1:** Find all 'O' cells connected to borders → Mark as 'S' (safe)
- **Phase 2:** Remaining 'O' cells are surrounded → Convert to 'X', restore 'S' to 'O'

---

### 🔸 Key Insight - Reverse Thinking:

- **❌ Hard:** Directly find surrounded regions (complex boundary checks)
- **✅ Easy:** Find NON-surrounded regions first, then everything else is surrounded

---

### 🔸 Why Temporary Marker 'S'?

- Need to distinguish between:
    - **Original 'O' that are safe** (keep as 'O')
    - **Original 'O' that are surrounded** (change to 'X')
- Without 'S', we lose this distinction during traversal

---

### 🔸 Border Strategy:

```cpp
// Check if cell is on border
(i == 0 || i == n-1 || j == 0 || j == m-1)
```

- Start DFS/BFS only from border 'O' cells
- These are guaranteed to be non-surrounded

---

### 🔸 BFS vs DFS:

- **BFS:** Level-by-level expansion, uses queue, iterative
- **DFS:** Depth-first exploration, uses recursion/stack
- **Both work equally well** for this problem - same time/space complexity O(m×n)

---

### 🔸 Final Insight:

- **Border-connected = Safe** (cannot be surrounded)
- **Not border-connected = Surrounded** (can be captured)
- Think of it as **"flood fill from borders"** to identify escape routes

---



# SOLUTION :

```CPP
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        
        // Step 1: Mark all 'O's connected to border as safe (change to 'S')
        // Check all border cells
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // If it's on the border and is 'O', mark it and all connected 'O's as safe
                if((i == 0 || i == n-1 || j == 0 || j == m-1) && board[i][j] == 'O') {
                    dfs(board, i, j, n, m);
                }
            }
        }
        
        // Step 2: Convert all remaining 'O's to 'X' (these are surrounded)
        // Convert all 'S' back to 'O' (these are safe)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(board[i][j] == 'O') {
                    board[i][j] = 'X';  // Surrounded, capture it
                } else if(board[i][j] == 'S') {
                    board[i][j] = 'O';  // Safe, restore it
                }
            }
        }
    }
    
private:
    void dfs(vector<vector<char>>& board, int x, int y, int n, int m) {
        // Mark current cell as safe
        board[x][y] = 'S';
        
        // Directions: up, down, left, right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        // Check all 4 directions
        for(int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            // If valid cell and is 'O', recursively mark it as safe
            if(nx >= 0 && ny >= 0 && nx < n && ny < m && board[nx][ny] == 'O') {
                dfs(board, nx, ny, n, m);
            }
        }
    }
};

// Alternative BFS approach
class SolutionBFS {
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        
        queue<pair<int,int>> q;
        
        // Add all border 'O' cells to queue and mark them as safe
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if((i == 0 || i == n-1 || j == 0 || j == m-1) && board[i][j] == 'O') {
                    board[i][j] = 'S';
                    q.push({i, j});
                }
            }
        }
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        // BFS to mark all connected 'O's as safe
        while(!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for(int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                
                if(nx >= 0 && ny >= 0 && nx < n && ny < m && board[nx][ny] == 'O') {
                    board[nx][ny] = 'S';
                    q.push({nx, ny});
                }
            }
        }
        
        // Final conversion
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(board[i][j] == 'O') {
                    board[i][j] = 'X';  // Capture surrounded
                } else if(board[i][j] == 'S') {
                    board[i][j] = 'O';  // Restore safe
                }
            }
        }
    }
};
```