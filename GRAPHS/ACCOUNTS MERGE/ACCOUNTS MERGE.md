 **LeetCode-style problem statement** for **Accounts Merge**: #ACCOUNTS_MERGE

---

### 721. Accounts Merge

You are given a list of `accounts`, where each element `accounts[i]` is a list of strings, where:

- The first element `accounts[i][0]` is a name (a string).
    
- The rest of the elements are emails representing that person’s account.
    

Now, we want to merge these accounts. Two accounts belong to the same person if there is **any common email** between them.  
Note that even if two accounts have the same name, they may belong to different people, as people could have the same name. A person can have any number of accounts initially, but all of their accounts should be merged into a single account after merging.

The merged account’s name should be the name of the person, and the emails should be sorted in **lexicographical order**.

Return the accounts in any order.

---

**Example 1:**

**Input:**

```
accounts = [
  ["John", "johnsmith@mail.com", "john_newyork@mail.com"],
  ["John", "johnsmith@mail.com", "john00@mail.com"],
  ["Mary", "mary@mail.com"],
  ["John", "johnnybravo@mail.com"]
]
```

**Output:**

```
[
  ["John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"],
  ["Mary", "mary@mail.com"],
  ["John", "johnnybravo@mail.com"]
]
```

---

**Example 2:**

**Input:**

```
accounts = [
  ["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],
  ["Kevin","Kevin3@m.co","Kevin2@m.co","Kevin0@m.co"],
  ["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],
  ["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],
  ["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]
]
```

**Output:**

```
[
  ["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],
  ["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],
  ["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],
  ["Kevin","Kevin0@m.co","Kevin2@m.co","Kevin3@m.co"],
  ["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]
]
```

---

**Constraints:**

- `1 <= accounts.length <= 1000`
    
- `2 <= accounts[i].length <= 10`
    
- `1 <= accounts[i][j].length <= 30`
    
- `accounts[i][0]` consists of English letters.
    
- `accounts[i][j]` (for `j > 0`) is a valid email.
    

---

# MINI-NOTE :

## 🔹 Problem Deep Dive

Given a list of accounts where each account is `[name, email1, email2, ...]`, merge accounts belonging to the same person if they share **any common email**. The key insight is that accounts can be transitively connected: if Account A shares an email with Account B, and Account B shares a different email with Account C, then all three accounts belong to the same person.

**Input**: `[["John","john@gmail.com","john@yahoo.com"],["John","john@yahoo.com","john@hotmail.com"],["Mary","mary@gmail.com"]]` **Output**: `[["John","john@gmail.com","john@hotmail.com","john@yahoo.com"],["Mary","mary@gmail.com"]]`

## 🔹 Why This Is Actually A Graph Problem

This problem disguises itself as string manipulation, but it's fundamentally about **connected components**:

- **Nodes**: Each unique email address
- **Edges**: Two emails are connected if they appear in the same account
- **Connected Component**: All emails belonging to the same person
- **Goal**: Find all connected components and reconstruct merged accounts

The brilliance lies in recognizing that email sharing creates transitive relationships that graphs handle naturally.

## 🔹 Union-Find vs DFS/BFS Analysis

### Why Union-Find Is Superior Here

1. **Incremental Building**: As we process each account, we incrementally build connections. Union-Find excels at this dynamic connectivity.
2. **Path Compression**: Efficiently flattens deep chains like `email1 → email2 → email3 → root`
3. **Amortized O(α(n))**: Nearly constant time operations for practical input sizes
4. **Memory Efficient**: No need to explicitly build adjacency lists

### When DFS/BFS Would Be Better

- If we needed to find actual paths between emails
- If we needed to analyze the structure of connections
- For one-time connectivity queries on pre-built graphs

## 🔹 Core Algorithm Template

### Phase 1: Build Union-Find Structure

```cpp
class UnionFind {
private:
    vector<int> parent;
    
public:
    UnionFind(int n) : parent(n) {
        // Initialize each element as its own parent (self-loop)
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression flattens tree
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            parent[px] = py;  // Union by rank optimization can be added here
        }
    }
};

// Email mapping structures
unordered_map<string, int> email_to_id;
unordered_map<string, string> email_to_name;
```

### Phase 2: Process Accounts

```cpp
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    UnionFind uf(10000);  // Maximum possible emails
    unordered_map<string, int> email_to_id;
    unordered_map<string, string> email_to_name;
    int id_counter = 0;
    
    // Process each account and build Union-Find structure
    for (const auto& account : accounts) {
        string name = account[0];
        
        // Assign unique IDs to new emails
        for (int i = 1; i < account.size(); i++) {
            string email = account[i];
            
            if (email_to_id.find(email) == email_to_id.end()) {
                email_to_id[email] = id_counter++;
            }
            
            // Map email to account owner's name
            email_to_name[email] = name;
        }
        
        // Union all emails in this account with the first email
        if (account.size() > 1) {
            int first_id = email_to_id[account[1]];
            for (int i = 2; i < account.size(); i++) {
                int current_id = email_to_id[account[i]];
                uf.unite(first_id, current_id);
            }
        }
    }
```

### Phase 3: Group and Reconstruct

```cpp
    // Group emails by their root parent (connected component)
    unordered_map<int, vector<string>> root_to_emails;
    
    for (const auto& [email, email_id] : email_to_id) {
        int root = uf.find(email_id);
        root_to_emails[root].push_back(email);
    }
    
    // Build final merged accounts
    vector<vector<string>> result;
    for (auto& [root, emails] : root_to_emails) {
        sort(emails.begin(), emails.end());  // Sort emails lexicographically
        
        // Get name from any email in this component (they all belong to same person)
        string owner_name = email_to_name[emails[0]];
        
        // Create merged account: [name, email1, email2, ...]
        vector<string> merged_account = {owner_name};
        merged_account.insert(merged_account.end(), emails.begin(), emails.end());
        
        result.push_back(merged_account);
    }
    
    return result;
}
```

## 🔹 Critical Implementation Details

### The Name Mapping Challenge

The trickiest part is maintaining `email → name` mapping because:

1. Multiple accounts can have the same name (different people named "John")
2. We need to retrieve the correct name after merging emails
3. Solution: During initial processing, map each email to its account owner's name

### Path Compression Optimization

```cpp
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // This single line flattens the entire tree path!
    }
    return parent[x];
}
```

Without path compression, repeatedly calling `find()` on deep chains could degrade to O(n) per operation. With path compression, every node on the path gets directly connected to the root, making future `find()` calls nearly O(1).

## 🔹 Complexity Analysis

- **Time**: O(N × α(N) + M log M) where N = total emails, M = emails per merged account
    - N × α(N): Union-Find operations with path compression
    - M log M: Sorting emails within each merged account
- **Space**: O(N) for parent array, email mappings, and result construction

## 🔹 Pattern Recognition Tags

`Graph Connectivity` | `Union-Find` | `Connected Components` | `Transitive Relationships` | `Dynamic Connectivity`

## 🔹 Mental Model

Think of this as a **social network problem**:

- People are connected if they share email addresses
- We want to find all connected groups (friend circles)
- Union-Find efficiently builds these social clusters as we discover shared connections

## 🔹 Common Pitfalls

1. **Forgetting to sort emails**: Output requires sorted email lists
2. **Name confusion**: Using wrong name for merged accounts
3. **Not handling single-email accounts**: They form their own connected components
4. **Inefficient union strategy**: Always union with first email of each account for consistency

## 🔹 Extension Opportunities

- **Weighted Union-Find**: Union by rank for even better performance
- **Online queries**: "Are these two emails from the same person?"
- **Account history tracking**: When were accounts merged?
- **Similarity scoring**: How "connected" are two email addresses?

This problem beautifully demonstrates how graph theory concepts apply to seemingly unrelated domains like account management and data deduplication.

---

# SOLUTION : 

## Code (C++ with DSU)

```cpp
#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unionSet(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DSU dsu(n);

        unordered_map<string, int> emailToIndex; // maps email -> account index

        // Step 1: Union accounts that share emails
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                if (emailToIndex.count(email)) {
                    dsu.unionSet(i, emailToIndex[email]);
                } else {
                    emailToIndex[email] = i;
                }
            }
        }

        // Step 2: Gather emails under their parent (representative account)
        unordered_map<int, set<string>> merged;
        for (auto &p : emailToIndex) {
            string email = p.first;
            int owner = dsu.find(p.second);
            merged[owner].insert(email);
        }

        // Step 3: Build final result
        vector<vector<string>> result;
        for (auto &entry : merged) {
            vector<string> account;
            account.push_back(accounts[entry.first][0]); // account name
            account.insert(account.end(), entry.second.begin(), entry.second.end());
            result.push_back(account);
        }

        return result;
    }
};
```

---

## Key Idea

1. **DSU binds accounts** → If two accounts share at least one email, they are merged.
    
2. **Email-to-index mapping** → Every email is linked to an account index.
    
3. **Union all shared emails** → If same email appears in two accounts, union those account indices.
    
4. **Group by parent index** → Collect all emails under their root representative.
    
5. **Sort emails** → Use `set<string>` to keep them sorted.
    

---

⚡ Example Dry Run (Quick Recap with Input):

```
accounts = [
  ["John", "johnsmith@mail.com", "john00@mail.com"],
  ["John", "johnnybravo@mail.com"],
  ["John", "johnsmith@mail.com", "john_newyork@mail.com"],
  ["Mary", "mary@mail.com"]
]
```

- "[johnsmith@mail.com](mailto:johnsmith@mail.com)" links account 0 and 2 → union(0,2)
    
- Final groups:
    
    - John → {[johnsmith@mail.com](mailto:johnsmith@mail.com), [john00@mail.com](mailto:john00@mail.com), [john_newyork@mail.com](mailto:john_newyork@mail.com)}
        
    - John → {[johnnybravo@mail.com](mailto:johnnybravo@mail.com)}
        
    - Mary → {[mary@mail.com](mailto:mary@mail.com)}
        

Output:

```
[
  ["John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"],
  ["John", "johnnybravo@mail.com"],
  ["Mary", "mary@mail.com"]
]
```

---

# DRY-RUN : 

Great — let’s do a **full, line-by-line dry run** of the DSU-based `accountsMerge` code you have, using this input:

```text
accounts = [
  ["John", "johnsmith@mail.com", "john_newyork@mail.com"],
  ["John", "johnsmith@mail.com", "john00@mail.com"],
  ["Mary", "mary@mail.com"],
  ["John", "johnnybravo@mail.com"]
]
```

I’ll show the program state (DSU arrays, maps) as we execute the important lines. I’ll skip trivial lines like `#include` and focus on the algorithmic steps.

---

## Initial setup (entering `accountsMerge`)

```cpp
int n = accounts.size();              // n = 4
DSU dsu(n);                           // parent = [0,1,2,3], rank = [0,0,0,0]
unordered_map<string,int> emailToIndex; // empty
```

State:

```
n = 4
parent = [0, 1, 2, 3]
rank   = [0, 0, 0, 0]
emailToIndex = {}
```

---

## Step 1 — Build emailToIndex & union accounts that share emails

We iterate `i` from `0` to `3`.

### i = 0 (account 0 = ["John", "[johnsmith@mail.com](mailto:johnsmith@mail.com)", "[john_newyork@mail.com](mailto:john_newyork@mail.com)"])

Loop j from 1 to end:

- j = 1, email = `"johnsmith@mail.com"`
    
    ```cpp
    if (emailToIndex.count(email)) { ... } else { emailToIndex[email] = i; }
    ```
    
    Not present → set `emailToIndex["johnsmith@mail.com"] = 0`.
    
    State:
    
    ```
    emailToIndex = { "johnsmith@mail.com" -> 0 }
    ```
    
- j = 2, email = `"john_newyork@mail.com"`  
    Not present → set `emailToIndex["john_newyork@mail.com"] = 0`.
    
    State:
    
    ```
    emailToIndex = {
      "johnsmith@mail.com"     -> 0,
      "john_newyork@mail.com"  -> 0
    }
    ```
    

No unions done for i=0 (we only recorded first-seen account index for each email).

---

### i = 1 (account 1 = ["John", "[johnsmith@mail.com](mailto:johnsmith@mail.com)", "[john00@mail.com](mailto:john00@mail.com)"])

- j = 1, email = `"johnsmith@mail.com"`
    
    `emailToIndex.count(email)` is true — it maps to `0`. So we do:
    
    ```cpp
    dsu.unionSet(i, emailToIndex[email]);   // unionSet(1, 0)
    ```
    
    -> Call `unionSet(1,0)`:
    
    - `px = find(1)` → 1 (parent[1] == 1)
        
    - `py = find(0)` → 0 (parent[0] == 0)
        
    - `px != py`
        
    - `rank[px] == rank[py]` (both 0), so code executes:
        
        ```cpp
        parent[py] = px;   // parent[0] = 1
        rank[px]++;        // rank[1] = 1
        ```
        
    
    After union:
    
    ```
    parent = [1, 1, 2, 3]
    rank   = [0, 1, 0, 0]
    ```
    
    (component: root 1 contains {0,1})
    
- j = 2, email = `"john00@mail.com"`  
    Not present in `emailToIndex` → set `emailToIndex["john00@mail.com"] = 1`.
    
    State after i=1:
    
    ```
    emailToIndex = {
      "johnsmith@mail.com"     -> 0,
      "john_newyork@mail.com"  -> 0,
      "john00@mail.com"        -> 1
    }
    
    parent = [1,1,2,3]
    rank   = [0,1,0,0]
    ```
    

---

### i = 2 (account 2 = ["Mary", "[mary@mail.com](mailto:mary@mail.com)"])

- j = 1, email = `"mary@mail.com"`  
    Not present → set `emailToIndex["mary@mail.com"] = 2`.
    

State:

```
emailToIndex = {
  "johnsmith@mail.com"     -> 0,
  "john_newyork@mail.com"  -> 0,
  "john00@mail.com"        -> 1,
  "mary@mail.com"          -> 2
}
parent = [1,1,2,3]
rank   = [0,1,0,0]
```

---

### i = 3 (account 3 = ["John", "[johnnybravo@mail.com](mailto:johnnybravo@mail.com)"])

- j = 1, email = `"johnnybravo@mail.com"`  
    Not present → set `emailToIndex["johnnybravo@mail.com"] = 3`.
    

Final state after processing all accounts:

```
emailToIndex = {
  "johnsmith@mail.com"     -> 0,
  "john_newyork@mail.com"  -> 0,
  "john00@mail.com"        -> 1,
  "mary@mail.com"          -> 2,
  "johnnybravo@mail.com"   -> 3
}
parent = [1,1,2,3]
rank   = [0,1,0,0]
```

---

## Step 2 — Group emails under their DSU root (`merged` map)

We create:

```cpp
unordered_map<int, set<string>> merged;
for (auto &p : emailToIndex) {
    string email = p.first;
    int owner = dsu.find(p.second);  // find the representative account index
    merged[owner].insert(email);
}
```

We iterate over `emailToIndex` entries one-by-one (unordered order may differ, but result grouping is deterministic). I’ll process in the order shown above.

#### Entry: `"johnsmith@mail.com" -> 0`

- `owner = dsu.find(0)`
    
    - find(0): parent[0] = 1 → find(1): parent[1] = 1 → return 1. (path compression sets parent[0] = 1)
        
- `merged[1].insert("johnsmith@mail.com")`
    

`merged`:

```
1 : { "johnsmith@mail.com" }
```

#### Entry: `"john_newyork@mail.com" -> 0`

- `owner = dsu.find(0)` → path compression already done; returns 1.
    
- `merged[1].insert("john_newyork@mail.com")`
    

`merged`:

```
1 : { "john_newyork@mail.com", "johnsmith@mail.com" }  (set is sorted lexicographically)
```

#### Entry: `"john00@mail.com" -> 1`

- `owner = dsu.find(1)` → find(1) returns 1.
    
- `merged[1].insert("john00@mail.com")`
    

`merged`:

```
1 : { "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com" }
```

#### Entry: `"mary@mail.com" -> 2`

- `owner = dsu.find(2)` → 2
    
- `merged[2].insert("mary@mail.com")`
    

`merged`:

```
1 : { "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com" }
2 : { "mary@mail.com" }
```

#### Entry: `"johnnybravo@mail.com" -> 3`

- `owner = dsu.find(3)` → 3
    
- `merged[3].insert("johnnybravo@mail.com")`
    

Final `merged`:

```
1 : { "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com" }
2 : { "mary@mail.com" }
3 : { "johnnybravo@mail.com" }
```

Notes:

- Each `set<string>` keeps emails sorted lexicographically automatically.
    
- The keys `1,2,3` are DSU roots (representative account indices). Root `1` corresponds to account index 1 (the second input account).
    

---

## Step 3 — Build the final `result` vector

```cpp
vector<vector<string>> result;
for (auto &entry : merged) {
    vector<string> account;
    account.push_back(accounts[entry.first][0]); // name
    account.insert(account.end(), entry.second.begin(), entry.second.end()); // sorted emails
    result.push_back(account);
}
```

Process each `merged` entry:

- entry.first = `1`:
    
    - name = `accounts[1][0]` = `"John"`
        
    - emails = `{ "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com" }`
        
    - account vector = `["John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"]`
        
    - push into `result`.
        
- entry.first = `2`:
    
    - name = `accounts[2][0]` = `"Mary"`
        
    - emails = `{ "mary@mail.com" }`
        
    - account vector = `["Mary", "mary@mail.com"]`
        
    - push into `result`.
        
- entry.first = `3`:
    
    - name = `accounts[3][0]` = `"John"`
        
    - emails = `{ "johnnybravo@mail.com" }`
        
    - account vector = `["John", "johnnybravo@mail.com"]`
        
    - push into `result`.
        

`result` (order of rows depends on unordered_map iteration order — any order is acceptable):

```text
[
  ["John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"],
  ["Mary", "mary@mail.com"],
  ["John", "johnnybravo@mail.com"]
]
```

---

## Final returned value

```cpp
return result;
```

This matches the expected merged accounts set:

- One John with 3 emails combined and sorted,
    
- Mary with her single email,
    
- Another John (johnnybravo) separate.
    

---

## A few important implementation notes you should keep in mind

1. **Why we map email → first-seen account index** (`emailToIndex[email] = i`):
    
    - When we later see the same email in a different account `i2`, we do `unionSet(i2, firstSeenIndex)` to connect the two accounts.
        
    - The DSU groups account indices that share any email.
        
2. **Why we use `set<string>` for merged values**:
    
    - `set` keeps emails sorted automatically (LeetCode asks for sorted emails). If you prefer, you can collect into a `vector` and `sort()` before pushing.
        
3. **Why we use account index as DSU nodes instead of email indices**:
    
    - This implementation unions **account indices** (each account is a DSU node) and uses the `emailToIndex` mapping to connect accounts that share emails.
        
    - An equivalent approach is to treat **each unique email as a DSU node** — both approaches are valid. The implementation you used is a common, clean variant.
        
4. **Path compression** happened during the `dsu.find()` calls in grouping stage, ensuring future finds are O(1).
    

---
