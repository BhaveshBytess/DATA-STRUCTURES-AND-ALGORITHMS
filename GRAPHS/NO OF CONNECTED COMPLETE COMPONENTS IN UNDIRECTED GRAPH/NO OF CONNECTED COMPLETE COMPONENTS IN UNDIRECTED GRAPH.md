Sure! Here's the **LeetCode-style question format** for the problem you just solved:

---

### **2685. Count the Number of Complete Components**

**Medium**

You are given an integer `n`. There is an **undirected graph** with `n` vertices, numbered from `0` to `n - 1`. You are also given a **2D integer array** `edges` where `edges[i] = [ai, bi]` denotes that there exists an **undirected edge** connecting vertices `ai` and `bi`.

Return _the number of **complete** connected components of the graph._

A **connected component** is a subgraph in which there exists a path between any two vertices, and no vertex in the subgraph shares an edge with a vertex outside of the subgraph.

A connected component is said to be **complete** if there exists an edge between every pair of its vertices.

---

### **Example 1:**

```
Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
Output: 3
Explanation:
There are 3 connected components:
1. [0,1,2] is a complete component because every pair is connected.
2. [3,4] is a complete component because 3 and 4 are directly connected.
3. [5] is a complete component (a single node is trivially complete).
```

### **Example 2:**

```
Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[4,5]]
Output: 1
Explanation:
Only the component [0,1,2] is complete.
The component [3,4,5] is not complete because there's no edge between 3 and 5.
The node [5] is not isolated in this case.
```

---

### **Constraints:**

- `1 <= n <= 50`
    
- `0 <= edges.length <= n * (n - 1) / 2`
    
- `edges[i].length == 2`
    
- `0 <= ai, bi < n`
    
- `ai != bi`
    
- There are no repeated edges.
    

---

Let me know if you want this saved inside a mindmap or notes doc.


---


# MINI NOTE

Here's your **mini note** for the problem **"2685. Count the Number of Complete Components"** using your standardized template:

---

📘 **MINI NOTE**

🔹 **Problem**: Count the Number of Complete Components (Leetcode 2685)  
🔹 **Graph Type**: Undirected Graph (Adjacency List)  
🔹 **Technique**: DFS Traversal + Degree Counting  
🔹 **Core Template**: DFS with tracking of node count & total edge contribution  
🔹 **Pattern Tag**: #DFS #ComponentCheck #EdgeCountTrick

🔸 **Logic Summary**:

- For each connected component, perform DFS.
    
- Count:
    
    - `nodes`: total nodes in this component
        
    - `edges`: sum of all adjacency list sizes in this component (each edge counted twice)
        
- A component is _complete_ if:  
    `edges / 2 == nodes × (nodes - 1) / 2`  
    i.e., if every pair of nodes is connected.
    

🔸 **Trick**:

- Instead of storing all pairs, just count total degrees (adj[i].size) — a mathematical shortcut.
    
- Edge count is doubled in adjacency list, so divide by 2 before final check.
    

🔸 **Why BFS/Union Find not preferred**:

- DFS gives more control to collect per-component stats (nodes and edges in one recursive pass).
    
- Union Find would need additional structures to store sizes and edge counts separately.
    

🔸 **Final Insight**:  
Use this strategy for problems that check if a graph/component is a **clique or fully connected**. The formula `n(n-1)/2` is a powerful validator for "completeness" in undirected components.

---

Want me to log the next one too when you're done?


---



# SOLUTION : 

```c++
class Solution {

public:

    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited,int& edges,int& nodes){

        visited[node] = true;

        nodes++;

        edges += adj[node].size();

        for(int neighbor : adj[node]){

            if(!visited[neighbor]){

                dfs(neighbor,adj,visited,edges,nodes);

            }

        }

    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        vector<vector<int>> adj(n);

        for(auto edge : edges){

            int u = edge[0];

            int v = edge[1];

            adj[u].push_back(v);

            adj[v].push_back(u);

        }

  

        vector<bool> visited(n,false);

        int count = 0;

        for(int i=0;i<n;i++){

            if(!visited[i]){

                int edges = 0;

                int nodes = 0;

  

                dfs(i,adj,visited,edges,nodes);

  

                edges = edges/2;

                if(edges == nodes*(nodes-1)/2){

                    count++;

                }

                else{

                    continue;

                }

            }

        }

  

        return count;

    }

};

```

