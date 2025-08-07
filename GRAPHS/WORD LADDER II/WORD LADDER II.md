Here’s the **Word Ladder II** problem in classic **LeetCode-style**, exactly how you prefer — **just the question, no hints, no solutions**: #WORD_LADDER_II

---

### 🧩 LeetCode 126. **Word Ladder II**

**Hard**

---

You are given two words, `beginWord` and `endWord`, and a dictionary `wordList`.

Return **all the shortest transformation sequences** from `beginWord` to `endWord`, such that:

1. Only one letter can be changed at a time.
    
2. Each transformed word must exist in the `wordList`.
    

Each sequence should be returned as a **list of words**, beginning with `beginWord` and ending with `endWord`.

If there is **no such sequence**, return an empty list.

---

### 🔒 Constraints:

- `1 <= beginWord.length <= 5`
    
- `endWord.length == beginWord.length`
    
- `1 <= wordList.length <= 500`
    
- `wordList[i].length == beginWord.length`
    
- `beginWord`, `endWord`, and `wordList[i]` consist of lowercase English letters.
    
- `beginWord != endWord`
    
- All words in `wordList` are **unique**.
    

---

### 🔁 Example:

```txt
Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
```


> You may return the sequences in any order.

---


# MINI-NOTE : 

🔹 **Problem:** Word Ladder I  
🔹 **Graph Type:** Implicit Word Graph (Each word is a node, edges exist if words differ by 1 letter)  
🔹 **Technique:** BFS (Unweighted Shortest Path)  
🔹 **Core Template:**

```cpp
queue<string> q;
unordered_set<string> wordSet; // for O(1) lookup
q.push(beginWord);

while (!q.empty()) {
    for (int i = 0; i < q.size(); ++i) {
        string word = q.front(); q.pop();
        if (word == endWord) return level;
        for (each position) {
            for (char c = 'a'; c <= 'z'; ++c) {
                string newWord = word;
                newWord[pos] = c;
                if (wordSet.count(newWord)) {
                    q.push(newWord);
                    wordSet.erase(newWord); // mark visited
                }
            }
        }
    }
    level++;
}
return 0;
```

🔹 **Pattern Tag:** #BFS #ShortestPath #WordGraph #UnweightedGraph

---

🔸 **Logic Summary:**

- Transform `beginWord` into `endWord` by changing one letter at a time.
    
- Each transformed word must be in `wordList`.
    
- Goal is to find the shortest transformation **length**, not the path.
    
- Classic **BFS** problem in disguise → shortest path in unweighted graph.
    

---

🔸 **Trick:**

- Don't pre-build the graph.
    
- Use **character substitution at each position** to generate neighbors dynamically.
    
- Use `unordered_set` for fast lookups and to track unvisited words.
    

---

🔸 **Why DFS/Backtracking won’t work:**

- You’ll end up exploring all possible paths → exponential time.
    
- Only BFS guarantees shortest path in unweighted graphs.
    

---

🔸 **Final Insight:**

This problem is a disguised **graph shortest path** problem where nodes are words and edges exist if they differ by one letter.  
Use BFS from `beginWord` to reach `endWord` with level counting to track distance.


---


You're feeling stuck right now — and that's completely okay.  
You've been grinding hard through a dense set of graph problems. What you're facing now (Word Ladder II) is a **combination of BFS + backtracking**, and it _is_ a tough transition.

So let’s not panic — I’ve got you.

---

### 🧠 First, remember what the question asks:

You're given:

- `beginWord`
    
- `endWord`
    
- `wordList`
    

You need to find **all shortest transformation sequences** from `beginWord` to `endWord` where:

- Only one letter changes at each step.
    
- Each transformed word must exist in `wordList`.
    

So you're NOT just checking _if_ a path exists (Word Ladder I), you're now collecting **all shortest paths**.

---

### ✅ Strategy (High-level):

We break this into 2 phases:

---

#### 🔹 Phase 1: BFS

Build a graph (using `unordered_map<string, vector<string>> parents`)

- For every word, store the words that came before it (i.e., built level-by-level BFS tree)
    

This gives us:

- Level-wise traversal (shortest path guaranteed).
    
- A map to trace back all valid shortest paths later.
    

---

#### 🔹 Phase 2: Backtrack

Once BFS finishes, use DFS or backtracking to **reconstruct all paths** from `endWord` back to `beginWord` using the `parents` map.

---

### ✅ Final Optimized Code (Clean, BFS + Backtrack)

```cpp
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        vector<vector<string>> res;

        if (!dict.count(endWord)) return res;

        unordered_map<string, vector<string>> parents;
        unordered_set<string> visited, currLevel;

        queue<string> q;
        q.push(beginWord);
        visited.insert(beginWord);

        bool found = false;

        while (!q.empty() && !found) {
            int size = q.size();
            currLevel.clear();

            for (int i = 0; i < size; ++i) {
                string word = q.front(); q.pop();

                string original = word;
                for (int j = 0; j < word.size(); ++j) {
                    char c = word[j];
                    for (char ch = 'a'; ch <= 'z'; ++ch) {
                        if (ch == c) continue;
                        word[j] = ch;

                        if (dict.count(word)) {
                            if (!visited.count(word)) {
                                if (!currLevel.count(word)) {
                                    q.push(word);
                                    currLevel.insert(word);
                                }
                                parents[word].push_back(original);
                                if (word == endWord) found = true;
                            }
                        }
                    }
                    word[j] = c;
                }
            }

            for (const string& w : currLevel) visited.insert(w);
        }

        if (found) {
            vector<string> path = {endWord};
            backtrack(endWord, beginWord, parents, path, res);
        }

        return res;
    }

    void backtrack(string& word, string& beginWord,
                   unordered_map<string, vector<string>>& parents,
                   vector<string>& path,
                   vector<vector<string>>& res) {
        if (word == beginWord) {
            vector<string> temp = path;
            reverse(temp.begin(), temp.end());
            res.push_back(temp);
            return;
        }

        for (string& p : parents[word]) {
            path.push_back(p);
            backtrack(p, beginWord, parents, path, res);
            path.pop_back();
        }
    }
};
```

---

### 🔁 What You Should Take Away:

- **BFS builds the structure** (word connections via shortest steps).
    
- **Backtracking reconstructs all valid shortest sequences**.
    

---

If you're feeling stuck, take a short break — maybe 15 minutes. Come back with a clearer mind and walk through this code step-by-step. I’ll be here to help break any part down again if needed.

You’ve already climbed high — this is just one more hill. Ready to go through it slowly now?

---

# DRY RUN 


Let’s **dry run the BFS parent‐mapping phase** step by step, using our example:

```txt
beginWord = "hit"
endWord   = "cog"
wordList  = ["hot","dot","dog","lot","log","cog"]
```

We track:

- **dict**: set of valid words
    
- **q**: BFS queue
    
- **visited**: globally visited words
    
- **currLevel**: visited in the current BFS layer
    
- **parents**: map from each word → list of its predecessors
    

---

### 🔹 Initialization

```cpp
dict    = {hot, dot, dog, lot, log, cog}
q       = ["hit"]
visited = {hit}
parents = {}
foundEnd = false
```

---

### 🔹 Level 1 (distance = 0 → 1)

**Before loop:**  
`q.size() = 1`

**Process “hit”:**

- original = `"hit"`
    
- mutate each position:
    
    1. pos=0:
        
        - `"ait","bit",…,"hot",…`
            
        - Only `"hot"` in dict
            
        
        Since `"hot"` not in `visited`:
        
        - `currLevel.insert("hot")` → `{hot}`
            
        - `q.push("hot")`
            
        - `parents["hot"].push_back("hit")` → `{ hot: [hit] }`
            
    2. pos=1,2: no other dict matches
        

**End of Level 1:**

```
q         = ["hot"]  
currLevel = {hot}  
visited   = {hit}  
parents   = { "hot": ["hit"] }  
foundEnd  = false  
```

Mark `hot` visited:

```
visited = {hit, hot}  
```

---

### 🔹 Level 2 (distance = 1 → 2)

**Before loop:**  
`q.size() = 1`

**Process “hot”:**

- original = `"hot"`
    
    1. pos=0: `"aot",…` no match
        
    2. pos=1: `"hat","hbt",…,"dot","lot",…`
        
        - `"dot"`, `"lot"` in dict
            
        
        For each:
        
        - Not in `visited` →
            
            - `currLevel.insert(word)`
                
            - `q.push(word)`
                
        - `parents[word].push_back("hot")`
            
        
        => `parents` adds:
        
        ```
        dot: [hot]
        lot: [hot]
        ```
        
    3. pos=2: no match
        

**End of Level 2:**

```
q         = ["dot","lot"]  
currLevel = {dot, lot}  
visited   = {hit, hot}  
parents   = {
              hot: [hit],
              dot: [hot],
              lot: [hot]
            }  
foundEnd = false  
```

Mark these visited:

```
visited = {hit, hot, dot, lot}  
```

---

### 🔹 Level 3 (distance = 2 → 3)

**Before loop:**  
`q.size() = 2` (`"dot","lot"`)

**Process “dot”:**

- original = `"dot"`
    
    - Only `"dog"` matches one‐letter change
        
        - Not visited → `currLevel.insert("dog")`, `q.push("dog")`
            
        - `parents["dog"] = ["dot"]`
            

**Process “lot”:**

- original = `"lot"`
    
    - Only `"log"` matches
        
        - Not visited → `currLevel.insert("log")`, `q.push("log")`
            
        - `parents["log"] = ["lot"]`
            

**End of Level 3:**

```
q         = ["dog","log"]  
currLevel = {dog, log}  
visited   = {hit, hot, dot, lot}  
parents   = {
              hot: [hit],
              dot: [hot],
              lot: [hot],
              dog: [dot],
              log: [lot]
            }  
foundEnd = false  
```

Mark these visited:

```
visited = {hit, hot, dot, lot, dog, log}  
```

---

### 🔹 Level 4 (distance = 3 → 4)

**Before loop:**  
`q.size() = 2` (`"dog","log"`)

**Process “dog”:**

- original = `"dog"`
    
    - `"cog"` matches
        
        - Not visited → `currLevel.insert("cog")`, `q.push("cog")`
            
        - `parents["cog"].push_back("dog")`
            
        - `foundEnd = true`
            

**Process “log”:**

- original = `"log"`
    
    - `"cog"` matches again
        
        - Already in `currLevel` but not yet in `visited` →
            
            - `parents["cog"].push_back("log")`
                

**End of Level 4:**

```
q         = ["cog"]  
currLevel = {cog}  
visited   = {hit, hot, dot, lot, dog, log}  
parents   = {
              hot: [hit],
              dot: [hot],
              lot: [hot],
              dog: [dot],
              log: [lot],
              cog: [dog, log]
            }  
foundEnd = true  
```

We break out of the BFS loop (shortest depth reached).

---

## 🔹 BFS Phase Results

- **parents** map built:
    
    ```
    hit → []
    hot → [hit]
    dot → [hot]
    lot → [hot]
    dog → [dot]
    log → [lot]
    cog → [dog, log]
    ```
    
- **level** map (implicitly):
    
    ```
    hit:0, hot:1, dot:2, lot:2, dog:3, log:3, cog:4
    ```
    
- **Queue** left with `"cog"`, but BFS stops.
    

---

At this point, **we have all the data** (`parents`) needed for **Stage 2: Backtracking**, which will reconstruct **all shortest paths** from `"hit"` to `"cog"`.

Let me know when you’re ready to walk through **backtracking**, or if you’d like to inspect any part of this BFS dry run in more detail.


---

Great, Bhavesh. Let’s dive into **Stage 2: Backtracking** to reconstruct **all shortest paths** using the `parents` map we built.

---

## 🔷 Backtracking Overview

- We start from `endWord` and move **backwards** via its parents.
    
- Each recursive call adds a parent word to the current path.
    
- When we reach `beginWord`, we have one complete path (in reverse).
    
- We **reverse** it and add to our results.
    
- We explore **all** parent branches to get **all** shortest sequences.
    

---

### 🧩 Step-by-Step Code for Backtracking

```cpp
// Assume `parents` is our map<string, vector<string>> built during BFS
vector<vector<string>> result; 

void backtrack(const string& word,
               const string& beginWord,
               unordered_map<string, vector<string>>& parents,
               vector<string>& path) {
    if (word == beginWord) {
        // We've reached the start; record the full path
        vector<string> temp = path;
        reverse(temp.begin(), temp.end());
        result.push_back(temp);
        return;
    }

    // Recurse over all parents of `word`
    for (const string& p : parents[word]) {
        path.push_back(p);
        backtrack(p, beginWord, parents, path);
        path.pop_back();
    }
}
```

#### How to Invoke It

After BFS, you’d do:

```cpp
vector<string> path = { endWord };
backtrack(endWord, beginWord, parents, path);
// `result` now contains all shortest sequences
```

---

## 🔁 Dry Run of Backtracking

Using our example’s `parents` map:

```
hit → []
hot → [hit]
dot → [hot]
lot → [hot]
dog → [dot]
log → [lot]
cog → [dog, log]
```

We call:

```cpp
path = ["cog"];
backtrack("cog", "hit", parents, path);
```

1. **Call** `backtrack("cog")`
    
    - `word != beginWord`
        
    - Loop `parents["cog"] = ["dog","log"]`
        
2. **First branch**: parent = `"dog"`
    
    - `path = ["cog","dog"]`
        
    - **Call** `backtrack("dog")`
        
        - Loop `parents["dog"] = ["dot"]`
            
3. **Nested**: parent = `"dot"`
    
    - `path = ["cog","dog","dot"]`
        
    - **Call** `backtrack("dot")`
        
        - Loop `parents["dot"] = ["hot"]`
            
4. **Nested**: parent = `"hot"`
    
    - `path = ["cog","dog","dot","hot"]`
        
    - **Call** `backtrack("hot")`
        
        - Loop `parents["hot"] = ["hit"]`
            
5. **Nested**: parent = `"hit"`
    
    - `path = ["cog","dog","dot","hot","hit"]`
        
    - **Call** `backtrack("hit")`
        
        - `word == beginWord`
            
        - Reverse `path` → `["hit","hot","dot","dog","cog"]`
            
        - Add to `result`
            
    
    **Return**, pop `"hit"`, back to `"hot"` call.
    
6. **Back at** `backtrack("hot")`, no more parents → pop `"hot"`, return to `"dot"`.
    

Continue popping back up to the `"cog"` level.

---

7. **Second branch** at top: parent = `"log"`
    
    - `path = ["cog","log"]`
        
    - **Call** `backtrack("log")` → parents = `[lot]`
        
    - Push/pop similarly to build  
        `["cog","log","lot","hot","hit"]` → reversed → `["hit","hot","lot","log","cog"]`
        
    - Add to `result`
        

---

### ✅ Final `result`

```cpp
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
```

---

**That completes the backtracking phase.** You now have **all** shortest transformation sequences, built from the BFS-constructed “parent tree.”

Feel free to integrate both stages into one cohesive function and test with other examples.

---



