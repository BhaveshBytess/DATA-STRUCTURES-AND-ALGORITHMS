
# (IMPORTANT — Couldn’t Solve Initially)

---

## 🔹 Problem

Given an integer array `nums` (can contain **negative numbers**) and an integer `k`, return:

```text
Length of the shortest non-empty subarray with sum ≥ k
```

If no such subarray exists:

```text
return -1
```

---

## 🔹 Example

```text
nums = [2, -1, 2], k = 3  
Output = 3
```

---

# ⚔️ Why This Problem Is Important

```text
⭐ Could NOT solve initially
→ Sliding window intuition FAILS
→ Introduces Prefix + Monotonic Deque (very advanced)
```

---

# 🧠 First Principle

We know:

```text
prefix[r] - prefix[l] = subarray sum
```

---

## 🔥 Goal

```text
prefix[r] - prefix[l] ≥ k
```

---

## Rearranged

```text
prefix[l] ≤ prefix[r] - k
```

---

# 💣 Core Transformation

Instead of thinking:

```text
window [l … r]
```

Think:

```text
For each r → find best l
```

---

# 🔹 Technique

```text
Prefix Sum + Monotonic Deque
```

---

# 🔹 State

```text
prefix[i] → sum from 0 to i-1
deque → stores indices of prefix
```

---

# 🔥 Key Observations

---

## 1️⃣ Smaller prefix is better

```text
prefix[r] - smaller value → bigger sum
```

👉 Helps reach ≥ k faster

---

## 2️⃣ Closer index is better

```text
length = r - l → smaller l gives longer window
```

👉 We want l as large as possible (closer to r)

---

# ⚔️ Deque Rules

---

## 🔹 Rule 1 — Remove from BACK

```cpp
while(prefix[i] <= prefix[dq.back()])
    dq.pop_back();
```

### Why?

```text
New prefix is smaller → better candidate
Old larger prefix is useless forever
```

👉 Dominated candidate removed

---

## 🔹 Rule 2 — Remove from FRONT

```cpp
while(prefix[i] - prefix[dq.front()] >= k)
```

### Why?

```text
We found a valid subarray
Try next l to minimize length
```

👉 Already used → remove

---

# 🔹 Core Algorithm

At each index `i`:

---

### 1️⃣ Check for valid subarray

```text
prefix[i] - prefix[l] ≥ k
```

→ update answer  
→ pop front

---

### 2️⃣ Maintain monotonic property

```text
Remove larger prefixes from back
```

---

### 3️⃣ Add current index

```text
Push i into deque
```

---

# 🔹 C++ Code

```cpp
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {

        int n = nums.size();

        vector<long long> prefix(n + 1, 0);
        for(int i = 0; i < n; i++){
            prefix[i + 1] = prefix[i] + nums[i];
        }

        deque<int> dq;
        int ans = INT_MAX;

        for(int i = 0; i <= n; i++){

            while(!dq.empty() && prefix[i] - prefix[dq.front()] >= k){
                ans = min(ans, i - dq.front());
                dq.pop_front();
            }

            while(!dq.empty() && prefix[i] <= prefix[dq.back()]){
                dq.pop_back();
            }

            dq.push_back(i);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
```

---

# 🔍 Dry Run Insight

```text
prefix = [0, 2, 1, 3]
```

- Remove 2 when 1 comes → 1 is better
    
- Use 0 when 3 comes → valid subarray
    
- Remove used indices → optimize length
    

---

# ⚠️ Why Sliding Window Fails

```text
Negative numbers break monotonicity
```

Example:

```text
Removing element can INCREASE sum
```

👉 Cannot decide expand/shrink reliably

---

# 🧠 Core Mental Shift

---

## ❌ Old Thinking

```text
Maintain window → adjust L/R
```

---

## ✅ New Thinking

```text
At each r:
Find best l using prefix + deque
```

---

# 🔥 Pattern Tag

```text
Prefix Sum + Monotonic Deque + Optimization (Shortest Length)
```

---

# ⚠️ Common Mistakes

---

❌ Trying sliding window  
❌ Not understanding prefix transformation  
❌ Forgetting to remove dominated candidates  
❌ Not using long long (overflow risk)

---

# 🧠 Final Insight (LOCK THIS)

```text
We are NOT scanning windows

We are filtering best starting points
using prefix sums
```

---

# 🧠 Memory Trigger (Future You)

If you see:

```text
→ shortest/longest subarray
→ sum condition
→ NEGATIVE numbers involved
```

Think:

```text
Sliding window will fail
→ Use prefix + deque
```

---

# ⚔️ Final Feeling

```text
This problem feels confusing because:
→ It breaks sliding window intuition
→ Requires a shift to prefix-based reasoning
```

---

# 🚀 STATUS

```text
⭐ IMPORTANT PROBLEM
❌ Could not solve initially
✅ Now understood deeply
```
