
## 🔹 Problem

You are given an integer array `height` of length `n`.

There are `n` vertical lines drawn such that the two endpoints of the i-th line are `(i, 0)` and `(i, height[i])`.

Find two lines that together with the x-axis form a container that holds the most water.

Return the maximum amount of water a container can store.

---

## 🔹 Mathematical Model

If we choose indices `i` and `j`:

[  
Area = (j - i) \times \min(height[i], height[j])  
]

Where:

- `(j - i)` = width
    
- `min(height[i], height[j])` = limiting height
    

---

## 🔹 First Principles Understanding

We are maximizing:

[  
f(i, j) = width \times limiting_height  
]

Two key observations:

1. Width strictly decreases as pointers move inward.
    
2. Area is limited by the smaller wall.
    

This creates a monotonic elimination structure.

---

## 🔹 Why Brute Force Fails

Brute force:

- Check all pairs
    
- Time complexity:  
    [  
    O(n^2)  
    ]
    

For ( n = 10^5 ), this is too slow.

We need linear time.

---

## 🔹 Core Insight (Greedy Elimination Principle)

If:

[  
height[left] < height[right]  
]

Then:

- `height[left]` is limiting.
    
- Any container using this `left` index has already been evaluated at maximum width.
    
- Shrinking width while keeping same limiting height can never increase area.
    

Therefore:

👉 Discard the smaller height pointer.

This is safe elimination.

---

## 🔹 Invariant

At every step:

- All containers using discarded boundaries are provably suboptimal.
    
- `maxArea` stores maximum seen so far.
    

---

## 🔹 Decision Rule

```
If height[left] < height[right]
    move left++
else
    move right--
```

Move the smaller height.

---

## 🔹 Stop Condition

```
while (left < right)
```

When pointers meet, search space exhausted.

---

## 🔹 Edge Cases

- n < 2 → return 0
    
- All heights equal
    
- Strictly increasing heights
    
- Strictly decreasing heights
    

Algorithm handles all.

---

## 🔹 Time Complexity

Each pointer moves at most n times.

[  
O(n)  
]

Optimal.

---

## 🔹 Space Complexity

[  
O(1)  
]

---

## 🔹 Correct C++ Implementation

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        long long maxArea = 0;

        while (left < right) {
            long long currentArea =
                1LL * min(height[left], height[right]) * (right - left);

            maxArea = max(maxArea, currentArea);

            if (height[left] < height[right])
                left++;
            else
                right--;
        }

        return (int)maxArea;
    }
};
```

---

## 🔹 Why We Do NOT Sort

Sorting destroys index positions.  
Width depends on original geometry.

This is a positional optimization problem.

---

## 🔹 Why Greedy Works (Formal Reason)

If:

[  
height[left] < height[right]  
]

Then:

[  
NewArea \le (right - left - 1) \times height[left]  
]

Which is strictly smaller than current area using that left.

So left can be permanently eliminated.

---

## 🔹 When Greedy Would Fail

Greedy depends on:

- Heights ≥ 0
    
- Width strictly decreasing
    
- Smaller wall limiting area
    

If heights were negative → proof collapses.

If formula used `max(height[left], height[right])` → elimination fails.

If formula used `|height[left] - height[right]|` → no monotonic bound → fails.

---

## 🔹 Interview Deep Insight

This problem works because:

> The limiting factor is tied to one boundary and creates a provable upper bound.

That is why two-pointer greedy is valid.

---

# MINI-NOTE : 


🔹 **Problem**  
Container With Most Water — Given heights of vertical lines, find two lines forming maximum water container.

---

🔹 **Graph Type**  
Array (Geometric / Greedy Two-Pointer Optimization)

---

🔹 **Technique**  
Opposite Direction Two Pointers  
Greedy Elimination with Monotonic Upper Bound

---

🔹 **Core Template**

```cpp
int left = 0, right = n - 1;
long long maxArea = 0;

while (left < right) {
    long long area =
        1LL * min(height[left], height[right]) * (right - left);

    maxArea = max(maxArea, area);

    if (height[left] < height[right])
        left++;
    else
        right--;
}

return maxArea;
```

---

🔹 **Pattern Tag**  
Greedy Boundary Elimination  
Monotonic Width Shrinking  
Limiting Boundary Optimization

---

🔸 **Logic Summary**

- Area = width × min(height[left], height[right])
    
- Smaller wall limits container.
    
- Shrinking width always decreases potential area.
    
- So eliminate smaller wall.
    
- Every eliminated boundary is proven suboptimal.
    

Greedy works because:

> For fixed limiting height, smaller width cannot produce larger area.

---

🔸 **Trick**

- Move the smaller height pointer.
    
- Sorting is NOT allowed (destroys geometry).
    
- Use `long long` if constraints are large.
    

---

🔸 **Why Moving Larger Pointer Won’t Work**

If smaller wall limits area:

[  
Area = width × smallerHeight  
]

Shrinking width while keeping same limiting height can never increase area.

So moving larger pointer is useless.

---

🔸 **Why Negative Heights Break Logic**

Greedy relies on:

[  
Area ≥ 0  
]

If height < 0:

Shrinking width may increase area magnitude (less negative).

Monotonicity collapses → elimination unsafe.

---

🔸 **Why This Logic Fails for |hL − hR| Version**

Difference depends on both sides symmetrically.

No single boundary controls objective.

No monotonic upper bound → greedy fails.

---

🔸 **Final Insight**

Greedy works when:

1. Objective has clear limiting boundary.
    
2. Width shrinking strictly reduces potential.
    
3. Eliminated boundary can be mathematically proven useless.
    

Container With Most Water satisfies all three.

---
