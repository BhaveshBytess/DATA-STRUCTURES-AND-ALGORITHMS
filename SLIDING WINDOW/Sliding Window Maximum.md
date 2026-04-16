## 🔹 Problem

Given an array `nums` and an integer `k`, return the **maximum of every contiguous subarray of size k**.

### Example

```text
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
```

---

## 🔹 First Principles (Why normal SW fails)

Sliding window works when:

```text
Shrinking helps fix condition
```

But here:

```text
We need max element
```

---

### ❌ Problem

When L moves:

```text
If max element goes out → we don’t know next max
```

👉 Recomputing = O(k) → TLE

---

## 🔹 Key Insight

```text
We don’t store all elements
We store only useful candidates
```

---

### 🔥 Rule

```text
If a smaller element comes before a bigger one,
it will NEVER become maximum
```

👉 Remove it permanently

---

## 🔹 Technique

Use:

```text
Deque (double-ended queue)
```

---

### What it stores?

```text
Indices (not values)
```

---

### What it maintains?

```text
Monotonic decreasing order
(front = max)
```

---

## 🔹 Core Template Mapping

```text
Window = [L … R]
```

---

### 1️⃣ Expand

```cpp
while(!dq.empty() && nums[dq.back()] < nums[R])
    dq.pop_back();

dq.push_back(R);
```

---

### 2️⃣ Fix Window

```cpp
if(R - L + 1 > k){
    if(dq.front() == L)
        dq.pop_front();
    L++;
}
```

---

### 3️⃣ Answer

```cpp
if(R - L + 1 == k)
    ans.push_back(nums[dq.front()]);
```

---

## 🔹 Final C++ Code (Your Style — Clean Template)

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        int l = 0;
        deque<int> dq;
        vector<int> ans;

        for(int r = 0; r < nums.size(); r++){

            // include r
            while(!dq.empty() && nums[dq.back()] < nums[r]){
                dq.pop_back();
            }
            dq.push_back(r);

            // fix window
            if(r - l + 1 > k){
                if(dq.front() == l){
                    dq.pop_front();
                }
                l++;
            }

            // update answer
            if(r - l + 1 == k){
                ans.push_back(nums[dq.front()]);
            }
        }

        return ans;
    }
};
```

---

## 🔹 Logic Summary

```text
We maintain a deque of indices such that:

- Elements are in decreasing order
- Front always gives maximum
- Remove:
    → smaller elements from back (useless)
    → out-of-window elements from front
```

---

## 🔹 Trick

```text
Deque = filtered version of window
Only stores potential maximums
```

---

## 🔹 Why normal SW fails

```text
Because max is NOT monotonic under shrinking

Removing L can destroy max
→ cannot fix in O(1)
```

---

## 🔹 Final Insight (VERY IMPORTANT)

```text
This is NOT just sliding window

This is:

Sliding Window + Monotonic Data Structure
```

---

## 🔹 Memory Anchor (Lock this)

```text
If problem asks:

→ max/min in window
→ sliding range queries

Think:

👉 MONOTONIC DEQUE
```

---

## 🔹 Interview Signal

If you solve this smoothly:

```text
You are ABOVE average in sliding window
```

---

## 🧠 Recap (Future You — Read This)

If you come back after months:

```text
Normal SW breaks when removing elements ruins answer

Solution:
→ Keep only useful candidates
→ Maintain order (deque)
→ Front = answer
```

---
