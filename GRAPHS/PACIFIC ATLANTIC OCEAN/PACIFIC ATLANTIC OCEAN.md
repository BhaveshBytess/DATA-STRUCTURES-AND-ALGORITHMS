
# **417. Pacific Atlantic Water Flow**  
## **Medium**

You are given an `m x n` integer matrix `heights` where `heights[r][c]` represents the height of a cell.

The **Pacific ocean** touches the matrix's left and top edges, and the **Atlantic ocean** touches the matrix's right and bottom edges.

Water can only flow from a cell to another cell directly north, south, east, or west (4-directionally) **if the neighboring cell's height is less than or equal to the current cell's height**.

Return _a list of grid coordinates_ where water can flow to **both** the Pacific and Atlantic oceans.

**Example 1:**

```
Input: heights = [[1,2,2,3,5],
                  [3,2,3,4,4],
                  [2,4,5,3,1],
                  [6,7,1,4,5],
                  [5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
```

**Example 2:**

```
Input: heights = [[2,1],[1,2]]
Output: [[0,0],[0,1],[1,0],[1,1]]
```

**Constraints:**

- `m == heights.length`
    
- `n == heights[r].length`
    
- `1 <= m, n <= 200`
    
- `0 <= heights[r][c] <= 10^5`
    

---

# MINI-NOTE : 

🔹 **Problem:** Pacific Atlantic Water Flow  
🔹 **Graph Type:** Grid Graph (each cell is a node, edges = 4-directional adjacency with height condition)  
🔹 **Technique:**

- **Multi-source BFS** (start from ocean borders instead of individual cells)
    
- **Intersection of reachable cells from both oceans**
    

---

🔹 **Core Template:**

```cpp
// 1. Initialize visited matrices and queues
vector<vector<int>> pacific(n, vector<int>(m, 0));
vector<vector<int>> atlantic(n, vector<int>(m, 0));
queue<pair<int,int>> qPacific, qAtlantic;

// Push Pacific borders
for (int i = 0; i < n; i++) {
    pacific[i][0] = 1;
    qPacific.push({i, 0});
}
for (int j = 0; j < m; j++) {
    pacific[0][j] = 1;
    qPacific.push({0, j});
}

// Push Atlantic borders
for (int i = 0; i < n; i++) {
    atlantic[i][m-1] = 1;
    qAtlantic.push({i, m-1});
}
for (int j = 0; j < m; j++) {
    atlantic[n-1][j] = 1;
    qAtlantic.push({n-1, j});
}

// 2. BFS function (flow condition: heights[next] >= heights[curr])
auto bfs = [&](queue<pair<int,int>> &q, vector<vector<int>> &visited) {
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
                !visited[nx][ny] && heights[nx][ny] >= heights[x][y]) {
                visited[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }
};

// 3. Run BFS for both oceans
bfs(qPacific, pacific);
bfs(qAtlantic, atlantic);

// 4. Collect intersection cells
vector<vector<int>> result;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (pacific[i][j] && atlantic[i][j])
            result.push_back({i, j});
    }
}
```

---

🔹 **Pattern Tag:** #BFS #MultiSource #GridGraph #WaterFlow

---

### 🔸 Logic Summary:

- **Start BFS from the oceans themselves** (multi-source), not from land cells.
    
- Water “flows” in reverse: from ocean borders to higher/equal cells.
    
- Any cell visited by **both BFS traversals** can flow to both oceans.
    

---

### 🔸 Trick:

- The key reversal: **Instead of starting from land and flowing downwards, start from the ocean and flow upwards (to higher/equal height cells).**
    
- This ensures each cell is processed only once per ocean → **O(m × n)**.
    

---

### 🔸 Why Multi-source BFS?

- If you start BFS/DFS from each cell individually, complexity blows up to **O((mn)²)**.
    
- By starting from the ocean edges (multi-source BFS), each cell is visited at most twice → **Optimal solution.**
    

---

### 🔸 Final Insight:

- Think of it as **two flood-fills**:
    
    - One from the **Pacific edges**
        
    - One from the **Atlantic edges**
        
- The **intersection** gives the final answer.
    
- This is a **classic multi-source BFS grid pattern** with a **reverse condition** (higher → lower allowed).
    


---


# Solution (bfs code)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();

        vector<vector<int>> pacific(n, vector<int>(m, 0));
        vector<vector<int>> atlantic(n, vector<int>(m, 0));

        queue<pair<int, int>> qPacific;
        queue<pair<int, int>> qAtlantic;

        // Step 1: Push Pacific border cells into qPacific
        for (int i = 0; i < n; i++) {
            pacific[i][0] = 1;
            qPacific.push({i, 0});
        }
        for (int j = 0; j < m; j++) {
            pacific[0][j] = 1;
            qPacific.push({0, j});
        }

        // Step 2: Push Atlantic border cells into qAtlantic
        for (int i = 0; i < n; i++) {
            atlantic[i][m - 1] = 1;
            qAtlantic.push({i, m - 1});
        }
        for (int j = 0; j < m; j++) {
            atlantic[n - 1][j] = 1;
            qAtlantic.push({n - 1, j});
        }

        // 4-directional movement
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        // BFS function
        auto bfs = [&](queue<pair<int, int>>& q, vector<vector<int>>& visited) {
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
                        !visited[nx][ny] &&
                        heights[nx][ny] >= heights[x][y]) {
                        visited[nx][ny] = 1;
                        q.push({nx, ny});
                    }
                }
            }
        };

        // Step 3: BFS for both oceans
        bfs(qPacific, pacific);
        bfs(qAtlantic, atlantic);

        // Step 4: Collect intersection cells
        vector<vector<int>> result;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }
};

```


# DFS


```cpp
using namespace std;

class Solution {
public:
    int n, m;
    vector<vector<int>> heights;
    vector<vector<int>> pacific, atlantic;

    void dfs(int i, int j, vector<vector<int>>& ocean, int prevHeight) {
        // boundary check
        if (i < 0 || j < 0 || i >= n || j >= m) return;

        // already visited or not valid height flow
        if (ocean[i][j] || heights[i][j] < prevHeight) return;

        ocean[i][j] = 1;

        // explore 4 directions
        dfs(i + 1, j, ocean, heights[i][j]);
        dfs(i - 1, j, ocean, heights[i][j]);
        dfs(i, j + 1, ocean, heights[i][j]);
        dfs(i, j - 1, ocean, heights[i][j]);
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& h) {
        heights = h;
        n = heights.size();
        m = heights[0].size();

        pacific.assign(n, vector<int>(m, 0));
        atlantic.assign(n, vector<int>(m, 0));

        // DFS from Pacific (top & left borders)
        for (int i = 0; i < n; i++) dfs(i, 0, pacific, heights[i][0]);
        for (int j = 0; j < m; j++) dfs(0, j, pacific, heights[0][j]);

        // DFS from Atlantic (bottom & right borders)
        for (int i = 0; i < n; i++) dfs(i, m - 1, atlantic, heights[i][m - 1]);
        for (int j = 0; j < m; j++) dfs(n - 1, j, atlantic, heights[n - 1][j]);

        // collect results
        vector<vector<int>> res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pacific[i][j] && atlantic[i][j])
                    res.push_back({i, j});
            }
        }
        return res;
    }
};
```

