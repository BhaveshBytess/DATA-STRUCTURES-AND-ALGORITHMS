

## Problem Statement

You are given an integer array `candles`, where `candles[i]` represents the number of candles in the `i-th` pile.  
You are also given an integer `k`, representing the number of children.

### Rules

- Each child must receive **the same number of candles**.
    
- Candles for a child must come from **a single pile**.
    
- A pile can be split among multiple children.
    
- Some piles may remain unused.
    

### Task

Return the **maximum number of candles** each child can receive.  
If it is **not possible** to give at least one candle to every child, return `0`.

---

## Constraints

- `1 <= candles.length <= 10^5`
    
- `1 <= candles[i] <= 10^7`
    
- `1 <= k <= 10^9`
    

---

## Key Observations

- We are **not** minimizing or maximizing piles or children.
    
- We are maximizing **candles per child** (equal for all children).
    
- For a fixed value `x` (candles per child), feasibility depends on how many children can be served.
    
- If a value `x` is feasible, then **any smaller value** is also feasible.
    

This creates a **monotonic feasibility function** suitable for **Binary Search on Answer**.

---

## Binary Search Setup

### Core Variable

- `x` = number of candles given to each child
    

This is the value we want to **maximize**.

---

### Answer Space

- Minimum possible value = `1`
    
- Maximum possible value = `max(candles)`
    

Reasoning:

- Giving fewer than 1 candle per child is invalid.
    
- A child cannot receive more candles than the largest pile.
    

So the search space is:

```
[1 … max(candles)]
```

---

### Decision Function (`isPossible`)

For a fixed value `x`:

- From a pile with `candles[i]`, you can serve `candles[i] / x` children.
    
- Sum this across all piles to compute how many children can be served.
    
- If the total is **greater than or equal to `k`**, then `x` is feasible.
    

To improve performance and safety, stop early once `k` children are reached.

The function is **monotonic**:

- Smaller `x` → more children can be served (feasible)
    
- Larger `x` → fewer children can be served (may become infeasible)
    

---

## Boundary Being Searched

> **The maximum value `x` such that it is possible to serve at least `k` children with `x` candles each.**

---

## C++ Implementation

```cpp
class Solution {
public:
    bool isPossible(vector<int>& candles, long long k, int x) {
        long long children = 0;
        for (int c : candles) {
            children += c / x;
            if (children >= k) return true; // early stop
        }
        return false;
    }

    int maximumCandles(vector<int>& candles, long long k) {
        long long total = 0;
        int high = 0;
        for (int c : candles) {
            total += c;
            high = max(high, c);
        }

        if (total < k) return 0; // not even 1 candle per child

        int low = 1;
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (isPossible(candles, k, mid)) {
                ans = mid;      // feasible, try larger
                low = mid + 1;
            } else {
                high = mid - 1; // infeasible, try smaller
            }
        }
        return ans;
    }
};
```

---

## Time and Space Complexity

### Time Complexity

- Feasibility check: **O(n)**
    
- Binary Search: **O(log M)** where `M = max(candles)`
    

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

- Using `total_children <= k` instead of `>= k`
    
- Searching for the smallest feasible value instead of the largest
    
- Forgetting early stop when `children >= k`
    
- Using sum of candles as upper bound (unnecessary)
    

---

## Final Insight

> This problem reverses the usual boundary: we search for the **largest feasible value**, not the smallest.

Once you frame the question as “how many children can I serve with `x` candles each?”, Binary Search becomes natural.

---

_(Phase 3 — Binary Search on Answer)_


---

# MINI-NOTE :

🔹 **Problem**  
Maximum Candles (Candies) Allocated to K Children

🔹 **Graph Type**  
Binary Search on Answer (Reverse Monotonic)

🔹 **Technique**  
Binary Search on maximum feasible value

🔹 **Core Template**

- Identify core variable `x` (candles per child)
    
- Define `isPossible(x)` as: can we serve **at least k children**?
    
- Search for the **largest true** value
    

🔹 **Pattern Tag**  
#BinarySearchOnAnswer #LargestTrue #ReverseMonotonic

🔸 **Logic Summary**  
For a given `x`, each pile contributes `candles[i] / x` children.  
If total children ≥ `k`, then `x` is feasible.  
As `x` increases, feasibility decreases → reverse monotonic.

🔸 **Trick**  
Stop early inside `isPossible` once children ≥ `k`.

🔸 **Why other approach won’t work**

- Linear search over `x` is too slow
    
- Greedy per child fails because piles are independent
    
- Prefix/suffix tricks don’t apply
    

🔸 **Boundary**  
Largest `x` such that `isPossible(x) == true`

🔸 **Binary Search Moves**

- If `true` → store answer, move `low = mid + 1`
    
- If `false` → move `high = mid - 1`
    

🔸 **Final Insight**  
If feasibility goes from **true → false**, always search for the **largest true**.

---

_(Phase 3 — Binary Search on Answer)_
