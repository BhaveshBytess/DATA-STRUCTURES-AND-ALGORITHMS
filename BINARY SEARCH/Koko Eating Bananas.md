# Koko Eating Bananas (LeetCode 875)

## Problem Statement

Koko loves to eat bananas. There are `n` piles of bananas, where the `i-th` pile has `piles[i]` bananas.

The guards have gone and will return in `h` hours.

Koko can decide her **eating speed** `k` (bananas per hour). Each hour:

- She chooses **one pile** and eats up to `k` bananas from that pile.
    
- If the pile has fewer than `k` bananas, she eats the whole pile and does not eat more bananas that hour.
    

### Task

Return the **minimum integer eating speed `k`** such that Koko can eat **all bananas within `h` hours**.

---

## Constraints

- `1 <= piles.length <= 10^4`
    
- `1 <= piles[i] <= 10^9`
    
- `piles.length <= h <= 10^9`
    

---

## Key Observations

- The value we are searching for is **eating speed `k`**, not an index.
    
- If Koko can finish eating at speed `k`, then she can also finish at **any speed greater than `k`**.
    
- This creates a **monotonic decision function**, making Binary Search applicable.
    

---

## Binary Search Setup

### Answer Space

- Minimum speed: `1`
    
- Maximum speed: `max(piles)`
    

So the search range is:

```
[1 … max(piles)]
```

---

### Decision Function

For a fixed speed `k`, compute the total hours needed:

```
hours = sum( ceil(piles[i] / k) )
```

If:

```
hours <= h
```

then speed `k` is feasible.

This function is **monotonic**:

- Smaller `k` → more hours (possibly infeasible)
    
- Larger `k` → fewer hours (feasible)
    

---

## Boundary Being Searched

> **The minimum speed `k` such that Koko can finish eating within `h` hours.**

This is a classic **Binary Search on Answer** problem.

---

## C++ Implementation

```cpp
class Solution {
public:
    bool isPossible(vector<int>& piles, int k, int h) {
        long long hours = 0;
        for (int i = 0; i < piles.size(); i++) {
            // ceil(piles[i] / k) using integer math
            hours += (piles[i] + k - 1) / k;
        }
        return hours <= h;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isPossible(piles, mid, h)) {
                high = mid;      // mid could be the boundary
            } else {
                low = mid + 1;   // mid is too slow
            }
        }
        return low; // boundary speed
    }
};
```

---

## Time and Space Complexity

### Time Complexity

- `isPossible(k)` runs in **O(n)**, where `n = piles.length`
    
- Binary Search runs in **O(log M)**, where `M = max(piles)`
    

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

## Final Insight

> This problem is not about bananas — it is about **finding the smallest feasible value in a monotonic answer space**.

Once framed this way, Binary Search becomes inevitable and clean.

---

_(This document is the Phase 1 entry point for Binary Search on Answer.)_


---


# MINI-NOTE

## 🔹 Problem

Koko has `n` banana piles. Each hour she eats from **one pile** at speed `k` bananas/hour.  
If a pile has fewer than `k` bananas, she eats the entire pile in that hour.  
Guards return in `h` hours.  
👉 Find the **minimum integer speed `k`** such that all bananas are eaten within `h` hours.

---

## 🔹 Graph Type

Not a graph problem.  
This is a **Binary Search on Answer** problem (search space = values, not indices).

---

## 🔹 Technique

**Binary Search on Answer**

- Monotonic feasibility check (`isPossible(k)`).
    

---

## 🔹 Core Template

```cpp
low = minimum possible value
high = maximum possible value

while (low < high) {
    mid = low + (high - low) / 2;
    if (isPossible(mid)) {
        high = mid;      // keep boundary
    } else {
        low = mid + 1;   // discard impossible
    }
}
return low;
```

---

## 🔹 Pattern Tag

- Binary Search on Answer
    
- Minimum feasible value
    
- Monotonic decision function
    

---

## 🔸 Logic Summary

- The variable we optimize is **eating speed `k`**.
    
- For a fixed `k`, total hours required is:  
    `sum( ceil(piles[i] / k) )`.
    
- If total hours ≤ `h`, speed `k` is feasible.
    
- As `k` increases, required hours **never increase** → monotonic.
    
- Binary Search finds the **minimum `k`** that is feasible.
    

---

## 🔸 Trick

- **Ceil division without floating point**:
    
    ```cpp
    (piles[i] + k - 1) / k
    ```
    
- Search space is `[1 … max(piles)]`, **not indices**.
    
- Use `long long` for total hours to avoid overflow.
    

---

## 🔸 Why other approach won’t work

- **Greedy without Binary Search**: no direct way to jump to minimum speed.
    
- **Brute force on `k`**: too slow (`max(piles)` can be `10^9`).
    
- **Sorting / prefix sums**: irrelevant — time depends on division, not order.
    

---

## 🔸 Final Insight

This problem is **not about bananas**.  
It is about:

> **Finding the smallest value in an ordered answer space that satisfies a monotonic feasibility condition.**

Once you identify:

- the core variable (`k`),
    
- the feasibility check,
    
- and monotonicity,
    

Binary Search becomes unavoidable and clean.

---

If you want, next we can:

- 🔁 do **Minimum Days to Make Bouquets** (very similar pattern), or
    
- 🔁 do **Capacity to Ship Packages** (greedy + BS), or
    
- 🧪 I can **test you** by slightly modifying Koko and seeing if you can re-derive the logic.
    

Just tell me.