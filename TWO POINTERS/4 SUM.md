
## 🔹 Problem Statement

Given an integer array `nums` and an integer `target`,  
return all unique quadruplets:

```
[nums[a], nums[b], nums[c], nums[d]]
```

such that:

- `a, b, c, d` are distinct indices
    
- `nums[a] + nums[b] + nums[c] + nums[d] == target`
    

The solution set must not contain duplicate quadruplets.

---

### 🔹 Example

Input:

```
nums = [1,0,-1,0,-2,2], target = 0
```

Output:

```
[
  [-2,-1,1,2],
  [-2,0,0,2],
  [-1,0,0,1]
]
```

---

### 🔒 Constraints

- `1 <= nums.length <= 200`
    
- `-10^9 <= nums[i] <= 10^9`
    
- `-10^9 <= target <= 10^9`
    

---

# 🧠 First Principles Understanding

This is:

> A value-unique combination enumeration problem.

Unlike 3Sum Closest:

- We are not optimizing.
    
- We must generate all unique quadruplets.
    

It is a direct extension of:

```
4Sum → reduce to 3Sum → reduce to 2Sum
```

---

# 🧩 Pattern Classification

- Technique: Fix Two + Two Pointers
    
- Category: k-Sum Enumeration
    
- Signal:
    
    - “All unique combinations”
        
    - Small n (≤ 200)
        
    - Exact equality condition
        

---

# 🏗 Core Strategy

1. Sort array.
    
2. Fix first element `i`.
    
3. Fix second element `j`.
    
4. Solve 2Sum in remaining subarray using two pointers.
    
5. Carefully skip duplicates at all three levels.
    

---

# 📌 Invariants

### Outer Loop (`i`)

- `nums[i]` is first anchor.
    
- All quadruplets begin with this value.
    
- Skip duplicates to avoid repeated first elements.
    

---

### Second Loop (`j`)

- `nums[j]` is second anchor.
    
- Skip duplicates relative to current `i`.
    

Correct duplicate check:

```cpp
if (j > i+1 && nums[j] == nums[j-1]) continue;
```

---

### Two Pointer Layer

For fixed `(i, j)`:

```
left = j + 1
right = n - 1
```

Invariant:

- All valid pairs must lie in [left … right].
    
- Window shrinks monotonically.
    
- Skip duplicates only after a valid quadruplet is found.
    

---

# 🔥 Pruning Optimization (Advanced)

Because array is sorted ascending:

### For fixed `i`

Minimum possible sum:

```
nums[i] + nums[i+1] + nums[i+2] + nums[i+3]
```

If this > target → break.

Maximum possible sum:

```
nums[i] + nums[n-1] + nums[n-2] + nums[n-3]
```

If this < target → continue.

---

### For fixed `(i, j)`

Minimum possible sum:

```
nums[i] + nums[j] + nums[j+1] + nums[j+2]
```

If > target → break.

Maximum possible sum:

```
nums[i] + nums[j] + nums[n-2] + nums[n-1]
```

If < target → continue.

---

# ⚠️ Overflow Handling

Since:

```
nums[i] can be up to 10^9
```

Sum of four values may exceed `int`.

Therefore:

```cpp
long long sum
```

must be used.

---

# 💻 C++ Implementation

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        vector<vector<int>> result;
        int n = nums.size();
        if (n < 4) return result;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 3; i++) {

            if (i > 0 && nums[i] == nums[i - 1]) continue;

            if ((long long)nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target)
                break;

            if ((long long)nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target)
                continue;

            for (int j = i + 1; j < n - 2; j++) {

                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                if ((long long)nums[i] + nums[j] + nums[j+1] + nums[j+2] > target)
                    break;

                if ((long long)nums[i] + nums[j] + nums[n-2] + nums[n-1] < target)
                    continue;

                int left = j + 1;
                int right = n - 1;

                while (left < right) {

                    long long sum = (long long)nums[i] + nums[j]
                                    + nums[left] + nums[right];

                    if (sum == target) {

                        result.push_back({nums[i], nums[j],
                                          nums[left], nums[right]});

                        while (left < right && nums[left] == nums[left + 1])
                            left++;

                        while (left < right && nums[right] == nums[right - 1])
                            right--;

                        left++;
                        right--;
                    }
                    else if (sum < target) {
                        left++;
                    }
                    else {
                        right--;
                    }
                }
            }
        }

        return result;
    }
};
```

---

# ⏱ Complexity Analysis

Sorting:

```
O(n log n)
```

Main logic:

```
O(n³)
```

Total:

```
O(n³)
```

Space:

```
O(1) extra (excluding output)
```

---

# 🎯 What Interviewer Tests Here

- Can you scale k-Sum pattern?
    
- Can you manage duplicate layers correctly?
    
- Do you understand monotonic pruning?
    
- Can you prevent integer overflow?
    
- Do you understand value-uniqueness vs index-uniqueness?
    

---

# MINI-NOTE : 

🔹 **Problem**  
4Sum

🔹 **Graph Type**  
Array (Sorted) — k-Sum Enumeration

🔹 **Technique**  
Fix Two + Two Pointers

🔹 **Core Template**

```cpp
vector<vector<int>> fourSum(vector<int>& nums, int target) {

    vector<vector<int>> res;
    int n = nums.size();
    if (n < 4) return res;

    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 3; i++) {

        if (i > 0 && nums[i] == nums[i-1]) continue;

        for (int j = i + 1; j < n - 2; j++) {

            if (j > i+1 && nums[j] == nums[j-1]) continue;

            int left = j + 1;
            int right = n - 1;

            while (left < right) {

                long long sum = (long long)nums[i] + nums[j]
                                + nums[left] + nums[right];

                if (sum == target) {

                    res.push_back({nums[i], nums[j],
                                   nums[left], nums[right]});

                    while (left < right && nums[left] == nums[left+1]) left++;
                    while (left < right && nums[right] == nums[right-1]) right--;

                    left++;
                    right--;
                }
                else if (sum < target) left++;
                else right--;
            }
        }
    }

    return res;
}
```

🔹 **Pattern Tag**  
k-Sum → Enumeration (Exact Match)

---

🔸 **Logic Summary**

1. Sort to enable monotonic pointer movement.
    
2. Fix first anchor `i`.
    
3. Fix second anchor `j`.
    
4. Apply two-pointer 2Sum on remaining range.
    
5. Skip duplicates at:
    
    - `i` level
        
    - `j` level
        
    - `left/right` level (after match)
        

Time → O(n³)  
Space → O(1) extra

---

🔸 **Trick**

- Use `long long` for sum (overflow safety).
    
- Duplicate skipping must be scoped:
    
    - `j > i+1`
        
- Prune using bounds:
    
    - Minimal sum > target → break
        
    - Maximal sum < target → continue
        

---

🔸 **Why Hashing Is Worse Here**

- Would require O(n²) storage for pair sums.
    
- More complex duplicate handling.
    
- Two-pointer keeps space O(1).
    

---

🔸 **Why Break vs Continue in Pruning**

- If minimal sum > target → future only increases → break.
    
- If maximal sum < target → next `i` may increase sum → continue.
    

Depends on monotonic ordering.

---

🔸 **Common Mistakes**

❌ Using `int` for sum → overflow  
❌ Wrong duplicate condition (`j > 0` instead of `j > i+1`)  
❌ Skipping duplicates before match in two-pointer  
❌ Forgetting pruning logic bounds  
❌ Mixing index uniqueness with value uniqueness

---

🔸 **Final Insight**

4Sum is not new logic.

It is:

> k-Sum scaling with layered duplicate control.

Time complexity grows as:

[  
O(n^{k-1})  
]

For k=4 → O(n³).

Mastering 4Sum means:  
You understand scalable two-pointer recursion structure.

---
