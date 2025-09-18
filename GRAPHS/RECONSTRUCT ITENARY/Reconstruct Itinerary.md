
# 332. Reconstruct Itinerary

You are given a list of airline tickets where `tickets[i] = [fromi, toi]` represent the departure and arrival airports of one flight. The task is to reconstruct the itinerary in order and return it.

All of the tickets belong to a man who departs from `"JFK"`, thus, the itinerary must begin with `"JFK"`.

- If there are multiple valid itineraries, you should return the itinerary that has the **smallest lexical order** when read as a single string.
    
    - For example, the itinerary `["JFK", "LGA"]` has a smaller lexical order than `["JFK", "LGB"]`.
        
- You may assume all tickets form at least one valid itinerary.
    
- You must use **all the tickets once and only once**.
    

---

**Example 1:**

```
Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]
```

**Example 2:**

```
Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] 
but it is larger in lexical order.
```

---

**Constraints:**

- `1 <= tickets.length <= 300`
    
- `tickets[i].length == 2`
    
- `fromi.length == 3`
    
- `toi.length == 3`
    
- `fromi` and `toi` consist of uppercase English letters.
    
- `fromi != toi`
    

---

# MINI-NOTE : 







---

# CODE 
 
Here’s the **LeetCode solution for 332. Reconstruct Itinerary** in **C++** (using Hierholzer’s Algorithm + lexical order via `multiset` or `priority_queue`):

```cpp
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // Graph: departure -> list of arrivals (sorted by lexical order)
        unordered_map<string, multiset<string>> graph;
        for (auto &ticket : tickets) {
            graph[ticket[0]].insert(ticket[1]);
        }
        
        vector<string> result;
        stack<string> st;
        st.push("JFK");  // starting point
        
        while (!st.empty()) {
            string curr = st.top();
            
            // If no further edges from current node
            if (graph[curr].empty()) {
                result.push_back(curr); // add to result while backtracking
                st.pop();
            } else {
                // Take the smallest lexical edge
                auto next = graph[curr].begin();
                st.push(*next);
                graph[curr].erase(next); // use this ticket once
            }
        }
        
        reverse(result.begin(), result.end()); // reverse because we backtracked
        return result;
    }
};
```

---

✅ **Key Ideas in Code**:

1. Build adjacency list with `multiset` → automatically keeps destinations sorted.
    
2. Use **Hierholzer’s Algorithm**:
    
    - Traverse until you hit a dead-end.
        
    - Backtrack and add nodes to the result.
        
3. Reverse the result at the end since we collect airports in backtracking order.
    



---

# EXPLANATION : 

Perfect, let’s connect it to what we already know 🚀

---

### 🔹 Step 1. What is happening in the problem?

We are given **tickets = edges** (directed edges) and airports = **nodes**.  
We must reconstruct an itinerary that:

1. **Starts at JFK**
    
2. **Uses all edges exactly once**
    
3. **Respects lexicographical order if multiple paths exist**
    

This is **exactly** the definition of an **Eulerian Path** in a **directed graph** — a path that uses all edges once and only once.

---

### 🔹 Step 2. But why Eulerian Path?

- Every ticket = one edge
    
- We must **use every ticket exactly once** (that’s Eulerian path condition).
    
- The graph might not be Eulerian in the strict mathematical sense (in-degree ≠ out-degree sometimes), but LeetCode guarantees at least one valid itinerary always exists.
    

So we adapt **Hierholzer’s Algorithm** (Eulerian Path construction):

- Keep exploring edges greedily in lexical order.
    
- When a node has no more unused outgoing edges, we backtrack.
    
- This naturally gives the path in reverse → so we need to reverse the result at the end.
    

---

### 🔹 Step 3. Why lexicographical order?

Normally Eulerian path doesn’t care about order. But here, we must pick the **smallest lexical airport first**.  
So, for each adjacency list, we store destinations in a **min-heap (priority queue)** or sorted structure.

Example:

```
From JFK: ["SFO", "ATL"]
→ We must always take "ATL" first because "ATL" < "SFO"
```

---

### 🔹 Step 4. Core Intuition (Crux)

- Imagine DFS as **boarding flights**:
    
    - Always board the lexicographically smallest available flight.
        
    - Once you reach an airport where no flights are left, **that’s your final stop for now** → backtrack and record it.
        
- This ensures tickets are consumed properly and final itinerary is reconstructed.
    

---

Perfect 👍 Let’s dry run **Example 2** from LeetCode:

---

### ✈ Input

```
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
```

We must start from `JFK`.  
Adjacency list after sorting lexicographically:

```
JFK → [ATL, SFO]
SFO → [ATL]
ATL → [JFK, SFO]
```

---

### 🔹 Step 1: DFS from JFK

- Current = `JFK`
    
- Choices = `["ATL","SFO"]` → pick `"ATL"` (lexicographically smaller).
    
- Consume edge `JFK→ATL`.
    

---

### 🔹 Step 2: DFS from ATL

- Current = `ATL`
    
- Choices = `["JFK","SFO"]` → pick `"JFK"`.
    
- Consume edge `ATL→JFK`.
    

---

### 🔹 Step 3: DFS from JFK (again)

- Current = `JFK`
    
- Choices = `[SFO]` (ATL already used)
    
- Take `JFK→SFO`.
    

---

### 🔹 Step 4: DFS from SFO

- Current = `SFO`
    
- Choices = `[ATL]`
    
- Take `SFO→ATL`.
    

---

### 🔹 Step 5: DFS from ATL (again)

- Current = `ATL`
    
- Choices = `[SFO]` (JFK already used)
    
- Take `ATL→SFO`.
    

---

### 🔹 Step 6: DFS from SFO (again)

- Current = `SFO`
    
- Choices = [] → no more outgoing edges!
    
- Add `"SFO"` to itinerary (but remember, we backtrack, so this is added in reverse).
    

---

### 🔹 Backtracking Phase

We now unwind recursion:

- From `ATL` → last edge exhausted → add `"ATL"`.
    
- From `SFO` → exhausted → add `"SFO"`.
    
- From `JFK` → exhausted → add `"JFK"`.
    
- From `ATL` → exhausted → add `"ATL"`.
    
- From `JFK` → exhausted → add `"JFK"`.
    

So we build:

```
["SFO","ATL","SFO","JFK","ATL","JFK"]
```

---

### 🔹 Step 7: Reverse result

Final itinerary:

```
["JFK","ATL","JFK","SFO","ATL","SFO"]
```

✅ Which matches LeetCode’s output.

---

let’s dry-run **Example 2** from LeetCode in the context of the **code I gave**.

### Example 2 input:

```
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],
           ["ATL","JFK"],["ATL","SFO"]]
```

### Step 1. Build graph

`graph` after insertion (using multiset so sorted automatically):

- JFK → { "ATL", "SFO" }
    
- SFO → { "ATL" }
    
- ATL → { "JFK", "SFO" }
    

---

### Step 2. Start traversal

We start with stack = [`"JFK"`], result = [].

---

### Iteration trace

**Stack top = JFK**

- graph["JFK"] = {ATL, SFO}
    
- Take lexical smallest → "ATL"
    
- Push ATL, erase from JFK.
    
- stack = [JFK, ATL]
    

---

**Stack top = ATL**

- graph["ATL"] = {JFK, SFO}
    
- Take lexical smallest → "JFK"
    
- Push JFK, erase from ATL.
    
- stack = [JFK, ATL, JFK]
    

---

**Stack top = JFK**

- graph["JFK"] = {SFO} (ATL already erased)
    
- Only option = "SFO"
    
- Push SFO.
    
- stack = [JFK, ATL, JFK, SFO]
    

---

**Stack top = SFO**

- graph["SFO"] = {ATL}
    
- Push ATL.
    
- stack = [JFK, ATL, JFK, SFO, ATL]
    

---

**Stack top = ATL**

- graph["ATL"] = {SFO} (JFK already erased)
    
- Push SFO.
    
- stack = [JFK, ATL, JFK, SFO, ATL, SFO]
    

---

**Stack top = SFO**

- graph["SFO"] = {} (ATL erased) → dead end.
    
- Pop SFO → result = ["SFO"]
    

---

**Stack top = ATL**

- graph["ATL"] = {} (SFO erased) → dead end.
    
- Pop ATL → result = ["SFO", "ATL"]
    

---

**Stack top = SFO**

- graph["SFO"] = {} → dead end.
    
- Pop SFO → result = ["SFO", "ATL", "SFO"]
    

---

**Stack top = JFK**

- graph["JFK"] = {} → dead end.
    
- Pop JFK → result = ["SFO", "ATL", "SFO", "JFK"]
    

---

**Stack top = ATL**

- graph["ATL"] = {} → dead end.
    
- Pop ATL → result = ["SFO", "ATL", "SFO", "JFK", "ATL"]
    

---

**Stack top = JFK**

- graph["JFK"] = {} → dead end.
    
- Pop JFK → result = ["SFO", "ATL", "SFO", "JFK", "ATL", "JFK"]
    

---

### Step 3. Reverse result

Now result = `["SFO","ATL","SFO","JFK","ATL","JFK"]`  
After reverse:  
`["JFK","ATL","JFK","SFO","ATL","SFO"]`

---

✅ This matches **lexical smallest itinerary** among the valid ones.

---

👉 Notice how:

- The lexical order was enforced by `multiset` each time.
    
- Dead ends caused **backtracking**, where nodes get added to result only when no further moves exist.
    
- Reversal gave final itinerary in forward order.
    

---

