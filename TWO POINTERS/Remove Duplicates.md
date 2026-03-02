
## 🟢 Problem: Remove Duplicates from Sorted Array

---

## 🔹 Problem Statement

Given a **sorted integer array `nums`** in non-decreasing order, remove duplicates **in-place** such that each unique element appears only once.

Return the number of unique elements `k`.

After the function returns:

- The first `k` elements of `nums` must contain the unique elements.
    
- The remaining elements beyond `k` do not matter.
    

Constraints:

- `1 <= nums.length <= 3 * 10^4`
    
- `-100 <= nums[i] <= 100`
    
- Array is sorted.
    

---

# 🧠 First Principles Understanding

### What is this problem really asking?

Not “remove duplicates”.

It is asking:

> Compact unique elements to the front of a sorted array using O(1) extra space.

This is **in-place stable compaction**.

---

# 🏗 Why Sorting Is Critical

Sorted array guarantees:

- All duplicates appear consecutively.
    
- If `nums[i] != nums[i-1]`, it must be a new unique value.
    

Without sorting:  
You would need a set or hash map.  
Time or space complexity would increase.

Sorting gives us **local duplicate detection**.

---

# 🧩 Pattern Classification

- Technique: Same Direction Two Pointers
    
- Subtype: Reader–Writer Pattern
    
- Category: In-place Array Compaction
    
- Signal: “Sorted array” + “remove duplicates” + “O(1) space”
    

---

# 📌 Invariant

At any point:

```
nums[0 … slow] → contains all unique elements found so far
nums[slow+1 … fast-1] → irrelevant
nums[fast … end] → unexplored
```

More precisely:

> `slow` stores the index of the last unique element.

---

# ⚙️ Algorithm Logic

1. First element is always unique → initialize `slow = 0`
    
2. Start scanning from index 1
    
3. If `nums[fast] != nums[slow]`:
    
    - Increment `slow`
        
    - Copy `nums[fast]` into `nums[slow]`
        
4. Continue until end
    
5. Return `slow + 1`
    

---

# 🧪 Dry Run

Input:

```
[0,0,1,1,1,2,2,3,3,4]
```

Step-by-step unique build:

```
0
0 (skip)
1 → copy
1 (skip)
1 (skip)
2 → copy
2 (skip)
3 → copy
3 (skip)
4 → copy
```

Final array:

```
[0,1,2,3,4,_,_,_,_,_]
```

slow = 4  
Return 5.

---

# 💻 C++ Implementation

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int slow = 0;

        for (int fast = 1; fast < nums.size(); fast++) {
            if (nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            }
        }

        return slow + 1;
    }
};
```

---

# ⏱ Complexity

- Time: O(n)
    
- Space: O(1)
    

---

# ❌ Why Other Approaches Fail

### 1. Using Set

- Extra space O(n)
    
- Breaks in-place requirement
    

### 2. Nested Loops

- O(n²)
    
- Unacceptable for 3×10⁴ constraint
    

### 3. Sorting Again

- Already sorted
    
- Unnecessary work
    

---

# 🎯 What Interviewer Is Testing

- Recognition of sorted property
    
- Invariant reasoning
    
- Zero-based index vs count understanding
    
- In-place array manipulation
    
- Off-by-one correctness
    

If candidate cannot explain `slow + 1`, they lack depth.

---

# 🧠 Subtle Insight

`slow` tracks index of last valid element — not count.

Valid region size:

```
slow - 0 + 1
```

= `slow + 1`

This is a common off-by-one trap.

---

# MINI-NOTE : 


🔹 **Problem**  
Remove Duplicates from Sorted Array

🔹 **Graph Type**  
Array (Sorted) — In-place Compaction

🔹 **Technique**  
Two Pointers (Same Direction) — Reader/Writer Pattern

🔹 **Core Template**

```cpp
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int slow = 0;

    for (int fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }

    return slow + 1;
}
```

🔹 **Pattern Tag**  
Stable In-Place Compaction (Sorted Input)

---

🔸 **Logic Summary**

- First element is always unique.
    
- `slow` tracks index of last unique element.
    
- `fast` scans for next new value.
    
- When `nums[fast] != nums[slow]`, we found new unique.
    
- Expand valid region by moving `slow` forward.
    
- Return `slow + 1` (size = last index + 1).
    

---

🔸 **Trick**

`slow` stores **index**, not count.  
Final answer = `slow + 1`.

Sorted property guarantees duplicates are adjacent.  
That’s why local comparison works.

---

🔸 **Why HashSet Won’t Work (Interview Constraint)**

- Violates O(1) space requirement.
    
- In-place modification is mandatory.
    
- Sorted structure already gives duplicate detection for free.
    

---

🔸 **Why Brute Force Won’t Work**

- Nested loops → O(n²)
    
- 3×10⁴ worst-case input → unacceptable.
    

---

🔸 **Final Insight**

This is not about duplicates.

It is about:

> Compressing a sorted array in-place using a moving boundary.

The moment you see:

- Sorted array
    
- Remove duplicates
    
- O(1) space
    

Your brain should auto-trigger:

Reader–Writer Template.

---

Phase 1 — Problem 1 documented.

Ready to create docs for **Move Zeroes** next?