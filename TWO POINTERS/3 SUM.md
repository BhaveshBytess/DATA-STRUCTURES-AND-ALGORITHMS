
## 🟢 Problem: 3Sum

---

## 🔹 Problem Statement

Given an integer array `nums`, return all unique triplets  
`[nums[i], nums[j], nums[k]]` such that:

```
i != j != k
nums[i] + nums[j] + nums[k] == 0
```

The solution set must not contain duplicate triplets.

Constraints:

- `3 <= nums.length <= 3000`
    
- `-10^5 <= nums[i] <= 10^5`
    

---

# 🧠 First Principles Understanding

This is not “find triplets.”

It is:

> Fix one element → reduce to Two Sum → apply monotonic elimination.

Naive approach:

- Try all triplets → O(n³)
    
- Not acceptable
    

We must reduce one dimension.

---

# 🧩 Pattern Classification

- Technique: Fix One + Opposite Direction Two Pointers
    
- Category: k-Sum Reduction
    
- Signal:
    
    - “Find triplets”
        
    - “Unique combinations”
        
    - Target sum given
        
    - Constraints allow O(n²)
        

---

# 🏗 Why Sorting Is Necessary

Sorting enables:

1️⃣ Monotonic pointer movement  
2️⃣ Deterministic elimination  
3️⃣ Duplicate clustering  
4️⃣ Early pruning (`nums[i] > 0` break)

Without sorting:

- Two pointers don’t work
    
- Duplicate control becomes messy
    

Sorting transforms brute force into structured elimination.

---

# 📌 Outer Loop Invariant

For each index `i`:

```
nums[i] is fixed anchor
We search for two numbers in nums[i+1 … n-1]
whose sum equals -nums[i]
```

Duplicate prevention:

```
if (i > 0 && nums[i] == nums[i-1]) continue;
```

Reason:  
Same anchor → identical search space → duplicate triplets.

---

# 📌 Inner Two-Pointer Invariant

For fixed `i`:

```
left = i + 1
right = n - 1
```

Invariant during loop:

- All pairs outside `[left … right]` are eliminated.
    
- If current_sum < target → move left.
    
- If current_sum > target → move right.
    
- If equal → record triplet and skip duplicates.
    

Stop when:

```
left >= right
```

---

# ⚙️ Algorithm Logic

1. Sort array.
    
2. Iterate `i` from 0 to n-1.
    
3. Skip duplicate anchors.
    
4. If `nums[i] > 0`, break early.
    
5. Apply two-pointer search on subarray.
    
6. After finding valid triplet:
    
    - Move left++
        
    - Move right--
        
    - Skip duplicate values on both sides.
        

---

# 💻 C++ Implementation

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n; i++) {

            if (nums[i] > 0) break;

            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                long sum = (long)nums[i] + nums[left] + nums[right];

                if (sum < 0) {
                    left++;
                } 
                else if (sum > 0) {
                    right--;
                } 
                else {
                    ans.push_back({nums[i], nums[left], nums[right]});

                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                }
            }
        }

        return ans;
    }
};
```

---

# ⏱ Complexity Analysis

Sorting:

```
O(n log n)
```

Outer loop:

```
O(n)
```

Inner two-pointer:

```
O(n)
```

Total:

```
O(n²)
```

Space:

```
O(1) extra (excluding output)
```

---

# ❌ Why Brute Force Fails

Triple nested loops:

```
O(n³)
```

For n = 3000:

[  
3000^3 = 27 \text{ billion}  
]

Not feasible.

---

# ❌ Why Hashing Isn’t Superior

Hash-based approach:

- Also O(n²)
    
- Uses O(n) extra space
    
- Duplicate handling more complex
    
- No pruning via monotonic property
    

Sorting + two pointers is cleaner and space-optimal.

---

# 🔥 Critical Edge Cases

1️⃣ All zeros:

```
[0,0,0,0]
→ [[0,0,0]]
```

2️⃣ All positive:

```
[1,2,3]
→ []
```

3️⃣ All negative:

```
[-3,-2,-1]
→ []
```

4️⃣ Large magnitude values → use long for sum to avoid overflow.

---

# 🎯 What Interviewer Is Testing

- Can you reduce dimensionality?
    
- Can you handle duplicates correctly?
    
- Can you maintain pointer invariants?
    
- Do you understand pruning logic?
    
- Can you analyze complexity properly?
    

---

# MINI-NOTE : 


🔹 **Problem**  
3Sum

🔹 **Graph Type**  
Array (Sorted) — k-Sum Reduction

🔹 **Technique**  
Fix One + Two Pointers (Opposite Direction)

🔹 **Core Template**

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    int n = nums.size();

    for (int i = 0; i < n; i++) {

        if (nums[i] > 0) break;

        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            long sum = (long)nums[i] + nums[left] + nums[right];

            if (sum < 0) left++;
            else if (sum > 0) right--;
            else {
                ans.push_back({nums[i], nums[left], nums[right]});

                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;

                left++;
                right--;
            }
        }
    }

    return ans;
}
```

🔹 **Pattern Tag**  
k-Sum → Reduce to (k-1)-Sum → Two Pointer Convergence

---

🔸 **Logic Summary**

1. Sort to enable monotonic movement.
    
2. Fix anchor `i`.
    
3. Convert to 2Sum with target `-nums[i]`.
    
4. Use left/right convergence.
    
5. Skip duplicates at:
    
    - Anchor level
        
    - Pair level
        
6. Early break if `nums[i] > 0`.
    

Time → O(n²)  
Space → O(1) extra

---

🔸 **Trick**

- Skip duplicate anchors:
    
    ```cpp
    if (i > 0 && nums[i] == nums[i-1]) continue;
    ```
    
- Skip duplicate pairs AFTER finding valid triplet.
    
- Use `long` for sum to prevent overflow.
    
- Break early if anchor becomes positive.
    

---

🔸 **Why Hashing Isn’t Better**

- Also O(n²)
    
- Requires extra space
    
- Duplicate handling messy
    
- No monotonic pruning
    

---

🔸 **Why We Move Pointers**

For fixed `i`:

- If sum < 0 → move left (increase sum)
    
- If sum > 0 → move right (decrease sum)
    
- If equal → record & skip duplicates
    

Sorting guarantees this elimination works.

---

🔸 **Common Mistakes**

❌ Not sorting  
❌ Forgetting duplicate skip for `i`  
❌ Forgetting duplicate skip for `left/right`  
❌ Skipping duplicates before recording result  
❌ Integer overflow

---

🔸 **Final Insight**

3Sum is:

> 1 fixed dimension + 1 linear convergence dimension.

General k-Sum complexity:

```
O(n^(k-1))
```

3Sum is theoretically Ω(n²).  
No known sub-quadratic solution.

---

