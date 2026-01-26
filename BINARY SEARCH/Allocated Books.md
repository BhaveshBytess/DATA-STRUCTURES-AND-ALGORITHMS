
## Problem Statement

You are given an array `pages[]` of length `n`, where `pages[i]` denotes the number of pages in the `i-th` book.

You are also given an integer `m`, representing the number of students.

### Rules

- Each student must be allocated **at least one book**.
    
- Each book must be allocated to **exactly one student**.
    
- Books must be allocated in a **contiguous manner**.
    

### Task

Allocate the books such that the **maximum number of pages assigned to any student is minimized**.

If allocation is **not possible**, return `-1`.

---

## Constraints

- `1 ≤ n ≤ 10^5`
    
- `1 ≤ pages[i] ≤ 10^5`
    
- `1 ≤ m ≤ n`
    

---

## Key Observations

- We are **not** minimizing the number of students.
    
- The number of students `m` is fixed.
    
- We are minimizing the **maximum pages assigned to a student**.
    
- If a certain maximum page limit `X` is feasible, then **any value greater than `X` is also feasible**.
    

This monotonic behavior makes the problem suitable for **Binary Search on Answer**.

---

## Binary Search Setup

### Core Variable

- `X` = maximum number of pages assigned to any student
    

This is the value we want to **minimize**.

---

### Answer Space

- Minimum possible value = `max(pages)`
    
    - A student must be able to take at least one full book.
        
- Maximum possible value = `sum(pages)`
    
    - One student takes all the books.
        

So the search space is:

```
[max(pages) … sum(pages)]
```

---

### Decision Function (`isPossible`)

For a fixed value `X`:

- Allocate books from left to right.
    
- Keep adding pages to the current student.
    
- If adding a book exceeds `X`, assign books to the next student.
    
- Count how many students are required.
    

If the number of students required is `<= m`, then `X` is feasible.

This decision function is **monotonic**:

- Smaller `X` → more students needed (possibly infeasible)
    
- Larger `X` → fewer students needed (feasible)
    

---

## Boundary Being Searched

> **The minimum value `X` such that books can be allocated to `m` students with maximum pages `<= X`.**

---

## C++ Implementation

```cpp
class Solution {
public:
    bool isPossible(vector<int>& pages, int m, int maxPages) {
        int students = 1;
        int currPages = 0;

        for (int p : pages) {
            if (currPages + p <= maxPages) {
                currPages += p;
            } else {
                students++;
                currPages = p;
            }
        }
        return students <= m;
    }

    int allocateBooks(vector<int>& pages, int m) {
        int n = pages.size();
        if (m > n) return -1;

        int low = *max_element(pages.begin(), pages.end());
        int high = 0;
        for (int p : pages) high += p;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isPossible(pages, m, mid)) {
                high = mid;
            } else {
                low = mid + 1;
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
    
- Binary Search: **O(log S)** where `S = sum(pages)`
    

```
Total Time = O(n log S)
```

---

### Space Complexity

```
O(1)
```

---

## Common Mistakes

- Forgetting the `m > n` impossible case
    
- Using `min(pages)` as lower bound
    
- Counting splits instead of students
    
- Resetting current pages to `0` instead of current book
    

---

## Final Insight

> This problem is not about book distribution — it is about **minimizing the maximum load under contiguous constraints**.

Once framed as a feasibility problem over a candidate maximum, Binary Search becomes inevitable.

---

_(Phase 2 — Advanced Binary Search on Answer)_


---


# MINI-NOTE :

## 🔹 Problem

Given an array `pages[]` and an integer `m` (students), allocate books such that:

- Each student gets **at least one book**
    
- Books are allocated **contiguously**
    
- Each book goes to exactly one student
    

The goal is to **minimize the maximum number of pages** assigned to any student.  
If allocation is impossible, return `-1`.

---

## 🔹 Graph Type

Not a graph problem.  
This is **Binary Search on Answer**.

---

## 🔹 Technique

**Binary Search on Answer**

- Greedy feasibility check (prefix accumulation).
    

---

## 🔹 Core Template

```cpp
low = minimum feasible maximum
high = maximum feasible maximum

while (low < high) {
    mid = low + (high - low) / 2;
    if (isPossible(mid)) {
        high = mid;      // try smaller maximum
    } else {
        low = mid + 1;   // need larger maximum
    }
}
return low;
```

---

## 🔹 Pattern Tag

- Binary Search on Answer
    
- Load balancing
    
- Greedy + monotonic feasibility
    

---

## 🔸 Logic Summary

- The variable we optimize is **maximum pages per student `X`**.
    
- Fix a candidate `X`.
    
- Allocate books from left to right.
    
- Add pages to the current student until exceeding `X`.
    
- On overflow, move to the next student.
    
- Count students required.
    
- If students `<= m`, then `X` is feasible.
    
- Increasing `X` never increases students required → monotonic.
    

---

## 🔸 Trick

- Lower bound = **`max(pages)`** (a student must hold the largest book).
    
- Upper bound = **`sum(pages)`** (one student takes all).
    
- Always start with **`students = 1`**.
    
- On overflow, reset current pages to **current book**, not `0`.
    

---

## 🔸 Why other approach won’t work

- Trying all allocations → exponential.
    
- DP solutions → unnecessary for this constraint.
    
- Counting splits instead of students → off-by-one errors.
    

---

## 🔸 Final Insight

> Allocate Books is structurally identical to **Split Array Largest Sum**.

The problem is about **minimizing the maximum load under contiguous constraints**, not about where to split.

---

**Phase:** Advanced Binary Search (Phase 2)