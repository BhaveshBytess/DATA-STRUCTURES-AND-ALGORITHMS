## 🔹 Problem

Given a string `s` and an integer `k`, return the **maximum number of vowels** in any substring of length `k`.

---

## 🔹 Graph Type

Array / String (Contiguous Window)

---

## 🔹 Technique

Sliding Window — **Fixed Size (Phase 0)**

---

## 🔹 Core Template

```cpp
int L = 0;
for (int R = 0; R < n; R++) {

    // include R
    update_state();

    if (R - L + 1 == k) {

        update_answer();

        // remove L
        remove_state();

        L++;
    }
}
```

---

## 🔹 Pattern Tag

`Fixed Window + Count Tracking`

---

# 🔸 Logic Summary

We maintain a **window of size k** and track:

👉 `count = number of vowels in current window`

Steps:

1. Expand window by moving `R`
    
2. If `s[R]` is vowel → `count++`
    
3. When window size reaches `k`:
    
    - Update answer using `count`
        
    - Remove `s[L]` from window
        
    - If `s[L]` is vowel → `count--`
        
    - Move `L++`
        

👉 This avoids recomputing window → O(n)

---

# 🔸 Trick

👉 **Never recompute window sum/count**

Instead:

- Add when entering (`R`)
    
- Remove when exiting (`L`)
    

This converts:

❌ O(n * k) → brute  
✅ O(n) → optimal

---

# 🔸 Why naive approach fails

### ❌ Recomputing each window

```cpp
for each window:
    loop k times → count vowels
```

👉 Time: O(n * k)

Too slow.

---

# 🔸 Why Two Pointers alone won’t work

Two pointers (comparison-based) need:

- sorted / monotonic behavior
    

Here:

👉 No ordering  
👉 Pure contiguous constraint

So we use **Sliding Window**

---

# 🔸 Final Insight

> Sliding Window is NOT about pointers  
> It’s about maintaining a **valid region efficiently**

For fixed window:

👉 No “invalid condition”  
👉 Only “maintain exact size”

---

# 🧠 Invariant

At every step:

```text
Window [L … R] contains exactly k elements
count = vowels inside this window
```

---

# ⚡ Complexity

- Time: **O(n)**
    
- Space: **O(1)**
    

---

# 🧠 Interview Insight

This problem tests:

- Can you avoid recomputation?
    
- Can you maintain state incrementally?
    
- Do you understand fixed window mechanics?
    

---

# 🔥 Final Thought

You didn’t fail this problem.

You just hadn’t:

- formalized the template
    
- trusted your incremental logic
    

Now you have both.

---

# MINI-NOTE :

🔹 **Problem**  
Max vowels in any substring of size `k`

---

🔹 **Graph Type**  
Array / String

---

🔹 **Technique**  
Sliding Window (Fixed Size)

---

🔹 **Core Template**

```cpp
if (isVowel(s[R])) count++;

if (R - L + 1 == k) {
    ans = max(ans, count);

    if (isVowel(s[L])) count--;

    L++;
}
```

---

🔹 **Pattern Tag**  
Fixed Window + Incremental Count

---

🔸 **Logic Summary**

- Expand `R`
    
- Add vowel → `count++`
    
- When window size = k:
    
    - Update answer
        
    - Remove L effect
        
    - Move L
        

---

🔸 **Trick**

👉 Add on enter, remove on exit  
👉 Never recompute window

---

🔸 **Why brute fails**

Recomputing each window → **O(n·k)** ❌

---

🔸 **Why not Two Pointers**

No ordering / monotonic property

---

🔸 **Final Insight**

👉 Fixed window = no shrinking loop  
👉 Just maintain exact size

---

🔥 **One-line memory**

> “Count vowels while sliding fixed window of size k”

---
