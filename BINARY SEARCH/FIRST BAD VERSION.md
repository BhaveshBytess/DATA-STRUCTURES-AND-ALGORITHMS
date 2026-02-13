

## Problem Statement (LeetCode Style)

You are given an API:

```cpp
bool isBadVersion(int version);
```

You are given an integer `n` representing versions from `1` to `n`.

Versions are sequential. Once a bad version appears, all later versions are also bad.

Example:

```
Good Good Good Bad Bad Bad
1    2    3    4   5   6
```

Return the **first bad version**.

---

## Constraints

- `1 <= n <= 2^31 - 1`
    
- `isBadVersion(version)` is monotonic:
    

```
false false false true true true
```

---

# Key Observations

## 1️⃣ Core Variable

`version`

We are searching for the first index where:

```
isBadVersion(version) == true
```

---

## 2️⃣ Answer Space

```
[1 … n]
```

---

## 3️⃣ Monotonic Property

The function transitions exactly once:

```
false false false true true true
```

So this is a classic:

> **Smallest True (Boundary Search)**

---

# Binary Search Strategy

We maintain the invariant:

> The first bad version is always inside `[low, high]`.

When `mid` is bad:

- The answer could be `mid` or earlier
    
- So we keep `mid`
    

When `mid` is good:

- The answer must be after `mid`
    
- So we discard `mid`
    

---

# Correct Template

We use:

```
while (low < high)
```

Because we are performing boundary search (not exact search).

---

# C++ Implementation

```cpp
class Solution {
public:
    int firstBadVersion(int n) {
        int low = 1;
        int high = n;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isBadVersion(mid))
                high = mid;          // keep mid
            else
                low = mid + 1;       // discard mid
        }

        return low;
    }
};
```

---

# Why NOT use `while (low <= high)`?

Because we are keeping `mid` when bad:

```
high = mid
```

If we used `<=`, it could lead to infinite loop when `low == high`.

Boundary search requires:

```
while (low < high)
```

---

# Time Complexity

Binary Search performs:

```
O(log n)
```

Each step calls `isBadVersion()` once.

---

# Space Complexity

```
O(1)
```

---

# Common Mistakes

- Using `high = mid - 1` (loses candidate)
    
- Using `while (low <= high)` with boundary logic
    
- Forgetting overflow-safe mid calculation
    

---

# Final Insight

This problem tests **invariants and boundary thinking**, not difficulty.

It is the purest example of:

> Smallest True Binary Search

---

(Phase 5 – Boundary Search Mastery)


---

# MINI -NOTE : 

🔹 Problem  
Given versions 1 to n and API isBadVersion(version), where once a version is bad all later versions are bad.  
Return the first bad version.

---

🔹 Graph Type  
Binary Search on Answer (Boundary Search)

---

🔹 Technique  
Smallest True Binary Search

---

🔹 Core Template

Answer Space: [1 … n]

Monotonic:  
false false false true true true

Binary Search:

low = 1  
high = n

while (low < high):  
mid = low + (high - low) / 2

```
if isBadVersion(mid):
    high = mid        // keep mid
else:
    low = mid + 1     // discard mid
```

return low

---

🔹 Pattern Tag  
#BinarySearch  
#SmallestTrue  
#BoundarySearch  
#Invariant

---

🔸 Logic Summary  
If mid is bad, first bad is in [low, mid].  
If mid is good, first bad is in [mid+1, high].  
Always keep the candidate when condition is true.

---

🔸 Trick

- Use while (low < high)
    
- Never use high = mid - 1 here
    
- Boundary search keeps mid when true
    

---

🔸 Why Other Approach Won’t Work  
Using while (low <= high) with high = mid may cause infinite loop.  
Using high = mid - 1 may discard the correct answer.

---

🔸 Boundary  
Smallest index where isBadVersion(version) == true.

---

🔸 Final Insight  
This problem tests invariant discipline, not difficulty.  
It is the cleanest example of Smallest True boundary search.

---

(Phase 5 – Interview Edge Case Mastery)