Great call — let’s tackle the classic follow-up: #COURSE_SCHEDULE_II

---

## 📘 LeetCode Style: Course Schedule II (Topological Ordering)

### 🔍 Problem Statement

You are given:

- An integer `numCourses`, representing courses labeled from `0` to `numCourses - 1`.
    
- A list `prerequisites`, where each element is a pair `[a, b]`, meaning **to take course `a`, you must first complete course `b`**.
    

Return **any valid order** in which you can complete all courses. If **no valid ordering exists** (because of a cycle), return an **empty array**.

### 💻 Function Signature

```cpp
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);
```

---

### 🚀 Key Insights

- Each valid order is basically a **topological sort** of the directed graph.
    
- If a graph contains a cycle, **no such ordering exists** → return `[]`.
    

---

### 🧠 Constraints

- `1 <= numCourses <= 10^5`
    
- `0 <= prerequisites.length <= 10^5`
    
- `prerequisites[i].length == 2`
    
- `0 <= a, b < numCourses`
    
- No duplicate prerequisite pairs.
    

---

### ✅ Your Task

Use your favorite approach — **either Kahn’s Algorithm (BFS)** or **Recursive DFS (using pathVisited)** — to build a topological order, or return an empty list if a cycle is found.

---

Drop your thoughts or partial code whenever you’re ready. I’ll nudge you gently from there — no full solution until you’re satisfied with your own grind. Let’s do this!


---


Great! Let's compile the **final clean C++ code** for **Leetcode 210. Course Schedule II** using **Kahn’s Algorithm (Topological Sort with BFS)**:

---

### ✅ Problem Summary

- You're given `numCourses` and a list of `prerequisites`, where each pair `[a, b]` means **take course `b` before `a`**.
    
- Return an ordering of courses you can take to finish all courses.
    
- If it's not possible (i.e., cycle exists), return an **empty array**.
    

---

### ✅ Final C++ Code (Kahn’s Algo – BFS)

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        vector<int> indegree(numCourses, 0);
        
        // Build adjacency list and compute indegrees
        for (auto& pre : prerequisites) {
            int u = pre[1], v = pre[0];
            adj[u].push_back(v);
            indegree[v]++;
        }
        
        // Push all nodes with indegree 0 into queue
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }
        
        vector<int> topoOrder;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topoOrder.push_back(node);
            
            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }
        
        // If all courses are not included, return empty
        if (topoOrder.size() != numCourses)
            return {};
        
        return topoOrder;
    }
};
```

---

Let me know if you want the **DFS-based Topo Sort version** too, or if you’re ready for the next graph grind.


---


Here is the **full C++ code** for **Leetcode 210. Course Schedule II** using **DFS with cycle detection (Topological Sort)**:

---

### ✅ DFS + Topological Sort + Cycle Detection

```cpp
class Solution {
public:
    bool dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& pathVisited, stack<int>& st) {
        visited[node] = true;
        pathVisited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (!dfs(neighbor, adj, visited, pathVisited, st))
                    return false;
            } else if (pathVisited[neighbor]) {
                // cycle found
                return false;
            }
        }
        
        pathVisited[node] = false; // backtrack
        st.push(node); // topo sort
        return true;
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        
        for (auto& edge : prerequisites) {
            adj[edge[1]].push_back(edge[0]); // u -> v (take u before v)
        }
        
        vector<bool> visited(numCourses, false);
        vector<bool> pathVisited(numCourses, false);
        stack<int> st;
        
        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {
                if (!dfs(i, adj, visited, pathVisited, st)) {
                    return {}; // cycle detected
                }
            }
        }
        
        vector<int> topoOrder;
        while (!st.empty()) {
            topoOrder.push_back(st.top());
            st.pop();
        }
        return topoOrder;
    }
};
```

---

### 🔍 Summary:

- We detect cycles using `pathVisited` (same as in earlier questions).
    
- If a cycle is detected → return `{}`.
    
- Otherwise, push nodes in a stack (reversed post-order) and return the valid course ordering.
    

Let me know when you're ready to jump to the next question — DFS, BFS, or Topo Sort-based — your grind continues 💪