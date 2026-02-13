
## 🔹 Problem Statement (LeetCode Style)

You are given an `n x n` integer matrix `grid` where:

- Each value `grid[i][j]` represents the elevation at that cell.
    
- You start at the top-left cell `(0,0)`.
    
- You want to reach the bottom-right cell `(n-1,n-1)`.
    

At time `t`, the water level rises to height `t`.

You can move to adjacent cells (up, down, left, right) **only if** both cells have elevation ≤ `t`.

Return the minimum time `t` such that you can reach the bottom-right cell.

---

## 🔹 Key Observations

### 1️⃣ Core Variable (What are we optimizing?)

We are minimizing:

```
t = time
```

Equivalent meaning:

> Minimize the maximum elevation encountered along the path.

---

### 2️⃣ Answer Space

Minimum possible time:

```
max(grid[0][0], grid[n-1][n-1])
```

Maximum possible time:

```
n*n - 1
```

Safe search space:

```
[0, n*n]
```

---

### 3️⃣ Monotonic Property

If you can reach destination at time `t`,  
then you can also reach it at any time `> t`.

Because:  
Water level only increases → more cells become accessible.

So decision function looks like:

```
false false false true true true
```

We search for **first true**.

---

## 🔹 Decision Function

For a given `t`:

> Can we reach `(n-1, n-1)` using only cells with value ≤ t?

This is a BFS problem.

---

## 🔹 Algorithm

1. Binary search on time `t`
    
2. For each mid:
    
    - Run BFS
        
    - Only move if:
        
        ```
        grid[nx][ny] <= mid
        ```
        
    - Use visited to avoid cycles
        
3. If reachable → shrink right
    
4. Else → move left
    

---

# 💻 C++ Code (Binary Search + BFS)

```cpp
class Solution {
public:
    
    bool isPossible(vector<vector<int>>& grid, int t) {
        int n = grid.size();
        
        if (grid[0][0] > t) return false;
        
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        queue<pair<int,int>> q;
        
        q.push({0,0});
        visited[0][0] = true;
        
        int dx[4] = {1,-1,0,0};
        int dy[4] = {0,0,1,-1};
        
        while(!q.empty()) {
            auto [x,y] = q.front();
            q.pop();
            
            if (x == n-1 && y == n-1)
                return true;
            
            for(int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if(nx >= 0 && ny >= 0 && nx < n && ny < n &&
                   !visited[nx][ny] &&
                   grid[nx][ny] <= t) {
                    
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        
        return false;
    }
    
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        int low = 0;
        int high = n*n;
        
        while(low < high) {
            int mid = low + (high - low)/2;
            
            if(isPossible(grid, mid))
                high = mid;
            else
                low = mid + 1;
        }
        
        return low;
    }
};
```

---

# ⏱ Time Complexity

Binary Search:

```
O(log(n²)) = O(log n)
```

Each BFS:

```
O(n²)
```

Total:

```
O(n² log n)
```

---

# 🧠 Space Complexity

```
O(n²) for visited
```

---

# 🔥 Why This Works

We converted:

> Minimize maximum elevation along path

into:

> Search smallest time such that connectivity exists.

This is classic:

```
Binary Search + Graph Reachability
```


---

# MINI- NOTE :

🔹 **Problem**  
Given an `n x n` grid of elevations, you start at `(0,0)` and want to reach `(n-1,n-1)`.  
At time `t`, water level is `t`.  
You can move only to cells with elevation ≤ `t`.  
Return minimum `t` required to reach destination.

---

🔹 **Graph Type**  
Grid Graph (4-directional)  
Binary Search on Answer + BFS (Node Constraint)

---

🔹 **Technique**  
Binary Search on time `t`  
For each `t`, check reachability using BFS.

---

🔹 **Core Template**

Binary Search:

```
low = 0
high = n*n
while (low < high):
    mid
    if isPossible(mid):
        high = mid
    else:
        low = mid + 1
return low
```

isPossible(t):

- If `grid[0][0] > t` → return false
    
- BFS from `(0,0)`
    
- Move only if:
    
    ```
    grid[nx][ny] <= t
    ```
    
- If reach `(n-1,n-1)` → true
    

---

🔹 **Pattern Tag**  
#BinarySearchOnAnswer  
#GraphConnectivity  
#SmallestTrue  
#NodeConstraint

---

🔸 **Logic Summary**  
At time `t`, only cells with elevation ≤ `t` are accessible.  
If reachable for `t`, then reachable for any `t' > t`.  
Monotonic:

```
false false false true true true
```

We search smallest true.

---

🔸 **Trick**

- Must use `visited` in BFS (grid has cycles)
    
- Do NOT compute path effort
    
- Do NOT track max manually inside BFS
    
- Binary Search controls allowed nodes
    

---

🔸 **Why Other Approach Won’t Work**

- Plain BFS → optimizes steps, not elevation
    
- Greedy local choice → fails
    
- Enumerating paths → exponential
    

---

🔸 **Boundary**  
Smallest `t` such that destination becomes reachable.

---

🔸 **Final Insight**  
This problem is actually:

> Minimize maximum elevation along the path.

Equivalent solutions:

- Binary Search + BFS
    
- Dijkstra (minimax variant)
    
- MST (bottleneck path property)
    

---

Phase 4 documentation complete.
