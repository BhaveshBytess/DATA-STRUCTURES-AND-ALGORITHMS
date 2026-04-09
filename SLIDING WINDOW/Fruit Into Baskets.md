## 🔹 Problem

Given an integer array `fruits`, each element represents a fruit type.

You have **2 baskets**, and each basket can hold only **one type of fruit**.

👉 Return the **maximum number of fruits** you can collect in a contiguous subarray such that:

```text
At most 2 distinct fruit types
```

---

## 🔹 Intuition (First Principles)

This is NOT a “fruit problem”.

This is:

```text
Longest subarray with at most 2 distinct elements
```

---

### 🔥 Key Observation

- We need a **contiguous window**
    
- Constraint: **≤ 2 distinct types**
    

👉 This is a **variable sliding window**

---

## 🔹 Key Idea

Maintain a window `[L … R]` such that:

```text
Number of distinct elements ≤ 2
```

---

## 🔹 Approach

1. Use sliding window with two pointers `L` and `R`
    
2. Maintain:
    
    - `map` → frequency of fruits
        
    - `count` → number of distinct fruits
        

---

### 🔹 Steps

- Expand `R`
    
- Add fruit to map
    
- If new fruit → increase `count`
    
- If `count > 2` → shrink window from left
    
- Update max length after window becomes valid
    

---

## 🔹 C++ Code

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> mp;
        int L = 0;
        int count = 0;
        int maxlen = 0;

        for (int R = 0; R < fruits.size(); R++) {
            mp[fruits[R]]++;

            if (mp[fruits[R]] == 1)
                count++;

            while (count > 2) {
                mp[fruits[L]]--;

                if (mp[fruits[L]] == 0)
                    count--;

                L++;
            }

            maxlen = max(maxlen, R - L + 1);
        }

        return maxlen;
    }
};
```

---

## 🔹 Time Complexity

```text
O(n)
```

👉 Each element is visited at most twice

---

## 🔹 Space Complexity

```text
O(1)
```

👉 At most 3 entries in map (since we shrink when >2)

---

## 🔹 Why This Works

- Window always maintains **valid constraint**
    
- We expand greedily
    
- Shrink only when constraint breaks
    
- Every valid window is considered
    

---

## 🔹 Common Mistakes

❌ Forgetting to decrement `count` when freq becomes 0  
❌ Updating answer before fixing window  
❌ Using set instead of frequency map  
❌ Not shrinking properly

---

## 🔹 Interview Insight

This problem is a **template problem** for:

```text
Longest Substring with At Most K Distinct Characters
```

---

## 🔹 Pattern Tag

```text
Sliding Window + Frequency Map + At Most K Distinct
```

---

If you can solve this cleanly → you’ve unlocked **Phase 2 foundation**.

---

Say **Doc 2** when ready.