## 🔹 Problem

Given an integer array `nums` and an integer `k`, return:

👉 Number of subarrays with **exactly k distinct integers**

---

## 🔹 Intuition (First Principles)

Directly solving **exactly k** is hard because:

```text
Not monotonic → cannot directly shrink/expand cleanly
```

So we transform:

```text
exactly(k) = atMost(k) - atMost(k - 1)
```

👉 This converts the problem into a **monotonic sliding window**

---

## 🔹 Key Idea

For any valid window `[L … R]`:

```text
All subarrays ending at R and starting from L to R are valid
```

So:

```text
Number of subarrays = (R - L + 1)
```

---

## 🔹 Approach

1. Create helper function:
    

```text
count subarrays with at most k distinct
```

2. Use sliding window:
    
    - Expand with `R`
        
    - Shrink when distinct count > k
        
3. For every valid window:
    

```text
ans += (R - L + 1)
```

4. Final answer:
    

```text
atMost(k) - atMost(k - 1)
```

---

## 🔹 C++ Code

```cpp
class Solution {
public:
    int atMostK(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        int L = 0;
        int count = 0;
        int ans = 0;

        for (int R = 0; R < nums.size(); R++) {
            mp[nums[R]]++;

            if (mp[nums[R]] == 1)
                count++;

            while (count > k) {
                mp[nums[L]]--;
                if (mp[nums[L]] == 0)
                    count--;
                L++;
            }

            ans += (R - L + 1);
        }

        return ans;
    }

    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k - 1);
    }
};
```

---

## 🔹 Time Complexity

```text
O(n)
```

👉 Each element is visited at most twice (L and R)

---

## 🔹 Space Complexity

```text
O(k)
```

👉 Map stores at most k+1 distinct elements

---

## 🔹 Why This Works

- `atMost(k)` → counts all valid subarrays with ≤ k distinct
    
- `atMost(k-1)` → removes those with fewer distinct
    

👉 What remains:

```text
Exactly k distinct subarrays
```

---

## 🔹 Common Mistakes

❌ Using `ans++` instead of `(R - L + 1)`  
❌ Forgetting to decrease `count` when freq becomes 0  
❌ Trying to solve “exactly k” directly  
❌ Updating answer in invalid window

---

## 🔹 Interview Insight

This problem tests:

- Transformation thinking (exact → at most)
    
- Sliding window counting pattern
    
- Understanding of contribution per index
    

---

If you say:

> “Each valid window contributes multiple subarrays ending at R”

👉 You sound **top 5% candidate**

---

Say **Doc 2** when ready.