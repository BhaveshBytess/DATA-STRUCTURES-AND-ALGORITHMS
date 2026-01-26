
## Problem Statement

You are given an integer array `nums` and an integer `k`.

Split the array into **`k` or fewer non-empty contiguous subarrays**.

The **largest sum** among these subarrays is called the **score** of the split.

### Task

Return the **minimum possible score** after splitting the array.

---

## Constraints

- `1 <= nums.length <= 1000`
    
- `0 <= nums[i] <= 10^6`
    
- `1 <= k <= nums.length`
    

---

## Key Observations

- We are **not** minimizing the number of subarrays.
    
- We are minimizing the **maximum subarray sum (score)**.
    
- If a certain score `X` is achievable, then **any score larger than `X` is also achievable**.
    
- This creates a **monotonic feasibility function**, enabling Binary Search on Answer.
    

---

## Binary Search Setup

### Core Variable

- `X` = maximum allowed subarray sum (score)
    

This is the value we want to **minimize**.

---

### Answer Space

- Minimum possible score = `max(nums)`
    
    - A subarray must contain at least one element.
        
    - The largest element must fit inside some subarray.
        
- Maximum possible score = `sum(nums)`
    
    - Entire array as one subarray.
        

So the search space is:

```
[max(nums) … sum(nums)]
```

---

### Decision Function (`isPossible`)

For a fixed score `X`:

- Traverse the array from left to right.
    
- Greedily accumulate elements into the current subarray.
    
- If adding the next element causes the sum to exceed `X`:
    
    - Start a new subarray.
        
    - Increment the subarray count.
        

If the total number of subarrays formed is `<= k`, then score `X` is feasible.

This decision function is **monotonic**:

- Smaller `X` → more subarrays required (possibly infeasible)
    
- Larger `X` → fewer subarrays required (feasible)
    

---

## Boundary Being Searched

> **The minimum score `X` such that the array can be split into `k` or fewer subarrays with maximum sum `<= X`.**

This is a classic **Binary Search on Answer** problem.

---

## C++ Implementation

```cpp
class Solution {
public:
    bool isPossible(vector<int>& nums, int k, int score) {
        int subarrays = 1;  // at least one subarray always exists
        int currSum = 0;

        for (int x : nums) {
            if (currSum + x <= score) {
                currSum += x;
            } else {
                subarrays++;
                currSum = x;
            }
        }
        return subarrays <= k;
    }

    int splitArray(vector<int>& nums, int k) {
        int low = *max_element(nums.begin(), nums.end());
        int high = 0;
        for (int x : nums) high += x;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isPossible(nums, k, mid)) {
                high = mid;      // try smaller score
            } else {
                low = mid + 1;   // need larger score
            }
        }
        return low;
    }
};
```

---

## Time and Space Complexity

### Time Complexity

- `isPossible(X)` runs in **O(n)**
    
- Binary Search runs in **O(log S)**, where `S = sum(nums)`
    

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

- Counting splits instead of subarrays
    
- Resetting current sum to `0` instead of current element
    
- Using invalid lower bounds (less than max element)
    
- Forgetting that one subarray always exists
    

---

## Final Insight

> This problem is about **controlling the maximum allowed chunk size**, not about where to split.

Once framed as a feasibility question over a candidate score, Binary Search becomes inevitable.

---

_(This document completes Phase 2 — Problem 1 of Binary Search on Answer.)_


---


# MINI-NOTE :


## 🔹 Problem

Given an array `nums` and an integer `k`, split the array into **k or fewer non-empty contiguous subarrays**.  
The **score** of a split is the **maximum subarray sum** among all subarrays.

👉 Find the **minimum possible score**.

---

## 🔹 Graph Type

Not a graph problem.  
This is **Binary Search on Answer** (searching over a constraint value).

---

## 🔹 Technique

**Binary Search on Answer**

- Greedy feasibility check (prefix accumulation).
    

---

## 🔹 Core Template

```cpp
low = minimum valid score
high = maximum valid score

while (low < high) {
    mid = low + (high - low) / 2;
    if (isPossible(mid)) {
        high = mid;      // keep boundary
    } else {
        low = mid + 1;   // need larger score
    }
}
return low;
```

---

## 🔹 Pattern Tag

- Binary Search on Answer
    
- Constraint minimization
    
- Greedy + monotonic feasibility
    

---

## 🔸 Logic Summary

- The variable we optimize is **score `X`** (maximum allowed subarray sum).
    
- Fix a candidate score `X`.
    
- Greedily build subarrays left to right.
    
- If adding an element exceeds `X`, start a **new subarray**.
    
- Count how many subarrays are formed.
    
- If subarrays `<= k`, then `X` is feasible.
    
- Larger `X` → fewer subarrays → feasibility never decreases.
    

---

## 🔸 Trick

- Lower bound is **`max(nums)`**, not smaller.
    
- Upper bound is **`sum(nums)`**.
    
- Always start with **`subarrays = 1`** (one subarray always exists).
    
- On overflow, reset current sum to **current element**, not `0`.
    

---

## 🔸 Why other approach won’t work

- Trying all split positions → exponential.
    
- DP without pruning → too slow.
    
- Counting splits instead of subarrays → off-by-one bugs.
    

---

## 🔸 Final Insight

> This problem is about **controlling the maximum allowed chunk**, not choosing split points.

Binary Search works because relaxing the allowed chunk size only makes splitting easier.

---

**Phase:** Advanced Binary Search (Phase 2)