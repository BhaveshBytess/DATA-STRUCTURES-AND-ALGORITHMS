
## 🟢 Problem: 3Sum Closest

---

## 🔹 Problem Statement

Given an integer array `nums` of length `n` and an integer `target`,  
find three integers in `nums` such that the sum is closest to `target`.

Return the sum of the three integers.

You may assume that each input has exactly one solution.

---

### 🔹 Example 1

Input:

```
nums = [-1,2,1,-4], target = 1
```

Output:

```
2
```

Explanation:

```
(-1 + 2 + 1 = 2)
```

2 is closest to 1.

---

### 🔹 Example 2

Input:

```
nums = [0,0,0], target = 1
```

Output:

```
0
```

---

### 🔒 Constraints

- `3 <= nums.length <= 1000`
    
- `-1000 <= nums[i] <= 1000`
    
- `-10^4 <= target <= 10^4`
    

---

# 🧠 First Principles Understanding

This is NOT a combination enumeration problem.

It is:

> An optimization problem over triplet sums.

Unlike 3Sum:

- We do NOT search for equality.
    
- We minimize absolute distance to target.
    
- We return a single best sum.
    

---

# 🧩 Pattern Classification

- Technique: Fix One + Two Pointers (Opposite Direction)
    
- Category: k-Sum Optimization Variant
    
- Signal:
    
    - “Closest to target”
        
    - “Return single value”
        
    - n ≤ 1000 → O(n²) acceptable
        

---

# 🏗 Why Sorting Is Necessary

Sorting enables:

1️⃣ Monotonic pointer movement  
2️⃣ Deterministic elimination of search space  
3️⃣ Efficient convergence toward target

After sorting:

- If sum < target → move left (increase sum)
    
- If sum > target → move right (decrease sum)
    

Without sorting, pointer movement logic breaks.

---

# 📌 Outer Loop Invariant

For each index `i`:

```
nums[i] is fixed anchor
We search in nums[i+1 … n-1]
for two elements forming sum closest to (target - nums[i])
```

Unlike 3Sum:

- No duplicate skipping required
    
- We evaluate every configuration
    

---

# 📌 Inner Loop Invariant

For fixed `i`:

```
left = i + 1
right = n - 1
```

Invariant during loop:

- All pairs outside [left … right] are eliminated.
    
- Each step strictly shrinks search space.
    
- At every configuration, we update closest sum if needed.
    

Stop when:

```
left >= right
```

---

# ⚙️ Algorithm Logic

1. Sort array.
    
2. Initialize `closestSum = nums[0] + nums[1] + nums[2]`.
    
3. For each `i`:
    
    - Set `left = i + 1`, `right = n - 1`.
        
    - While `left < right`:
        
        - Compute `currentSum`.
            
        - Update closest if nearer to target.
            
        - If `currentSum == target` → return immediately.
            
        - If `currentSum < target` → left++.
            
        - Else → right--.
            
4. Return `closestSum`.
    

---

# 💻 C++ Implementation

```cpp
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int closestSum = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n - 2; i++) {

            int left = i + 1;
            int right = n - 1;

            while (left < right) {

                int currentSum = nums[i] + nums[left] + nums[right];

                if (currentSum == target) {
                    return target;
                }

                if (abs(currentSum - target) < abs(closestSum - target)) {
                    closestSum = currentSum;
                }

                if (currentSum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return closestSum;
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

Inner loop:

```
O(n)
```

Total:

```
O(n²)
```

Space:

```
O(1) extra
```

---

# 🔥 Why No Duplicate Skipping?

Because:

- We are optimizing distance, not enumerating unique triplets.
    
- Duplicate values may still produce better (closer) sums.
    
- Skipping could miss valid closer candidates.
    

Optimization problems evaluate all viable states.

---

# 🔥 Why No Early Break Like 3Sum?

In 3Sum:

- We searched for exact zero.
    
- Once anchor > 0 → impossible.
    

Here:

- We search for minimum |sum - target|.
    
- Even large sums may still be closest.
    
- No global impossibility region exists.
    

Therefore:  
No safe global pruning.

---

# 🎯 What Interviewer Is Testing

- Can you adapt equality-based logic to optimization?
    
- Do you understand pointer movement monotonicity?
    
- Can you maintain dynamic best value?
    
- Do you understand pruning vs unsafe pruning?
    
- Can you reason about complexity limits?
    

---

# MINI-NOTE : 

🔹 **Problem**  
3Sum Closest

🔹 **Graph Type**  
Array (Sorted) — k-Sum Optimization

🔹 **Technique**  
Fix One + Two Pointers (Opposite Direction)

🔹 **Core Template**

```cpp
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();

    int closest = nums[0] + nums[1] + nums[2];

    for (int i = 0; i < n - 2; i++) {

        int left = i + 1;
        int right = n - 1;

        while (left < right) {

            int sum = nums[i] + nums[left] + nums[right];

            if (sum == target) return target;

            if (abs(sum - target) < abs(closest - target))
                closest = sum;

            if (sum < target) left++;
            else right--;
        }
    }

    return closest;
}
```

🔹 **Pattern Tag**  
k-Sum → Optimization Variant (Distance Minimization)

---

🔸 **Logic Summary**

1. Sort to enable monotonic movement.
    
2. Fix anchor `i`.
    
3. Apply two-pointer convergence.
    
4. At every state:
    
    - Update `closest` if current sum is nearer to target.
        
5. If exact match → return immediately.
    
6. Continue shrinking search window.
    

Time → O(n²)  
Space → O(1)

---

🔸 **Trick**

- Initialize `closest` using first 3 elements.
    
- Update BEFORE moving pointers.
    
- No duplicate skipping needed.
    
- Early return if exact match found.
    

---

🔸 **Why No Duplicate Skipping**

Unlike 3Sum:

- We are not generating unique combinations.
    
- We are minimizing distance.
    
- Even duplicate values may produce closer sums.
    
- Skipping could miss optimal solution.
    

---

🔸 **Why No Early Break Like 3Sum**

In 3Sum:

- Once anchor > 0 → impossible to hit 0.
    

In 3Sum Closest:

- We minimize |sum - target|.
    
- Even large sums might be closest.
    
- No global impossibility region exists.
    

---

🔸 **Common Mistakes**

❌ Skipping duplicates unnecessarily  
❌ Updating closest after pointer move  
❌ Forgetting early return on exact match  
❌ Using INT_MAX without careful diff comparison

---

🔸 **Final Insight**

3Sum Closest is:

> Same structural skeleton as 3Sum  
> But objective shifts from equality → minimization.

This changes:

- Duplicate handling
    
- Pruning rules
    
- Return logic
    

Structure same. Objective different.

---
