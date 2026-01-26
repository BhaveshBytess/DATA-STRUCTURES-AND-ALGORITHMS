
## Problem Statement

You are given an integer array `weights`, where `weights[i]` represents the weight of the `i-th` package.

A ship transports these packages **in the given order** from one port to another within `D` days.

### Rules

- Each day, you load the ship with packages in order.
    
- You may load as many packages as you want per day **as long as the total weight does not exceed the ship’s capacity**.
    
- You **cannot split** a package.
    
- Packages **must be shipped in order**.
    

### Task

Return the **minimum ship capacity** required to ship all the packages within `D` days.

---

## Constraints

- `1 <= weights.length <= 5 * 10^4`
    
- `1 <= weights[i] <= 500`
    
- `1 <= D <= weights.length`
    

---

## Key Observations

- We are **not** optimizing days — days are fixed.
    
- We are optimizing the **ship capacity**.
    
- If a certain capacity `C` is sufficient, then **any capacity greater than `C` will also be sufficient**.
    
- This creates a **monotonic feasibility function**, making Binary Search applicable.
    

---

## Binary Search Setup

### Core Variable

- `C` = ship capacity (value we want to minimize)
    

---

### Answer Space

- Minimum possible capacity = `max(weights)`
    
    - The ship must be able to carry the heaviest package.
        
- Maximum possible capacity = `sum(weights)`
    
    - Ship everything in one day.
        

So the search space is:

```
[max(weights) … sum(weights)]
```

---

### Decision Function (`isPossible`)

For a fixed capacity `C`:

- Simulate the shipping process day by day.
    
- Load packages in order until adding the next package exceeds capacity.
    
- When capacity is exceeded:
    
    - Count one day
        
    - Start a new day with the current package
        

If the total number of days used is `<= D`, then capacity `C` is feasible.

This decision function is **monotonic**:

- Smaller capacity → more days needed (possibly infeasible)
    
- Larger capacity → fewer or equal days needed (feasible)
    

---

## Boundary Being Searched

> **The minimum ship capacity `C` such that all packages can be shipped within `D` days.**

This is a classic **Binary Search on Answer** problem.

---

## C++ Implementation

```cpp
class Solution {
public:
    bool isPossible(vector<int>& weights, int D, int capacity) {
        int days = 1;
        int currLoad = 0;

        for (int i = 0; i < weights.size(); i++) {
            if (currLoad + weights[i] <= capacity) {
                currLoad += weights[i];
            } else {
                days++;
                currLoad = weights[i];
            }
        }
        return days <= D;
    }

    int shipWithinDays(vector<int>& weights, int D) {
        int low = *max_element(weights.begin(), weights.end());
        int high = 0;
        for (int w : weights) high += w;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isPossible(weights, D, mid)) {
                high = mid;      // try smaller capacity
            } else {
                low = mid + 1;   // need larger capacity
            }
        }
        return low;
    }
};
```

---

## Time and Space Complexity

### Time Complexity

- `isPossible(C)` runs in **O(n)**, where `n = weights.length`
    
- Binary Search runs in **O(log S)**, where `S = sum(weights)`
    

```
Total Time = O(n log S)
```

---

### Space Complexity

- No extra data structures used
    

```
Space = O(1)
```

---

## Common Mistakes

- Using `min(weights)` as the lower bound instead of `max(weights)`
    
- Counting total weight instead of simulating day-by-day loading
    
- Forgetting that packages cannot be split
    
- Treating this as an index-based Binary Search
    

---

## Final Insight

> This problem is about finding the **smallest capacity that makes shipping possible**, not about scheduling or optimization tricks.

Once feasibility is framed as a YES/NO question over capacity, Binary Search becomes inevitable.

---

_(This document completes Phase 1 — Problem 3 of Binary Search on Answer.)_


----


# MINI-NOTE :

## 🔹 Problem

You are given an array `weights` where `weights[i]` is the weight of the `i-th` package.  
Packages must be shipped **in order** within `D` days.

Each day:

- You can load packages until total weight exceeds ship capacity.
    
- You **cannot split** packages.
    

👉 Find the **minimum ship capacity** required to ship all packages within `D` days.

---

## 🔹 Graph Type

Not a graph problem.  
This is a **Binary Search on Answer** problem (searching over capacity values).

---

## 🔹 Technique

**Binary Search on Answer**

- Greedy simulation for feasibility (`isPossible(capacity)`).
    

---

## 🔹 Core Template

```cpp
low = minimum feasible value
high = maximum feasible value

while (low < high) {
    mid = low + (high - low) / 2;
    if (isPossible(mid)) {
        high = mid;      // try smaller capacity
    } else {
        low = mid + 1;   // need more capacity
    }
}
return low;
```

---

## 🔹 Pattern Tag

- Binary Search on Answer
    
- Minimum feasible value
    
- Greedy feasibility check
    
- Order-preserving constraint
    

---

## 🔸 Logic Summary

- The variable we optimize is **ship capacity `C`**.
    
- Days `D` are fixed.
    
- For a fixed capacity:
    
    - Load packages in order.
        
    - If adding a package exceeds capacity → start a new day.
        
- Count how many days are required.
    
- If required days `<= D`, then capacity is feasible.
    
- Increasing capacity **never makes things worse** → monotonic.
    

---

## 🔸 Trick

- Lower bound of search space is **`max(weights)`**, not `min`.
    
- Upper bound is **`sum(weights)`** (ship everything in one day).
    
- Start `days = 1` to explicitly represent the first day.
    
- Simulate reality directly; don’t “fix” day counts after the loop.
    

---

## 🔸 Why other approach won’t work

- **Brute forcing capacity** → too slow.
    
- **Sorting weights** → breaks order constraint.
    
- **Greedy without Binary Search** → no guarantee of minimum capacity.
    
- **Counting total weight only** → ignores daily capacity limits.
    

---

## 🔸 Final Insight

This problem is about:

> **Finding the smallest capacity that makes shipping possible.**

Once you frame the question as  
“Can I ship everything in `D` days with capacity `C`?”  
Binary Search becomes inevitable.

---
