
## Problem Statement (LeetCode Style)

We are playing a guessing game.

I pick a number between `1` and `n`.

You must guess the number.

You have access to an API:

```cpp
int guess(int num);
```

It returns:

- `-1` → Your guess is **higher** than the picked number
    
- `1` → Your guess is **lower** than the picked number
    
- `0` → Your guess is **correct**
    

Return the picked number.

---

## Constraints

- `1 <= n <= 2^31 - 1`
    
- Exactly one correct number exists
    

---

# Key Observations

## 1️⃣ Core Variable

`num` — the number we are guessing.

We are searching for the exact value that makes:

```
guess(num) == 0
```

---

## 2️⃣ Answer Space

```
[1 … n]
```

---

## 3️⃣ Nature of the Decision

Unlike boundary problems, this is an **exact match search**.

The API gives directional feedback:

- If guess(mid) == -1 → shrink right
    
- If guess(mid) == 1 → shrink left
    
- If guess(mid) == 0 → return immediately
    

This is classical binary search.

---

# Binary Search Strategy

We maintain:

> The picked number is always inside `[low, high]`.

When guess(mid) == -1 (too high):

- Eliminate mid
    
- Search left half
    

When guess(mid) == 1 (too low):

- Eliminate mid
    
- Search right half
    

When guess(mid) == 0:

- Return mid immediately
    

---

# Correct Template

We use:

```
while (low <= high)
```

Because this is **exact search**, not boundary preservation.

---

# C++ Implementation

```cpp
class Solution {
public:
    int guessNumber(int n) {
        int low = 1;
        int high = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            int result = guess(mid);

            if (result == 0)
                return mid;
            else if (result == -1)
                high = mid - 1;  // discard mid
            else
                low = mid + 1;   // discard mid
        }

        return -1; // guaranteed not to happen
    }
};
```

---

# Why We Use `<=` Here

Because we **discard mid completely** when wrong:

```
high = mid - 1
low = mid + 1
```

The search space strictly shrinks each iteration.

No boundary preservation required.

---

# Time Complexity

```
O(log n)
```

---

# Space Complexity

```
O(1)
```

---


# MONI-NOTE : 


🔹 Problem  
You must guess a number between 1 and n using API:

int guess(int num)

Returns:

- -1 → guess is too high
    
- 1 → guess is too low
    
- 0 → correct
    

Return the picked number.

---

🔹 Graph Type  
Binary Search (Exact Search)

---

🔹 Technique  
Classic binary search with directional feedback

---

🔹 Core Template

Answer Space: [1 … n]

low = 1  
high = n

while (low <= high):  
mid = low + (high - low) / 2

```
result = guess(mid)

if result == 0:
    return mid
else if result == -1:
    high = mid - 1
else:
    low = mid + 1
```

---

🔹 Pattern Tag  
#BinarySearch  
#ExactSearch  
#DirectionalFeedback

---

🔸 Logic Summary  
We eliminate mid completely when incorrect.  
Search space strictly shrinks every iteration.  
No boundary preservation is required.

---

🔸 Trick

- Use while (low <= high)
    
- Always discard mid when wrong
    
- Avoid overflow in mid calculation
    

---

🔸 Why Other Approach Won’t Work  
Using boundary-style search (low < high with high = mid) is incorrect because we are not preserving candidates — we are searching for exact match.

---

🔸 Boundary  
None — this is exact-match search, not smallest true or largest false.

---

🔸 Final Insight  
This problem reinforces the difference between:  
Boundary search (keep mid) and Exact search (discard mid).

---

(Phase 5 – Exact Search Reinforcement)