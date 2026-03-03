
## 🔹 Problem

Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

---

## 🔹 Mathematical Model

For each index `i`:

[
water[i] = \min(maxLeft[i], maxRight[i]) - height[i]
]

Where:

* `maxLeft[i]` = maximum height from index `0 → i`
* `maxRight[i]` = maximum height from index `i → n-1`

If result is negative → treat as 0.

Total water = sum of water[i].

---

## 🔹 First Principles Understanding

Water at any index is limited by:

* The tallest wall on the left
* The tallest wall on the right

The lower of these two determines the water level.

This is a **boundary-limited accumulation problem**, not a pair optimization problem.

---

## 🔹 Brute Force Approach

For every index:

* Scan left to find max
* Scan right to find max

Time Complexity:

[
O(n^2)
]

Too slow.

---

## 🔹 Optimization 1 — Prefix Max Arrays (DP)

Precompute:

```id="7m52gk"
leftMax[i] = max(height[0…i])
rightMax[i] = max(height[i…n-1])
```

Then:

```id="xmr3df"
water += min(leftMax[i], rightMax[i]) - height[i]
```

Time: O(n)
Space: O(n)

---

## 🔹 Optimization 2 — Two Pointer (O(1) Space)

### Core Insight

At any step:

* If `leftMax < rightMax`
  → Water at left is determined
* Else
  → Water at right is determined

Because:

[
water[i] = \min(maxLeft, maxRight) - height[i]
]

If leftMax < rightMax:

[
\min(leftMax, rightMax) = leftMax
]

Right side cannot reduce water level.

So left can be finalized.

---

## 🔹 Invariant

At every iteration:

* `leftMax = max(height[0…left])`
* `rightMax = max(height[right…n-1])`

We process the side with smaller max boundary.

Each processed index is finalized permanently.

---

## 🔹 Correct C++ Implementation

```cpp id="c0ol0q"
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int leftMax = 0;
        int rightMax = 0;
        int water = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax)
                    leftMax = height[left];
                else
                    water += leftMax - height[left];
                left++;
            } else {
                if (height[right] >= rightMax)
                    rightMax = height[right];
                else
                    water += rightMax - height[right];
                right--;
            }
        }

        return water;
    }
};
```

---

## 🔹 Time Complexity

Each pointer moves at most `n` times.

[
O(n)
]

---

## 🔹 Space Complexity

[
O(1)
]

---

## 🔹 Why We Compare height[left] < height[right]

This ensures that:

* The side we process has a guaranteed limiting boundary.
* The opposite side is tall enough not to interfere.

This allows safe elimination.

---

## 🔹 Why We DO NOT Use min(leftMax, rightMax) Directly

Because when we decide to process one side,
we already know which boundary is smaller.

So:

* If processing left → water = leftMax - height[left]
* If processing right → water = rightMax - height[right]

No need for min().

---

## 🔹 Structural Difference From Container Problem

| Container                | Rain Water                     |
| ------------------------ | ------------------------------ |
| Pair-based               | Per-index accumulation         |
| Compare heights          | Compare max boundaries         |
| Maximize area            | Sum bounded water              |
| Eliminate smaller height | Eliminate smaller max boundary |

Different invariant. Different reasoning.

---

## 🔹 When This Logic Fails

If heights were negative:

* Boundary logic breaks
* Water formula invalid

Greedy relies on non-negative heights.

---

## 🔹 Final Insight

This problem works because:

> Once the smaller boundary max is known, water at that side is fully determined and can be safely finalized.

This is a boundary-elimination problem with dynamic maxima.

---

# MINI-NOTE : 

🔹 **Problem**
Given elevation heights, compute total water trapped after rain.

---

🔹 **Graph Type**
Array (Boundary Accumulation / Two Pointer Greedy)

---

🔹 **Technique**
Two Pointers + Dynamic Max Tracking
Greedy Boundary Finalization

---

🔹 **Core Template**

```cpp
int left = 0, right = n - 1;
int leftMax = 0, rightMax = 0;
int water = 0;

while (left < right) {
    if (height[left] < height[right]) {
        if (height[left] >= leftMax)
            leftMax = height[left];
        else
            water += leftMax - height[left];
        left++;
    } else {
        if (height[right] >= rightMax)
            rightMax = height[right];
        else
            water += rightMax - height[right];
        right--;
    }
}
return water;
```

---

🔹 **Pattern Tag**
Greedy Boundary Elimination
Dynamic Prefix/Suffix Max
Per-Index Finalization

---

🔸 **Logic Summary**

Water at index `i`:

[
water[i] = \min(maxLeft, maxRight) - height[i]
]

If `leftMax < rightMax`:

* Water at left depends only on `leftMax`
* Right boundary is guaranteed taller
* Finalize left and move forward

Else:

* Finalize right

Each step permanently processes one index.

---

🔸 **Trick**

* Compare heights to decide direction.
* Use max-so-far values to compute water.
* Never use `min(leftMax, rightMax)` directly inside loop.
* Process only one side per iteration.

---

🔸 **Why Container Logic Won’t Work**

Container:

* Depends on pair width.
* Limiting factor = smaller height.

Rain Water:

* Depends on global max boundaries.
* Limiting factor = smaller max boundary.

Different invariant.

---

🔸 **Why We Track leftMax & rightMax**

Immediate neighbors are not enough.

Water depends on tallest wall seen so far.

Example:
`[4,1,0,2]`
Water at index 2 depends on 4, not 1.

---

🔸 **Why Greedy Works**

When `leftMax < rightMax`:

[
\min(leftMax, rightMax) = leftMax
]

So water at left is fully determined.

Safe elimination.

---

🔸 **Why Heights Must Be Non-Negative**

If negative heights allowed:

* Monotonicity breaks
* Water formula invalid
* Elimination proof collapses

---

🔸 **Final Insight**

This is not a pair optimization problem.

It is a boundary-limited accumulation problem.

Each pointer move finalizes exactly one index permanently.

