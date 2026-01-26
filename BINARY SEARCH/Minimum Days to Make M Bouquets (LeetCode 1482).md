
## Problem Statement

You are given an integer array `bloomDay`, where `bloomDay[i]` represents the day on which the `i-th` flower blooms.

You are also given two integers:

- `m` → number of bouquets you need to make
    
- `k` → number of **adjacent** flowers required to make **one bouquet**
    

### Rules

- A bouquet can only be made from **k adjacent flowers**.
    
- A flower can be used in **only one bouquet**.
    
- A flower is usable only if it has bloomed.
    

### Task

Return the **minimum number of days** needed to make **at least `m` bouquets**.  
If it is **impossible**, return `-1`.

---

## Constraints

- `1 <= bloomDay.length <= 10^5`
    
- `1 <= bloomDay[i] <= 10^9`
    
- `1 <= m <= 10^6`
    
- `1 <= k <= bloomDay.length`
    

---

## Key Observations

- We are **not** searching indices or flowers — we are searching **days**.
    
- If it is possible to make bouquets on day `D`, then it will also be possible on **any day > D`**.
    
- This creates a **monotonic feasibility function**, enabling Binary Search.
    

---

## Binary Search Setup

### Core Variable

- `D` = number of days waited
    

This is the variable we want to **minimize**.

---

### Answer Space

- Minimum day = `min(bloomDay)`
    
- Maximum day = `max(bloomDay)`
    

So the search space is:

```
[min(bloomDay) … max(bloomDay)]
```

---

### Decision Function

For a fixed day `D`:

- A flower is usable if `bloomDay[i] <= D`
    
- Scan the array from left to right
    
- Count **consecutive usable flowers**
    
- Every time count reaches `k`, form one bouquet and reset
    

If total bouquets formed `>= m`, then day `D` is feasible.

This decision function is **monotonic**:

- Smaller `D` → fewer flowers bloomed → possibly infeasible
    
- Larger `D` → more flowers bloomed → feasible
    

---

## Boundary Being Searched

> **The minimum day `D` such that at least `m` bouquets can be formed.**

This is a classic **Binary Search on Answer** problem.

---

## C++ Implementation

```cpp
class Solution {
public:
    bool isPossible(vector<int>& bloomDay, int day, int m, int k) {
        int bouquets = 0;
        int flowers = 0;

        for (int i = 0; i < bloomDay.size(); i++) {
            if (bloomDay[i] <= day) {
                flowers++;
                if (flowers == k) {
                    bouquets++;
                    flowers = 0; // flowers cannot be reused
                }
            } else {
                flowers = 0; // adjacency breaks
            }
        }
        return bouquets >= m;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        long long n = bloomDay.size();
        if (n < (long long)m * k) return -1; // impossible case

        int low = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isPossible(bloomDay, mid, m, k)) {
                high = mid;      // try smaller day
            } else {
                low = mid + 1;   // need more days
            }
        }
        return low;
    }
};
```

---

## Time and Space Complexity

### Time Complexity

- `isPossible(D)` runs in **O(n)**, where `n = bloomDay.length`
    
- Binary Search runs in **O(log M)**, where `M = max(bloomDay)`
    

```
Total Time = O(n log M)
```

---

### Space Complexity

- No extra data structures used
    

```
Space = O(1)
```

---

## Common Mistakes (Learned from Practice)

- Thinking total bloomed flowers matter instead of **adjacency**
    
- Forgetting to reset flower count after forming a bouquet
    
- Searching indices instead of days
    
- Ignoring the impossible case (`m * k > n`)
    

---

## Final Insight

> This problem is about **finding the earliest time when a condition becomes true**, not about flowers or bouquets themselves.

Once feasibility is framed as a YES/NO question over days, Binary Search becomes inevitable.

---

_(This document completes Phase 1 — Problem 2 of Binary Search on Answer.)_


---


# MINI-NOTE : 

## 🔹 Problem

You are given `bloomDay[i]`, the day the `i-th` flower blooms.  
To make **one bouquet**, you need `k` **adjacent** bloomed flowers.  
You need to make **at least `m` bouquets**.

👉 Find the **minimum number of days** required.  
If impossible, return `-1`.

---

## 🔹 Graph Type

Not a graph problem.  
This is a **Binary Search on Answer** problem (searching over days).

---

## 🔹 Technique

**Binary Search on Answer**

- Greedy feasibility check using a linear scan.
    

---

## 🔹 Core Template

```cpp
low = minimum possible day
high = maximum possible day

while (low < high) {
    mid = low + (high - low) / 2;
    if (isPossible(mid)) {
        high = mid;      // keep boundary
    } else {
        low = mid + 1;   // need more days
    }
}
return low;
```

---

## 🔹 Pattern Tag

- Binary Search on Answer
    
- Minimum feasible value
    
- Monotonic decision function
    
- Adjacency-based greedy check
    

---

## 🔸 Logic Summary

- The variable we optimize is **days `D`**.
    
- For a fixed day `D`, a flower is usable if `bloomDay[i] <= D`.
    
- We scan left to right and count **consecutive usable flowers**.
    
- Every time the count reaches `k`, we form **one bouquet** and reset.
    
- If total bouquets formed ≥ `m`, then day `D` is feasible.
    
- As `D` increases, feasibility **never decreases** → monotonic.
    

---

## 🔸 Trick

- Reset flower count when:
    
    - a flower hasn’t bloomed yet, or
        
    - after forming one bouquet (flowers can’t be reused).
        
- Always check the **impossible case first**:
    
    ```cpp
    if (m * k > n) return -1;
    ```
    
- Think in terms of **segments**, not total bloomed flowers.
    

---

## 🔸 Why other approach won’t work

- **Brute force days** → too slow (`10^9`).
    
- **Counting total bloomed flowers** → wrong (adjacency matters).
    
- **Greedy without Binary Search** → no way to guarantee minimum day.
    

---

## 🔸 Final Insight

This problem is about:

> **Finding the earliest time when a condition becomes true.**

Once you fix a day and ask  
“Can I make the bouquets or not?”  
Binary Search becomes unavoidable.

