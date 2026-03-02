
## 🟢 Problem: Remove Element

---

## 🔹 Problem Statement

Given an integer array `nums` and an integer `val`, remove all occurrences of `val` **in-place**.

Return the number of elements not equal to `val`.

After the function returns:

- The first `k` elements of `nums` must contain elements not equal to `val`.
    
- The remaining elements do not matter.
    
- The order of remaining elements **does not need to be preserved**.
    

Constraints:

- `0 <= nums.length <= 100`
    
- `0 <= nums[i] <= 50`
    
- `0 <= val <= 100`
    

---

# 🧠 First Principles Understanding

This problem is not about deletion.

It is about:

> Shrinking the valid region of an array by discarding unwanted elements.

Key difference from Move Zeroes:

⚠️ Order does NOT need to be preserved.

That unlocks a more optimal strategy.

---

# 🧩 Pattern Classification

Two possible solutions:

### 1️⃣ Same Direction (Reader–Writer)

Stable compaction.

### 2️⃣ Opposite Direction (Shrinking Window) ✅ Optimal when order not required.

Signal:

- “Remove X”
    
- “Remaining elements don’t matter”
    
- “In-place”
    
- No order constraint
    

Your brain should consider two-end shrink.

---

# 🟢 Optimal Approach — Opposite Direction

---

## 📌 Invariant

At any time:

```
nums[0 … left-1] → confirmed NOT equal to val
nums[left … right] → unknown
nums[right+1 … n-1] → confirmed equal to val (discard zone)
```

---

## ⚙️ Algorithm Logic

1. Initialize:
    
    ```
    left = 0
    right = n - 1
    ```
    
2. While `left <= right`:
    
    - If `nums[left] == val`:
        
        - Replace `nums[left]` with `nums[right]`
            
        - Decrement `right`
            
        - Do NOT increment `left`
            
    - Else:
        
        - Increment `left`
            
3. Return `left`
    

---

## 🧠 Why Not Increment `left` After Replacement?

Because the value copied from `right` might also equal `val`.

It must be rechecked.

That is a subtle but critical detail.

---

# 🧪 Dry Run

Input:

```
nums = [3,2,2,3], val = 3
```

Process:

```
left=0, right=3
nums[0]==3 → replace with nums[3] → 3 → right=2
left still 0

nums[0]==3 → replace with nums[2] → 2 → right=1
left still 0

nums[0]==2 → keep → left=1
nums[1]==2 → keep → left=2
```

Stop.

Return 2.

Valid region:

```
[2,2]
```

---

# 💻 C++ Implementation (Optimal Version)

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            if (nums[left] == val) {
                nums[left] = nums[right];
                right--;
            } else {
                left++;
            }
        }

        return left;
    }
};
```

---

# ⏱ Complexity

- Time: O(n)
    
- Space: O(1)
    

---

# 🔄 Alternative (Reader–Writer Version)

```cpp
int removeElement(vector<int>& nums, int val) {
    int slow = 0;

    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != val) {
            nums[slow++] = nums[fast];
        }
    }

    return slow;
}
```

This preserves order.

---

# ⚔️ Comparison

|Approach|Preserves Order|Writes|
|---|---|---|
|Reader–Writer|Yes|Writes for every kept element|
|Opposite Shrink|No|Writes only when val found|

If order not required → opposite-direction is better signal.

---

# 🎯 What Interviewer Is Testing

- Recognition that order doesn’t matter
    
- Ability to change pointer strategy
    
- Shrinking window invariant
    
- Re-check logic after replacement
    
- Clean termination condition
    

---

# MINI-NOTE : 

🔹 **Problem**  
Remove Element

🔹 **Graph Type**  
Array — In-place Shrinking Window

🔹 **Technique**  
Two Pointers (Opposite Direction) — Window Shrink Pattern

🔹 **Core Template**

```cpp
int removeElement(vector<int>& nums, int val) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        if (nums[left] == val) {
            nums[left] = nums[right];
            right--;
        } else {
            left++;
        }
    }

    return left;
}
```

🔹 **Pattern Tag**  
Unstable In-Place Removal / Shrinking Boundary

---

🔸 **Logic Summary**

- `[0 … left-1]` → confirmed valid (not equal to val)
    
- `[left … right]` → unknown
    
- `[right+1 … n-1]` → discarded (equal to val)
    

If `nums[left] == val`:

- Replace it with `nums[right]`
    
- Shrink right boundary
    
- Re-check current index
    

Else:

- Expand valid region (`left++`)
    

Return `left` as count of valid elements.

---

🔸 **Trick**

Do NOT increment `left` after replacement.

Because the new value copied from `right` might also equal `val`.

This is the common mistake.

---

🔸 **Why Reader–Writer Also Works**

If order must be preserved:

```cpp
if (nums[fast] != val)
    nums[slow++] = nums[fast];
```

But this performs more writes.

---

🔸 **Why Opposite Direction Is Better Here**

Problem states:

> “Remaining elements do not matter.”

This signals:

- Order irrelevant
    
- Use shrinking window
    
- Minimize writes
    

---

🔸 **Edge Cases**

- All elements equal `val` → return 0
    
- No element equals `val` → return n
    
- Single element → handled naturally
    

---

🔸 **Final Insight**

When you see:

- “Remove X”
    
- “In-place”
    
- “Order does not matter”
    

Your brain must trigger:

Opposite Direction Shrinking Pattern.

---
