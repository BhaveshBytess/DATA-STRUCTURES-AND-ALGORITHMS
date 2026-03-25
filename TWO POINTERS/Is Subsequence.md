
## 🔹 Problem

Given two strings `s` and `t`, determine if `s` is a subsequence of `t`.

A subsequence means:

> Characters of `s` appear in `t` in the same order (not necessarily contiguous).

---

## 🔹 Mathematical / Structural Model

We need to check if:

[  
s = s_1, s_2, ..., s_k  
]

can be found in order within:

[  
t = t_1, t_2, ..., t_n  
]

Such that indices are increasing:

[  
i_1 < i_2 < ... < i_k  
]

---

## 🔹 First Principles Understanding

This is not substring matching.

This is:

> **Order-preserving sequential matching**

We do NOT need contiguous matches.

---

## 🔹 Core Strategy

- Use two pointers
    
- Scan `t` (the larger string)
    
- Try to match characters of `s` in order
    

---

## 🔹 Pointer Definitions

```id="ptr_subseq"
i → pointer for s (target sequence)
j → pointer for t (search space)
```

---

## 🔹 Invariant

```id="inv_subseq"
Everything before index i in s has been successfully matched.
Everything before index j in t has been scanned and cannot be reused.
```

---

## 🔹 Decision Rule

At each step:

```id="rule_subseq"
if (s[i] == t[j]):
    i++   // match found

j++       // always move in t
```

---

## 🔹 Why This Works

### Case 1: Match

```id="reason_match"
We successfully matched one character of s.
Move to next character in s.
```

---

### Case 2: No Match

```id="reason_nomatch"
We skip t[j] because it does not help match current s[i].
```

---

## 🔹 Why We Do NOT Move i on Mismatch

Because:

```id="reason_no_i"
s[i] is still required.
Skipping it would break subsequence order.
```

We must find this character later in `t`.

---

## 🔹 Stop Condition

```id="stop_subseq"
Return TRUE if i == s.length()
Return FALSE if j == t.length() and i < s.length()
```

---

## 🔹 Edge Cases

- `s` empty → always TRUE
    
- `t` empty → TRUE only if s is empty
    
- s longer than t → always FALSE
    

---

## 🔹 C++ Implementation

```cpp
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;

        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }

        return i == s.size();
    }
};
```

---

## 🔹 Time Complexity

[  
O(n)  
]

Where n = length of t.

---

## 🔹 Space Complexity

[  
O(1)  
]

---

## 🔹 Pattern Recognition

This is:

> **One Stream Matching (Driver + Follower Pattern)**

- `t` → driver (always moves)
    
- `s` → follower (moves only on match)
    

---

## 🔹 Structural Difference (Phase 4 Summary)

|Problem|Movement|
|---|---|
|Merge|Move both conditionally|
|Intersection|Move smaller pointer|
|Subsequence|Move one always, one conditionally|

---

## 🔹 Final Insight

This problem is about:

> Scanning a larger stream to sequentially match a smaller pattern without skipping required characters.



----

# 📝 MINI NOTES — Is Subsequence

---

🔹 **Problem**  
Check if string `s` is a subsequence of string `t`.

---

🔹 **Graph Type**  
String (Two Sequence — One-Sided Scan)

---

🔹 **Technique**  
Two Pointers (Driver + Follower Pattern)

---

🔹 **Core Template**

```cpp
int i = 0, j = 0;

while (i < s.size() && j < t.size()) {
    if (s[i] == t[j]) {
        i++;
    }
    j++;
}

return i == s.size();
```

---

🔹 **Pattern Tag**  
One Stream Matching  
Driver-Follower  
Order Preservation

---

🔸 **Logic Summary**

- Scan `t` (big string)
    
- Try to match `s` sequentially
    
- Move `i` only when match found
    
- Always move `j`
    

---

🔸 **Invariant**

```text
Everything before i in s is matched.
Everything before j in t is processed and cannot be reused.
```

---

🔸 **Decision Rule**

|Condition|Action|Reason|
|---|---|---|
|s[i] == t[j]|i++, j++|matched|
|s[i] != t[j]|j++|skip useless char|

---

🔸 **Why NOT Move i on Mismatch**

Skipping `s[i]` would mean losing required character → breaks subsequence condition.

---

🔸 **Stop Condition**

```text
Return true if i reaches end of s
Return false if t ends first
```

---

🔸 **Edge Cases**

- s empty → always true
    
- t empty → true only if s empty
    
- s longer than t → false
    

---

🔸 **Common Mistakes**

❌ Moving i on mismatch  
❌ Trying substring logic  
❌ Using extra space unnecessarily  
❌ Not understanding order constraint

---

🔸 **Final Insight**

This is not matching both sequences.

This is:

> **Scanning one stream while trying to consume another**

---

# ✅ Phase 4 COMPLETE

You now understand:

- Merge → backward safe placement
    
- Intersection → eliminate smaller
    
- Subsequence → one-sided scan
    

---

# 🚀 What’s Next (Critical)

Natural progression:

👉 Sliding Window (very important for interviews)  
👉 OR Monotonic Stack  
👉 OR Binary Search on Answer

---

Say **“Next Phase”** and we level up.