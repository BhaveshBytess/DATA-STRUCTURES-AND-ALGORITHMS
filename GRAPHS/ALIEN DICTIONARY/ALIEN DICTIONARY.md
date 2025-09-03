
### Problem: Alien Dictionary #ALIEN_DICTIONARY 

There is a new alien language that uses the English lowercase letters, but the order of the letters is unknown to you.

You are given a list of strings `words` from the dictionary, where the words are sorted lexicographically **according to the rules of this new language**.

Derive the order of letters in this alien language. If the order is invalid (i.e., no valid ordering exists), return an empty string. If there are multiple valid answers, return **any** of them.

---

### 🔹 Example 1:

**Input:**

```
words = ["wrt","wrf","er","ett","rftt"]
```

**Output:**

```
"wertf"
```

---

### 🔹 Example 2:

**Input:**

```
words = ["z","x"]
```

**Output:**

```
"zx"
```

---

### 🔹 Example 3:

**Input:**

```
words = ["z","x","z"]
```

**Output:**

```
""
```

**Explanation:**  
The sequence is invalid because `z` must come before `x` and `x` must come before `z`.

---

### 🔹 Constraints:

- `1 <= words.length <= 100`
    
- `1 <= words[i].length <= 100`
    
- `words[i]` consists of only lowercase English letters
    

---

# MINI-NOTE :









---


# SOLUTION (BFS)

Got it 👍 Let’s lock in the **final BFS (Kahn’s Algorithm) version** for Alien Dictionary.  
This version:

- Builds graph from first-differing characters.
    
- Uses **in-degree array** + queue for BFS topo sort.
    
- Detects invalid cases (prefix issue or cycle).
    

---

##  C++ Code (BFS Topological Sort)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        // Step 1: Initialize graph
        unordered_map<char, unordered_set<char>> adj; // adjacency list
        unordered_map<char, int> indegree;            // in-degree count

        // Add all unique chars to indegree map
        for (auto& word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }

        // Step 2: Build graph from adjacent word comparisons
        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i];
            string w2 = words[i + 1];
            int len = min(w1.size(), w2.size());
            bool found = false;

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    if (!adj[w1[j]].count(w2[j])) { 
                        adj[w1[j]].insert(w2[j]);
                        indegree[w2[j]]++;
                    }
                    found = true;
                    break; // Only first difference matters
                }
            }

            // Invalid case: prefix problem
            if (!found && w1.size() > w2.size()) {
                return "";
            }
        }

        // Step 3: BFS (Kahn's algorithm)
        queue<char> q;
        for (auto& [c, deg] : indegree) {
            if (deg == 0) q.push(c);
        }

        string result;
        while (!q.empty()) {
            char u = q.front();
            q.pop();
            result.push_back(u);

            for (char v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Step 4: Check if valid topo order exists
        if (result.size() < indegree.size()) {
            return ""; // cycle detected
        }

        return result;
    }
};
```

---

### ⚡ Key Points in This BFS Solution

1. **Indegree tracking** ensures we pick nodes with no remaining prerequisites.
    
2. **Queue** processes nodes level by level.
    
3. **Cycle detection** = if result has fewer characters than total unique chars.
    
4. Handles **prefix invalid case** explicitly (`["abc","ab"]` → return `""`).
    



---

# SOLUTION(DFS)
## BFS Version (Kahn’s Algorithm) — we already did

➡️ Uses **in-degree + queue**.

---

## DFS Version (Recursive Topo Sort with Cycle Detection)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        // Step 1: Build graph
        unordered_map<char, unordered_set<char>> adj;
        unordered_map<char, int> visited; 
        // visited states: 0 = unvisited, 1 = visiting, 2 = visited

        for (auto& w : words) {
            for (char c : w) visited[c] = 0; // register all chars
        }

        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i], w2 = words[i + 1];
            int len = min(w1.size(), w2.size());
            bool found = false;

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    adj[w1[j]].insert(w2[j]);
                    found = true;
                    break;
                }
            }

            // invalid case: prefix
            if (!found && w1.size() > w2.size()) return "";
        }

        // Step 2: DFS topo sort
        string result;
        for (auto& [c, _] : visited) {
            if (visited[c] == 0) {
                if (!dfs(c, adj, visited, result)) return ""; // cycle detected
            }
        }

        reverse(result.begin(), result.end());
        return result;
    }

private:
    bool dfs(char c, unordered_map<char, unordered_set<char>>& adj,
             unordered_map<char, int>& visited, string& result) {
        if (visited[c] == 1) return false; // cycle
        if (visited[c] == 2) return true;  // already done

        visited[c] = 1; // visiting
        for (char nei : adj[c]) {
            if (!dfs(nei, adj, visited, result)) return false;
        }

        visited[c] = 2; // done
        result.push_back(c);
        return true;
    }
};
```

---

## ⚖️ BFS vs DFS Comparison

|Feature|BFS (Kahn’s)|DFS (Topo Sort)|
|---|---|---|
|Cycle Detection|By checking if all nodes processed|By detecting back edges (`visiting → visiting`)|
|Order Production|Queue, layer by layer|Recursion + reverse result|
|Implementation|Slightly longer (indegree + queue mgmt)|Recursive, compact but requires careful visited states|
|Performance|`O(V + E)`|`O(V + E)` (same)|
|Intuition|Good if you like _levels_ (like courses with no prereqs first)|Good if you like _DFS exploration_ (push when done)|

---

👉 **In interviews:**

- If you like clean recursion → DFS is shorter.
    
- If interviewer asks for “iterative thinking” → BFS/Kahn’s is often preferred.
    

---

# DRY-RUN (BFS) : 

## Graph We Built

From words `["wrt","wrf","er","ett","rftt"]`, we had edges:

```
t → f
w → e
r → t
e → r
```

Graph looks like:

```
w → e → r → t → f
```

---

## Step 1: Build Indegree

Indegree = number of incoming edges for each node.

- `w`: indegree 0
    
- `e`: indegree 1 (from `w`)
    
- `r`: indegree 1 (from `e`)
    
- `t`: indegree 1 (from `r`)
    
- `f`: indegree 1 (from `t`)
    

So:

```
indegree = {w:0, e:1, r:1, t:1, f:1}
```

---

## Step 2: Initialize Queue

Start with nodes having **indegree = 0**.  
→ Queue = `[w]`

---

## Step 3: Process Queue (Kahn’s Algorithm)

1. Pop `w`
    
    - Append to result → `order = "w"`
        
    - Decrease indegree of `e` → indegree(e)=0
        
    - Push `e` into queue → Queue = `[e]`
        
2. Pop `e`
    
    - Append → `order = "we"`
        
    - Decrease indegree of `r` → indegree(r)=0
        
    - Push `r` → Queue = `[r]`
        
3. Pop `r`
    
    - Append → `order = "wer"`
        
    - Decrease indegree of `t` → indegree(t)=0
        
    - Push `t` → Queue = `[t]`
        
4. Pop `t`
    
    - Append → `order = "wert"`
        
    - Decrease indegree of `f` → indegree(f)=0
        
    - Push `f` → Queue = `[f]`
        
5. Pop `f`
    
    - Append → `order = "wertf"`
        

Queue is empty 

---

## Step 4: Check Validity

- Processed all 5 letters.
    
- No cycles detected.
    

 Final Alien Alphabet = **"wertf"**


---

# DRY-RUN (DFS)


`words = ["wrt","wrf","er","ett","rftt"]`

---

# 1) Build the graph from first-difference rules

Compare adjacent pairs:

- `"wrt"` vs `"wrf"` → first diff: `t` vs `f` ⇒ edge **t → f**
    
- `"wrf"` vs `"er"` → first diff: `w` vs `e` ⇒ edge **w → e**
    
- `"er"` vs `"ett"` → first diff: `r` vs `t` ⇒ edge **r → t**
    
- `"ett"` vs `"rftt"`→ first diff: `e` vs `r` ⇒ edge **e → r**
    

So adjacency:

```
w → {e}
e → {r}
r → {t}
t → {f}
f → {}
```

All characters present: `{w, e, r, t, f}`

(We also checked the prefix rule; none of these pairs are invalid like `"abc"` before `"ab"`.)

---

# 2) DFS topo sort setup

We keep `visited[c]` with states:

- `0 = unvisited`
    
- `1 = visiting` (in recursion stack)
    
- `2 = done` (fully processed)
    

We’ll also append to `result` **after** finishing a node (postorder). At the end, we **reverse** `result`.

Initial:

```
visited: w=0, e=0, r=0, t=0, f=0
result: ""
```

For iteration order (maps are unordered), assume we start at `w` (any unvisited start works; final order remains valid).

---

# 3) Detailed DFS trace (call stack view)

**Start loop:** `w` is unvisited ⇒ call `dfs(w)`.

### dfs(w)

- `visited[w] = 1` (visiting)
    
- Neighbors of `w`: `{e}` → `e` is 0 ⇒ `dfs(e)`
    
    ### dfs(e)
    
    - `visited[e] = 1`
        
    - Neighbors of `e`: `{r}` → `r` is 0 ⇒ `dfs(r)`
        
        ### dfs(r)
        
        - `visited[r] = 1`
            
        - Neighbors of `r`: `{t}` → `t` is 0 ⇒ `dfs(t)`
            
            ### dfs(t)
            
            - `visited[t] = 1`
                
            - Neighbors of `t`: `{f}` → `f` is 0 ⇒ `dfs(f)`
                
                ### dfs(f)
                
                - `visited[f] = 1`
                    
                - Neighbors of `f`: `{}` (none)
                    
                - Postorder push: `result += 'f'`
                    
                - `visited[f] = 2`
                    
                - Return `true`
                    
            - Back to `t`: all neighbors done
                
            - Postorder push: `result += 't'` → result = `"ft"`
                
            - `visited[t] = 2`
                
            - Return `true`
                
        - Back to `r`: neighbors done
            
        - Postorder push: `result += 'r'` → result = `"ftr"`
            
        - `visited[r] = 2`
            
        - Return `true`
            
    - Back to `e`: neighbors done
        
    - Postorder push: `result += 'e'` → result = `"ftre"`
        
    - `visited[e] = 2`
        
    - Return `true`
        
- Back to `w`: neighbors done
    
- Postorder push: `result += 'w'` → result = `"ftrew"`
    
- `visited[w] = 2`
    
- Return `true`
    

**Continue outer loop:** nodes `e, r, t, f` are already `visited=2`, so skipped.

---

# 4) Finalize order

Postorder result we built: `"ftrew"`  
Reverse it: **`"wertf"`**

That’s the alien alphabet consistent with the given dictionary.

---

# 5) Where cycle detection happens (why DFS works)

During `dfs(u)`, if we see a neighbor `v` with `visited[v] == 1` (still “visiting”), that’s a **back edge** → a **cycle**. We immediately return `false` and the whole function returns `""`. In our trace, we never hit `visited==1` on a neighbor, so there’s no cycle.

---

## TL;DR of the dry run

- Edges from first differences: `w→e→r→t→f`
    
- DFS goes deep: `w → e → r → t → f`
    
- Postorder pushes: `f, t, r, e, w` ⇒ reverse ⇒ **`wertf`**
    
- No `visited==1` conflicts encountered ⇒ no cycle ⇒ valid order.


