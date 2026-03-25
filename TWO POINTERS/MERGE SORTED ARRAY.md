
## 🔹 Problem

You are given two sorted integer arrays:

* `nums1` of size `m + n`, where first `m` elements are valid and last `n` elements are empty (0 placeholders)
* `nums2` of size `n`

Merge `nums2` into `nums1` as one sorted array **in-place**.

---

## 🔹 Mathematical / Structural Model

We need to merge two sorted sequences:

[
A[0…m-1], $\quad B[0…n-1]$
]

Into:

[
A[0…m+n-1]
]

Without using extra space.

---

## 🔹 First Principles Understanding

Key constraint:

> nums1 already contains valid data in the front.

If we write from the front → we overwrite unprocessed values.

So we must find a **safe write region**.

---

## 🔹 Core Insight

The **back of nums1 is empty**.

So:

> We fill nums1 from the back using the largest remaining elements.

---

## 🔹 Invariant

```id="inv_merge"
Everything from index k+1 to m+n-1 in nums1 is already correctly placed and sorted.
```

---

## 🔹 Pointer Definitions

```id="ptr_merge"
i = m - 1      → last valid element in nums1
j = n - 1      → last element in nums2
k = m + n - 1  → write position (end of nums1)
```

---

## 🔹 Decision Rule

At each step:

```id="rule_merge"
Compare nums1[i] and nums2[j]
Place the larger element at nums1[k]
```

---

### Why larger?

Because:

* We are filling from the back
* Largest element must go at position k

---

### Why not smaller?

Placing smaller element at back breaks sorted order.

---

## 🔹 Stop Condition

```id="stop_merge"
while (i >= 0 && j >= 0)
```

---

## 🔹 Edge Case Handling

After loop:

```id="edge_merge"
If nums2 still has elements → copy them
If nums1 has elements → do nothing
```

---

### Why no need to copy nums1?

Because:

> Remaining nums1 elements are already in correct sorted positions.

---

## 🔹 Correct C++ Implementation

```cpp id="code_merge"
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;

        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }

        while (j >= 0) {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
};
```

---

## 🔹 Time Complexity

[
O(m + n)
]

Each element processed once.

---

## 🔹 Space Complexity

[
O(1)
]

In-place.

---

## 🔹 Why Backward Merge Works

* Avoids overwriting unprocessed elements
* Uses empty space efficiently
* Maintains sorted order

---

## 🔹 Why Forward Merge Fails

* Overwrites elements before they are used
* Destroys required data

---

## 🔹 Pattern Recognition

This problem belongs to:

> **Two Pointer — Two Sequence Synchronization**

Key idea:

> Compare heads/tails of two streams and advance the one that wins.

---

## 🔹 Final Insight

This problem is not about merging arrays.

It is about:

> Safely placing elements without losing unprocessed information.

---


# 📝 MINI NOTES — Merge Sorted Array

---

🔹 **Problem**  
Merge two sorted arrays (`nums1`, `nums2`) into `nums1` in-place.

---

🔹 **Graph Type**  
Array (Two Sequence Processing)

---

🔹 **Technique**  
Two Pointers (Backward Merge)  
Stream Synchronization

---

🔹 **Core Template**

```cpp
int i = m - 1;          // last valid in nums1
int j = n - 1;          // last in nums2
int k = m + n - 1;      // write position

while (i >= 0 && j >= 0) {
    if (nums1[i] > nums2[j]) {
        nums1[k--] = nums1[i--];
    } else {
        nums1[k--] = nums2[j--];
    }
}

while (j >= 0) {
    nums1[k--] = nums2[j--];
}
```

---

🔹 **Pattern Tag**  
Two Stream Merge  
Backward Filling  
Safe Write Zone

---

🔸 **Logic Summary**

- nums1 has empty space at the back
    
- Fill from the back to avoid overwriting
    
- Always place the **largest remaining element**
    
- Compare `nums1[i]` and `nums2[j]`
    
- Move the pointer of the chosen element
    

---

🔸 **Invariant**

```text
Everything from k+1 → end is already sorted and final.
```

---

🔸 **Decision Rule**

- Compare `nums1[i]` and `nums2[j]`
    
- Place larger at `k`
    
- Move corresponding pointer
    

---

🔸 **Stop Condition**

```text
Main loop ends when j < 0 OR i < 0
```

But correctness depends on:

```text
nums2 must be fully processed
```

---

🔸 **Edge Case**

- If nums2 has remaining elements → copy them
    
- If nums1 has remaining → do nothing
    

---

🔸 **Why Backward?**

- Front contains valid data → unsafe to overwrite
    
- Back is empty → safe write zone
    

---

🔸 **Why No Copy for nums1?**

Remaining nums1 elements are already in correct position.

---

🔸 **Common Mistakes**

❌ Using `j = m - 1`  
❌ Using `k = m + m - 1`  
❌ Forgetting `i-- / j--`  
❌ Using `if (j > 0)` instead of `while (j >= 0)`  
❌ Trying to merge from front

---

🔸 **Final Insight**

This is not merging logic.

This is:

> **Preserving unprocessed data while filling result space**

---

✅ Phase 4 — First Pattern Locked

---

Next:

👉 Intersection of Two Arrays  
👉 Is Subsequence

Say **“Next Problem”** and we continue the grind.