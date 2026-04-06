
## 🔹 Problem

Given an integer array `nums` and an integer `k`, return an array `result` such that:

> `result[i]` is the **first negative number** in the subarray `nums[i … i + k - 1]`.

If no negative number exists in that window, return `0`.

---

## 🔹 First Principles Understanding

We are NOT asked to:

- scan each window fully ❌
    
- recompute negatives repeatedly ❌
    

We are asked to:

> Efficiently track the **first negative element inside a moving window**

---

## 🔹 Core Insight

We need a structure that:

```text
1. Maintains order
2. Gives first negative in O(1)
3. Supports removal when window slides
```

👉 This leads to using a **Queue (or Deque)**

---

## 🔹 Window Definition

```text
Window [L … R] represents a contiguous subarray
```

We process when:

```text
R - L + 1 == k
```

---

## 🔹 State

We maintain:

```text
A queue storing indices of negative elements inside current window
```

---

## 🔹 Why Store Indices?

```text
To check if an element is still inside window when L moves
```

---

## 🔹 Invariant

```text
Queue always contains indices of negative elements in current window [L … R], in order of appearance
```

---

## 🔹 Decision / Movement

### Step 1: Expand (R++)

```cpp
if (nums[R] < 0)
    queue.push(R);
```

---

### Step 2: When window size == k

- If queue not empty → front = first negative
    
- Else → answer = 0
    

---

### Step 3: Shrink (L++)

Before moving L:

```cpp
if (!queue.empty() && queue.front() == L)
    queue.pop();
```

---

## 🔹 Why This Works

Each index:

```text
Added once → when encountered
Removed once → when it leaves window
```

👉 Total operations:

[  
O(n)  
]

---

## 🔹 Stop Condition

Loop ends when `R` reaches end of array.

---

## 🔹 Edge Cases

- No negatives → all outputs 0
    
- k == 1 → check each element
    
- All negatives → each window’s first element
    
- Large k → still efficient
    

---

## 🔹 C++ Implementation

```cpp
class Solution {
public:
    vector<int> firstNegative(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> result;

        deque<int> dq; // stores indices of negative numbers
        int L = 0;

        for (int R = 0; R < n; R++) {
            if (nums[R] < 0) {
                dq.push_back(R);
            }

            if (R - L + 1 == k) {
                if (!dq.empty()) {
                    result.push_back(nums[dq.front()]);
                } else {
                    result.push_back(0);
                }

                if (!dq.empty() && dq.front() == L) {
                    dq.pop_front();
                }

                L++;
            }
        }

        return result;
    }
};
```

---

## 🔹 Time Complexity

[  
O(n)  
]

---

## 🔹 Space Complexity

[  
O(k)  
]

(for storing indices in worst case)

---

## 🔹 Pattern Recognition

This is:

> **Fixed Sliding Window + Data Structure State**

Unlike previous problem:

- State ≠ single variable
    
- State = structure (queue)
    

---

## 🔹 Common Mistakes

❌ Tracking only one negative (fails when it leaves window)  
❌ Using heap (overkill, wrong order)  
❌ Recomputing each window  
❌ Not removing expired indices  
❌ Storing values instead of indices

---

## 🔹 Final Insight

```text
When window needs "first/last element with condition" → use Queue/Deque
```

---

Perfect. Locking it into your revision system.

---

# 📝 MINI NOTES — First Negative Number in Every Window of Size K

---

🔹 **Problem**  
For every window of size `k`, find the **first negative number**. If none → return `0`.

---

🔹 **Graph Type**  
Array (Fixed Window + Condition Tracking)

---

🔹 **Technique**  
Sliding Window + Queue (FIFO State)

---

🔹 **Core Template**

```cpp
deque<int> dq;  // stores indices of negatives
int L = 0;

for (int R = 0; R < n; R++) {

    if (nums[R] < 0)
        dq.push_back(R);

    if (R - L + 1 == k) {

        if (!dq.empty())
            result.push_back(nums[dq.front()]);
        else
            result.push_back(0);

        if (!dq.empty() && dq.front() == L)
            dq.pop_front();

        L++;
    }
}
```

---

🔹 **Pattern Tag**  
Fixed Window + Queue  
Order Maintenance  
Condition Tracking

---

🔸 **Logic Summary**

- Track indices of negative numbers
    
- Queue front = first negative in window
    
- Add new negatives (R++)
    
- Remove expired negatives (when L moves)
    

---

🔸 **Invariant**

```text
Queue contains indices of negative elements in current window [L … R]
```

---

🔸 **Decision Rule**

- nums[R] < 0 → add index
    
- Window full → check front
    
- If front == L → remove
    

---

🔸 **Why Indices (NOT values)**

```text
To verify if element is still inside window when L moves
```

---

🔸 **Stop Condition**

```text
Process when window size == k
```

---

🔸 **Edge Cases**

- No negatives → all 0
    
- All negatives → first element of window
    
- k = 1 → check individually
    

---

🔸 **Common Mistakes**

❌ Using single variable instead of structure  
❌ Not removing expired elements  
❌ Using heap (wrong + slow)  
❌ Recomputing window

---

🔸 **Final Insight**

```text
When you need "first valid element in window" → use Queue
```

---

✅ Phase 0 — Fully Mastered

---
