Here’s the **Clone Graph** problem in LeetCode’s original format: #CLONE_GRAPH

---

**133. Clone Graph**  
**Medium**

**Problem Statement:**  
Given a reference of a node in a **connected** undirected graph. Return a **deep copy** (clone) of the graph.

Each node in the graph contains a value (`int`) and a list (`List[Node]`) of its neighbors.

```cpp
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
```

**Test case format:**  
For simplicity, each node's value is the same as the node's index (1-indexed). The graph is represented in the test case using an adjacency list.

**An adjacency list** is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

The given node will always be the first node in the adjacency list.

---

**Example 1:**

**Input:** `adjList = [[2,4],[1,3],[2,4],[1,3]]`  
**Output:** `[[2,4],[1,3],[2,4],[1,3]]`  
**Explanation:**  
Graph:

```
    1 -- 2
    |    |
    4 -- 3
```

---

**Example 2:**

**Input:** `adjList = [[]]`  
**Output:** `[[]]`  
**Explanation:**  
Graph has a single node with no neighbors.

---

**Example 3:**

**Input:** `adjList = []`  
**Output:** `[]`  
**Explanation:**  
Graph is empty.

---

**Constraints:**

- The number of nodes in the graph is in the range `[0, 100]`.
    
- `1 <= Node.val <= 100`
    
- Node values are unique.
    
- There are no repeated edges and no self-loops in the graph.
    
- The Graph is connected, and all nodes can be visited starting from the given node.
    

---

# MINI-NOTE :


Here’s your **mini note** for the **Clone Graph** problem:

---

🔹 **Problem**  
You are given a reference to a node in a connected undirected graph. Each node contains a value (`val`) and a list of neighbors. Return a **deep copy** (clone) of the graph.

🔹 **Graph Type**  
Undirected graph, connected, may contain cycles.

🔹 **Technique**  
Graph traversal using **BFS** or **DFS** + HashMap for visited mapping.

🔹 **Core Template**

```cpp
unordered_map<Node*, Node*> mp;
queue<Node*> q;
q.push(start);
mp[start] = new Node(start->val);

while (!q.empty()) {
    Node* cur = q.front(); q.pop();
    for (auto nei : cur->neighbors) {
        if (!mp.count(nei)) {
            mp[nei] = new Node(nei->val);
            q.push(nei);
        }
        mp[cur]->neighbors.push_back(mp[nei]);
    }
}
return mp[start];
```

🔹 **Pattern Tag**  
Graph cloning, BFS, HashMap for visited mapping, Graph traversal.

🔸 **Logic Summary**  
We maintain a mapping from **original node → cloned node** to avoid duplication and handle cycles. BFS ensures level-by-level cloning, and neighbors are linked as we go.

🔸 **Trick**  
Without the `unordered_map`, you’ll create infinite loops on cycles. The map also ensures each node is cloned exactly once.

🔸 **Why DFS-only approach won’t work for large graphs**  
DFS works fine logically, but can cause **stack overflow** in deep graphs. BFS avoids recursion depth limits.

🔸 **Final Insight**  
This is essentially the BFS version of deep-copying an object graph — the visited map is the backbone.


---



## DFS Solution (Optimal)

```cpp
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    unordered_map<Node*, Node*> mp; // maps original -> clone
    
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        if (mp.find(node) != mp.end()) return mp[node]; // already cloned
        
        Node* clone = new Node(node->val);
        mp[node] = clone;
        
        for (auto neighbor : node->neighbors) {
            clone->neighbors.push_back(cloneGraph(neighbor));
        }
        return clone;
    }
};
```

---

## BFS Solution (Optimal)

```cpp
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        
        unordered_map<Node*, Node*> mp; // original -> clone
        queue<Node*> q;
        
        // create first clone
        mp[node] = new Node(node->val);
        q.push(node);
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            for (auto neighbor : curr->neighbors) {
                if (mp.find(neighbor) == mp.end()) {
                    mp[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                mp[curr]->neighbors.push_back(mp[neighbor]);
            }
        }
        
        return mp[node];
    }
};
```

---

✅ **Complexity**

- **Time:** O(N + E) — visit each node & edge once
    
- **Space:** O(N) — map + recursion/queue
    

---

If you want, I can also make a **short "mini note" version** for Clone Graph like the BFS/graph notes format you’ve been using for revision.  
Do you want me to make that for this problem next?