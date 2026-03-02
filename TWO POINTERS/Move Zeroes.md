
## 🟢 Problem: Move Zeroes

---

## 🔹 Problem Statement

Given an integer array `nums`, move all `0`s to the end while maintaining the relative order of non-zero elements.

You must perform the operation **in-place**.

Constraints:

- `1 <= nums.length <= 10^4`
    
- Elements may be negative, positive, or zero.
    

---

# 🧠 First Principles Understanding

This problem is not about zeros.

It is about:

> Stable in-place compaction of elements satisfying a condition (non-zero).

We are partitioning the array into:

- Non-zero elements (front)
    
- Zero elements (back)
    

While preserving original order of non-zero elements.

---

# 🧩 Pattern Classification

- Technique: Two Pointers (Same Direction)
    
- Subtype: Reader–Writer
    
- Category: Stable In-place Partition
    
- Signal: “Move X to end” + “Maintain order” + “O(1) space”
    

---

# 📌 Invariant

At any moment:

```
nums[0 … slow-1] → contains all non-zero elements found so far (stable order)
nums[slow … fast-1] → irrelevant
nums[fast … end] → unexplored
```

Important distinction from Remove Duplicates:

Here:

> `slow` represents the next position to place a valid element.

Not the last valid index.

---

# ⚙️ Algorithm Logic

1. Initialize `slow = 0`
    
2. Iterate `fast` from 0 to n-1
    
3. If `nums[fast] != 0`:
    
    - Copy `nums[fast]` to `nums[slow]`
        
    - Increment `slow`
        
4. After loop:
    
    - Fill remaining positions from `slow` to end with 0
        

---

# 🧪 Dry Run

Input:

```
[0,1,0,3,12]
```

Processing:

```
fast=0 → skip
fast=1 → write at index 0 → slow=1
fast=2 → skip
fast=3 → write at index 1 → slow=2
fast=4 → write at index 2 → slow=3
```

Array becomes:

```
[1,3,12,3,12]
```

Fill from slow=3:

```
[1,3,12,0,0]
```

---

# 💻 C++ Implementation

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0;

        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != 0) {
                nums[slow] = nums[fast];
                slow++;
            }
        }

        while (slow < nums.size()) {
            nums[slow++] = 0;
        }
    }
};
```

---

# ⏱ Complexity

- Time: O(n)
    
- Space: O(1)
    

---

# 🔍 Optimization Insight (Advanced)

To reduce unnecessary writes:

```cpp
if (nums[fast] != 0) {
    if (slow != fast) {
        nums[slow] = nums[fast];
    }
    slow++;
}
```

Prevents redundant writes when array has no zeros.

---

# ❌ Why Swap Is Not Always Better

Swap performs 3 writes internally.

Overwrite performs 1 write.

Worst case `[1,2,3,4]`:

- Swap → 3n writes
    
- Overwrite → n writes
    
- Optimized overwrite → 0 writes
    

Overwrite strategy is generally superior.

---

# 🎯 What Interviewer Is Testing

- Stable partition understanding
    
- Invariant reasoning
    
- In-place memory handling
    
- Write-optimization awareness
    
- Difference between overwrite and swap
    

---

# MINI-NOTE : 

🔹 **Problem**  
Move Zeroes

🔹 **Graph Type**  
Array — Stable In-Place Partition

🔹 **Technique**  
Two Pointers (Same Direction) — Reader/Writer Pattern

🔹 **Core Template**

```cpp
void moveZeroes(vector<int>& nums) {
    int slow = 0;

    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            if (slow != fast) {
                nums[slow] = nums[fast];
            }
            slow++;
        }
    }

    while (slow < nums.size()) {
        nums[slow++] = 0;
    }
}
```

🔹 **Pattern Tag**  
Stable Compaction / Condition-Based Partition

---

🔸 **Logic Summary**

- `slow` = next position to place a non-zero.
    
- `fast` scans entire array.
    
- When `nums[fast] != 0`, copy it forward.
    
- After scan, fill remaining positions with 0.
    
- Maintains relative order of non-zero elements.
    

---

🔸 **Trick**

`slow` represents **next write position**, not last valid index.

Optimization:

```
if (slow != fast)
```

Avoids unnecessary writes when array has no zeroes.

---

🔸 **Why Swap Isn’t Ideal**

- `swap()` = 3 writes.
    
- Overwrite = 1 write.
    
- Optimized overwrite can result in 0 writes when no zeroes exist.
    
- Hence overwrite is memory-efficient.
    

---

🔸 **Why Single Pass Isn’t Enough**

After compaction, leftover values beyond `slow` may still contain old non-zero data.  
We must explicitly fill them with zero.

---

🔸 **Edge Cases**

- All zeros → slow remains 0 → fill entire array with 0 (no change).
    
- No zeros → slow becomes n → second loop doesn’t run.
    
- Single element → naturally handled.
    

---

🔸 **Final Insight**

This is not about zeros.

It’s about:

> Stable in-place compaction based on a boolean condition.

Whenever you see:

- “Move X to end”
    
- “Maintain order”
    
- “In-place”
    

Your brain should trigger:

Reader–Writer Template.
