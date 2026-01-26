# Find the Smallest Divisor Given a Threshold (LeetCode 1283)

## Problem Statement

You are given an integer array `nums` and an integer `threshold`.

You will choose a **positive integer divisor `d`**. For each element in `nums`, divide it by `d` and **round the result up** to the nearest integer.

Formally, compute:

```
sum = ceil(nums[0] / d) + ceil(nums[1] / d) + ... + ceil(nums[n-1] / d)
```

### Task

Return the **smallest positive integer divisor `d`** such that the resulting sum is **less than or equal to `threshold`**.

---

## Constraints

- `1 <= nums.length <= 5 * 10^4`
    
- `1 <= nums[i] <= 10^6`
    
- `nums.length <= threshold <= 10^6`
    

---

## Key Observations

- We are **not** minimizing the sum.
    
- The sum is constrained by `threshold`.
    
- We are minimizing the **divisor `d`**.
    
- For a fixed `d`, the computed sum is deterministic.
    
- If a divisor `d` works, then **any larger divisor will also work**.
    

This monotonic behavior allows **Binary Search on Answer**.

---

## Binary Search Setup

### Core Variable

- `d` = divisor used to divide each element
    

This is the value we want to **minimize**.

---

### Answer Space

- Minimum possible divisor = `1`
    
- Maximum possible divisor = `max(nums)`
    

Reason:

- Dividing by `1` gives the maximum possible sum.
    
- Dividing by any value larger than `max(nums)` would make all terms equal to `1`, which is unnecessary.
    

So the search space is:

```
[1 … max(nums)]
```

---

### Decision Function (`isPossible`)

For a fixed divisor `d`:

- Compute the sum of `ceil(nums[i] / d)` for all elements.
    
- If the sum is `<= threshold`, then divisor `d` is feasible.
    

To compute ceiling division safely in integers:

```
ceil(x / d) = (x + d - 1) / d
```

The function is **monotonic**:

- Smaller `d` → larger sum (possibly infeasible)
    
- Larger `d` → smaller sum (feasible)
    

---

## Boundary Being Searched

> **The smallest divisor `d` such that the computed sum is `<= threshold`.**

---

## C++ Implementation

```cpp
class Solution {
public:
    bool isPossible(vector<int>& nums, int threshold, int d) {
        int sum = 0;
        for (int x : nums) {
            sum += (x + d - 1) / d;  // ceil(x / d)
            if (sum > threshold) return false; // early stop
        }
        return true;
    }

    int smallestDivisor(vector<int>& nums, int threshold) {
        int low = 1;
        int high = *max_element(nums.begin(), nums.end());

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isPossible(nums, threshold, mid)) {
                high = mid;     // try smaller divisor
            } else {
                low = mid + 1;  // need larger divisor
            }
        }
        return low;
    }
};
```

---

## Time and Space Complexity

### Time Complexity

- Feasibility check: **O(n)**
    
- Binary Search: **O(log M)** where `M = max(nums)`
    

```
Total Time = O(n log M)
```

---

### Space Complexity

```
O(1)
```

---

## Common Mistakes

- Using floating-point `ceil()` with integer division
    
- Forgetting early exit when sum exceeds threshold
    
- Using an invalid upper bound for divisor
    

---

## Final Insight

> This problem is about **controlling the divisor to regulate the total cost**.

Once framed as a monotonic feasibility problem over `d`, Binary Search becomes straightforward.

---

_(Phase 3 — Binary Search on Answer)_

---


# MINI-NOTE 

## 🔹 Problem

Given an array `nums` and an integer `threshold`, find the **smallest positive integer divisor `d`** such that:

```
ceil(nums[0]/d) + ceil(nums[1]/d) + ... + ceil(nums[n-1]/d) <= threshold
```

---

## 🔹 Graph Type

Not a graph problem.  
This is **Binary Search on Answer (Phase 3)**.

---

## 🔹 Technique

**Binary Search on Answer** + **Mathematical monotonic constraint**

---

## 🔹 Core Template

```cpp
low = 1;
high = max(nums);

while (low < high) {
    mid = low + (high - low) / 2;
    if (isPossible(mid)) {
        high = mid;      // shrink right boundary
    } else {
        low = mid + 1;   // need larger divisor
    }
}
return low;
```

---

## 🔹 Pattern Tag

- Binary Search on Answer
    
- Monotonic mathematical function
    
- Threshold feasibility
    

---

## 🔸 Logic Summary

- Variable: **divisor `d`**.
    
- Fix `d`, compute `sum = Σ ceil(nums[i] / d)`.
    
- If `sum <= threshold`, divisor `d` works.
    
- If not, increase `d`.
    
- Smaller `d` → larger sum (false region).
    
- Larger `d` → smaller sum (true region).
    
- Find smallest `d` with `sum <= threshold`.
    

---

## 🔸 Trick

- Use integer-safe ceiling: `(x + d - 1) / d`.
    
- Add **early exit** when `sum > threshold`.
    
- Search space = `[1, max(nums)]`.
    
- Function is monotonic.
    

---

## 🔸 Why other approach won’t work

- Linear scan → O(max(nums)) → too slow.
    
- Floating-point division → rounding errors.
    
- DP → unnecessary for monotonic numeric search.
    

---

## 🔸 Final Insight

> Smaller divisors inflate the total; larger divisors relax it.

We simply **binary search the smallest divisor** that keeps the total within `threshold`.

---

**Phase:** 3 — Binary Search on Answer (Mathematical Constraint)