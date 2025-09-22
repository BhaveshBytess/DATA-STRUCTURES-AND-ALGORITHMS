
# 947. Most Stones Removed with Same Row or Column

You are given an array `stones` where `stones[i] = [xi, yi]` represents the location of the `ith` stone on a 2D plane.

A stone can be removed if it shares either the **same row or the same column** as another stone that has not been removed.

Return _the largest possible number of stones that can be removed_.

---

#### Example 1:

```
Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [0,1] because it shares row 0 with [0,0].
2. Remove stone [1,0] because it shares column 0 with [0,0].
3. Remove stone [2,1] because it shares column 1 with [0,1].
4. Remove stone [1,2] because it shares row 1 with [1,0].
5. Remove stone [2,2] because it shares row 2 with [2,1].
```

#### Example 2:

```
Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
```

#### Example 3:

```
Input: stones = [[0,0]]
Output: 0
```

---

#### Constraints:

- `1 <= stones.length <= 1000`
    
- `0 <= xi, yi <= 10^4`
    

---

# CODE : 

The key insight is:

- Stones in the same connected component (connected by sharing row/column) can all be removed except one.
    
- So the answer = `total stones - number of connected components`.
    

---

### DFS Version Code (C++)

```cpp
class Solution {
public:
    void dfs(int u, vector<vector<int>>& adj, vector<int>& visited) {
        visited[u] = 1;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, adj, visited);
            }
        }
    }
    
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<vector<int>> adj(n);
        
        // Build graph: connect stones in same row or column
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        
        vector<int> visited(n, 0);
        int components = 0;
        
        // Count connected components
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited);
                components++;
            }
        }
        
        return n - components; // remove all but one per component
    }
};
```

---

✅ **Time Complexity**: `O(n^2)` (because we check every pair to build edges).  
✅ **Space Complexity**: `O(n^2)` in worst case for adjacency list.

---

The DSU trick here is:

- We treat **rows** and **columns** as nodes in DSU.
    
- If a stone is at `(x, y)`, we union `x` and `y + 10001` (shift column index to avoid collision with row index).
    
- Then, the number of connected components is just the number of unique roots used.
    
- Answer = `total stones - number of connected components`.
    

---

### DSU Version Code (C++)

```cpp
class Solution {
public:
    unordered_map<int, int> parent;

    int find(int x) {
        if (parent.find(x) == parent.end()) parent[x] = x;
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }

    int removeStones(vector<vector<int>>& stones) {
        for (auto &stone : stones) {
            int row = stone[0];
            int col = stone[1] + 10001; // shift column index
            unite(row, col);
        }

        unordered_set<int> uniqueRoots;
        for (auto &stone : stones) {
            uniqueRoots.insert(find(stone[0]));
        }

        return stones.size() - uniqueRoots.size();
    }
};
```

---

✅ **Time Complexity**: Almost `O(n * α(n))` (α = inverse Ackermann, very small).  
✅ **Space Complexity**: `O(n)` (for DSU parent map).

---
