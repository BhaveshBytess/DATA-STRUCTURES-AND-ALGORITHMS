Absolutely, let’s tackle **LeetCode 733. Flood Fill** in your preferred grind-style format:


---
## 🌊 Flood Fill (LeetCode 733)

### 🔍 Problem Statement

You are given a 2D integer array `image`, representing the pixel values of an image, and three integers `sr`, `sc`, and `newColor`.

Perform a **"flood fill"** on the image starting from the pixel `image[sr][sc]`.

- A flood fill changes the starting pixel's color and **all connected pixels** (via direct 4-directional adjacency) that have the **same original color** to `newColor`.
    
- You may assume all values are integers in the range [0, 65535].
    

Return the final image after performing the flood fill.

---

### 📌 Example 1:

```
Input:
image = [[1,1,0,0],[1,1,0,0],[0,0,1,1]]
sr = 0, sc = 0, newColor = 2

Output:
[[2,2,0,0],[2,2,0,0],[0,0,1,1]]
```

Here, you flood fill starting at `(0,0)`—color `1`—so all connected `1`s change to `2`.

---

### 📌 Example 2:

```
Input:
image = [[0,0,0],[0,0,0]]
sr = 0, sc = 0, newColor = 0

Output:
[[0,0,0],[0,0,0]]
```

Since `newColor` is the same as the original, nothing changes.

---

### ✅ Objective

Write the function:

```cpp
vector<vector<int>> floodFill(
    vector<vector<int>>& image,
    int sr,
    int sc,
    int newColor
);
```

Implement this using your DFS or BFS skills — **no hints or full solution until you’ve thought it through**.

---

## 💡 Key Points to Think:

- How will you **avoid infinite loops** when changing colors in cycles?
    
- When should you **return early**, e.g. if the `newColor` is the same as the original color?
    
- How will you navigate the **4-directional neighbors** in the grid?
    

---

### 🔄 Your Turn:

Work through your strategy:

- If going DFS → how will you mark visited or ensure you don’t revisit?
    
- If BFS → how will you queue neighbors?
    
- How will you change the color **only for connected pixels of the same original color**?
    

Once you’re ready or if you hit a snag, just say _“nudge gently”_ and I’ll guide you forward.



----


![[Pasted image 20250727164149.png]]


Yes Bhavesh — you **absolutely nailed it!** ✅

Your approach is **solid and correct** — you're doing a standard **DFS-based flood fill**, and from what I see:

### 🔍 What You Did Right:

- ✅ You’ve got your `dfs()` function to handle coloring.
    
- ✅ You're checking bounds properly (`row >= 0`, `row < image.size()`, etc.).
    
- ✅ You’re comparing the original color (`org`) before replacing with `newColor`.
    
- ✅ You’re handling all **4 directions**: up, down, left, right.
    
- ✅ You’ve added the early return case if the `newColor == org` — excellent optimization!
    
- ✅ You’re using a loop to traverse directions — clean and compact style.
    

---

### 💯 Verdict:

You have indeed solved the **Flood Fill** problem properly and in a **LeetCode-accepted format**.

---

### ✍ Minor Improvements (optional):

1. Use a direction array to simplify your direction logic:
    
    ```cpp
    vector<pair<int, int>> directions = {{0,1},{1,0},{-1,0},{0,-1}};
    ```
    
2. Clean naming (optional):  
    Instead of `org`, maybe name it `originalColor` just for clarity. But that’s style preference.
    

---

Would you like me to now convert this into a **clean final version of the code** ready for submission — just as a checkpoint before we move to the next question (e.g., BFS version or 01 Matrix)?

---












# MINI-NOTE

Here’s your **Mini Note** for **Flood Fill (Leetcode 733)** — a foundational grid graph problem:

---

📘 **MINI NOTE**

🔹 **Problem**: Flood Fill (Leetcode 733)  
🔹 **Graph Type**: Grid Graph (2D Matrix)  
🔹 **Technique**: DFS or BFS  
🔹 **Core Template**: Standard 4-directional DFS/BFS on grid  
🔹 **Pattern Tag**: #MatrixGraph #DFS #BFS #ImageFill

---

🔸 **Logic Summary**:

- Starting from a given cell, **recolor** all connected cells with the same **initial color** into a **new color**.
    
- Recursively/Iteratively move in **4 directions** (up, down, left, right).
    
- Only continue if the neighboring cell has the **same original color** and hasn't been visited or changed yet.
    

---

🔸 **Trick**:

- Handle the **early return** if `newColor == originalColor` → avoids infinite recursion.
    
- Track bounds (`i >= 0 && i < n && j >= 0 && j < m`) to avoid overflow.
    

---

🔸 **Why BFS & DFS both work**:

- Both visit all reachable same-colored pixels.
    
- DFS is often **shorter in code**, BFS may be **safer against stack overflow** for large images.
    

---

🔸 **Why Other Approaches Don’t Work**:

- You can’t brute-force recolor everything — it must be **connected and same color**.
    
- Using a visited array is **optional**, because you can mutate the grid directly.
    

---

🔸 **Final Insight**:  
This is the **foundation** of matrix-based graph traversal — sets the base for 01 Matrix, Rotten Oranges, Walls & Gates, etc.

---

Let me know if you'd like the **C++ DFS + BFS template** for Flood Fill right alongside this.



---











Here’s your **clean, submission-ready Flood Fill DFS solution** in C++ (LeetCode style):

```cpp
class Solution {
public:
    void dfs(int row, int col, vector<vector<int>>& image, int originalColor, int newColor) {
        int m = image.size(), n = image[0].size();

        // Boundary + visited + color check
        if (row < 0 || row >= m || col < 0 || col >= n || image[row][col] != originalColor)
            return;

        image[row][col] = newColor;

        // 4-directional movement
        dfs(row + 1, col, image, originalColor, newColor);
        dfs(row - 1, col, image, originalColor, newColor);
        dfs(row, col + 1, image, originalColor, newColor);
        dfs(row, col - 1, image, originalColor, newColor);
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int originalColor = image[sr][sc];
        if (originalColor != newColor) {
            dfs(sr, sc, image, originalColor, newColor);
        }
        return image;
    }
};
```

---

### ✅ Time & Space Complexity:

- **Time:** O(m × n) — in the worst case, we may visit every pixel.
    
- **Space:** O(m × n) recursion stack in worst case (if all pixels are same color).
    

---

Let me know if you’d like to do the **BFS version next**, or jump straight to `01 Matrix` or `Rotten Oranges`.


---

Perfect — let's now do the **BFS version of Flood Fill**. Same logic as DFS, just implemented **iteratively** using a **queue** instead of recursion.

---

## 🔁 **Flood Fill — BFS Version**

Leetcode-style C++ code:

```cpp
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int oldColor = image[sr][sc];
        if (oldColor == newColor) return image;  // No change needed

        int rows = image.size();
        int cols = image[0].size();

        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = newColor;

        // Directions: up, down, left, right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                // Check bounds and color match
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && image[nx][ny] == oldColor) {
                    image[nx][ny] = newColor;
                    q.push({nx, ny});
                }
            }
        }

        return image;
    }
};
```

---

## 📌 Key Points:

- **Base condition**: If the color you're trying to flood with is the same as the starting pixel → return immediately.
    
- BFS spreads level by level — hence, we use a queue (`std::queue`) to keep track of which pixels to color next.
    
- We mark the cell as colored _as soon as we push it to the queue_ — so we don’t process it again.
    

---

Let me know if you'd like a **visual trace** of this BFS working step-by-step, or if you're ready to move to the **next BFS-based problem** like **Rotting Oranges**.

[^1]: Here’s your **Mini Note** for **Flood Fill (Leetcode 733)** — a foundational grid graph problem:
	
	---
	
	📘 **MINI NOTE**
	
	🔹 **Problem**: Flood Fill (Leetcode 733)  
	🔹 **Graph Type**: Grid Graph (2D Matrix)  
	🔹 **Technique**: DFS or BFS  
	🔹 **Core Template**: Standard 4-directional DFS/BFS on grid  
	🔹 **Pattern Tag**: #MatrixGraph #DFS #BFS #ImageFill
	
	---
	
	🔸 **Logic Summary**:
	
	- Starting from a given cell, **recolor** all connected cells with the same **initial color** into a **new color**.
	    
	- Recursively/Iteratively move in **4 directions** (up, down, left, right).
	    
	- Only continue if the neighboring cell has the **same original color** and hasn't been visited or changed yet.
	    
	
	---
	
	🔸 **Trick**:
	
	- Handle the **early return** if `newColor == originalColor` → avoids infinite recursion.
	    
	- Track bounds (`i >= 0 && i < n && j >= 0 && j < m`) to avoid overflow.
	    
	
	---
	
	🔸 **Why BFS & DFS both work**:
	
	- Both visit all reachable same-colored pixels.
	    
	- DFS is often **shorter in code**, BFS may be **safer against stack overflow** for large images.
	    
	
	---
	
	🔸 **Why Other Approaches Don’t Work**:
	
	- You can’t brute-force recolor everything — it must be **connected and same color**.
	    
	- Using a visited array is **optional**, because you can mutate the grid directly.
	    
	
	---
	
	🔸 **Final Insight**:  
	This is the **foundation** of matrix-based graph traversal — sets the base for 01 Matrix, Rotten Oranges, Walls & Gates, etc.
	
	---
	
	Let me know if you'd like the **C++ DFS + BFS template** for Flood Fill right alongside this.
