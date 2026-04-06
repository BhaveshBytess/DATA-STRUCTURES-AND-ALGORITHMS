
## 🔹 Problem

Given an integer array `nums` and an integer `k`, return the **maximum sum of any contiguous subarray of size `k`**.

---

## 🔹 First Principles Understanding

We are NOT asked to:

- check all subarrays ❌
    
- recompute sums ❌
    

We are asked to:

> Efficiently maintain the sum of a **moving window of size k**

---

## 🔹 Core Idea

Instead of recomputing every subarray:

```text
Reuse previous computation using add + remove
```

---

## 🔹 Window Definition

```text
Window [L … R] represents a contiguous subarray
```

We only care when:

```text
R - L + 1 == k
```

---

## 🔹 State

We maintain:

```text
windowSum → sum of current window
maxSum → best answer so far
```

---

## 🔹 Invariant

```text
windowSum always represents sum of elements in current window [L … R]
```

---

## 🔹 Decision / Movement

- Expand window:
    

```cpp
windowSum += nums[R];
```

- When window size reaches k:
    
    - Update answer
        
    - Shrink window
        

```cpp
windowSum -= nums[L];
L++;
```

---

## 🔹 Why This Works

Each element:

```text
Added once (when R includes it)
Removed once (when L excludes it)
```

👉 Hence:

[  
O(n)  
]

---

## 🔹 Stop Condition

Loop ends when `R` reaches end of array.

---

## 🔹 Edge Cases

- k == 1 → return max element
    
- k == n → return sum of whole array
    
- negative values → still works (no assumptions needed)
    

---

## 🔹 C++ Implementation

```cpp
class Solution {
public:
    int maxSumSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        
        int windowSum = 0;
        int maxSum = 0;
        int L = 0;

        for (int R = 0; R < n; R++) {
            windowSum += nums[R];

            if (R - L + 1 == k) {
                maxSum = max(maxSum, windowSum);
                
                windowSum -= nums[L];
                L++;
            }
        }

        return maxSum;
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
O(1)  
]

---

## 🔹 Pattern Recognition

This is:

> **Fixed Sliding Window**

- Window size is constant
    
- No dynamic shrinking condition
    
- Only shift window forward
    

---

## 🔹 Common Mistakes

❌ Recomputing sum using loop → O(n·k)  
❌ Forgetting to remove nums[L]  
❌ Updating answer at wrong time  
❌ Wrong window size condition

---

## 🔹 Final Insight

```text
Sliding Window = Maintain, don’t recompute
```

---

## MINI-NOTE : 

---

🔹 **Problem**  
Find maximum sum of any contiguous subarray of size `k`.

---

🔹 **Graph Type**  
Array (Fixed Window)

---

🔹 **Technique**  
Sliding Window (Fixed Size)

---

🔹 **Core Template**

```cpp
int windowSum = 0, maxSum = 0;
int L = 0;

for (int R = 0; R < n; R++) {
    windowSum += nums[R];

    if (R - L + 1 == k) {
        maxSum = max(maxSum, windowSum);
        windowSum -= nums[L];
        L++;
    }
}
```

---

🔹 **Pattern Tag**  
Fixed Window  
Add-Remove Optimization  
Running Sum

---

🔸 **Logic Summary**

- Expand window (R++)
    
- Add new element
    
- When size == k:
    
    - update answer
        
    - remove nums[L]
        
    - move L
        

---

🔸 **Invariant**

```text
windowSum always equals sum of elements in [L … R]
```

---

🔸 **Decision Rule**

- Always expand R
    
- When window size hits k → process and slide
    

---

🔸 **Stop Condition**

```text
Loop ends when R reaches n
```

---

🔸 **Edge Cases**

- k = 1 → max element
    
- k = n → sum of whole array
    
- negatives → still valid
    

---

🔸 **Common Mistakes**

❌ Recomputing sum with loop  
❌ Forgetting to subtract nums[L]  
❌ Updating before window reaches size k  
❌ Wrong window size condition

---

🔸 **Final Insight**

```text
Sliding Window = Add one, Remove one, Never recompute
```

---

✅ Phase 0 — Core Fixed Window Pattern Locked

---
