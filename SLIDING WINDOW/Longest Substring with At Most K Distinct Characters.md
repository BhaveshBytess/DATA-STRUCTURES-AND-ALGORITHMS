## 🔹 Problem

Given a string `s` and an integer `k`, return the **length of the longest substring** that contains **at most `k` distinct characters**.

---

## 🔹 First Principles Understanding

We are NOT asked to:

- check all substrings ❌
    
- recompute distinct counts ❌
    

We are asked to:

> Maintain a **dynamic window** such that number of distinct characters ≤ k

---

## 🔹 Core Idea

```text
Expand → Break → Fix → Use
```

---

## 🔹 Window Definition

```text
Window [L … R] represents a substring
```

---

## 🔹 State

We maintain:

```text
unordered_map<char, int> freq
distinct → number of unique characters
maxLen → best answer
```

---

## 🔹 Invariant

```text
After shrinking, window [L … R] always satisfies:
distinct ≤ k
```

---

## 🔹 Validity Condition

```text
VALID   → distinct ≤ k  
INVALID → distinct > k
```

---

## 🔹 Decision / Movement

### Step 1: Expand (R++)

```cpp
freq[s[R]]++;
if (freq[s[R]] == 1) distinct++;
```

---

### Step 2: Fix Window

```cpp
while (distinct > k) {
    freq[s[L]]--;
    if (freq[s[L]] == 0) distinct--;
    L++;
}
```

---

### Step 3: Update Answer

```cpp
maxLen = max(maxLen, R - L + 1);
```

---

## 🔹 Why This Works

Each character:

```text
Added once → when R includes it  
Removed once → when L excludes it
```

👉 Total:

[  
O(n)  
]

---

## 🔹 C++ Implementation (Final)

```cpp
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> freq;
        
        int L = 0;
        int distinct = 0;
        int maxLen = 0;

        for (int R = 0; R < s.size(); R++) {

            // include R
            freq[s[R]]++;
            if (freq[s[R]] == 1) distinct++;

            // fix window
            while (distinct > k) {
                freq[s[L]]--;
                if (freq[s[L]] == 0) distinct--;
                L++;
            }

            // update answer
            maxLen = max(maxLen, R - L + 1);
        }

        return maxLen;
    }
};
```

---

## 🔹 Time Complexity

[  
O(n)  
]

---

## 🔹 Space Complexity

[  
O(k)  
]  
(at most k distinct characters in window)

---

## 🔹 Pattern Recognition

This is:

> **Variable Sliding Window + Frequency Constraint**

---

## 🔹 Common Mistakes

❌ Updating answer before fixing window  
❌ Checking freq before decrement  
❌ Not updating distinct correctly  
❌ Trying Phase 1 “math adjustment”

---

## 🔹 Final Insight

```text
Distinct count changes ONLY when freq goes from 0 ↔ 1
```

---

## 🔹 Interview Insight

This problem tests:

- frequency tracking
    
- correct shrink logic
    
- invariant maintenance
    

---

## 🔥 Final One-Line Memory

```text
Add → track distinct → shrink if > k → update
```

---
Perfect. Let’s compress it into your **fast-recall weapon**.

---

# 📝 MINI NOTES — Longest Substring with At Most K Distinct Characters


🔹 **Problem**  
Longest substring with ≤ k distinct characters

---

🔹 **Graph Type**  
String / Array

---

🔹 **Technique**  
Sliding Window (Variable + Frequency Map)

---

🔹 **Core Template**

```cpp
mp[s[R]]++;
if (mp[s[R]] == 1) distinct++;

while (distinct > k) {
    mp[s[L]]--;
    if (mp[s[L]] == 0) distinct--;
    L++;
}

maxLen = max(maxLen, R - L + 1);
```

---

🔹 **Pattern Tag**  
Variable Window  
Frequency Constraint  
Distinct Count

---

🔸 **Logic Summary**

- Expand R → update freq
    
- If new char → distinct++
    
- If distinct > k → shrink
    
- When freq hits 0 → distinct--
    
- After fix → update answer
    

---

🔸 **Invariant**

```text
Window always has ≤ k distinct characters (after shrinking)
```

---

🔸 **Decision Rule**

|Condition|Action|
|---|---|
|distinct ≤ k|valid → update|
|distinct > k|shrink until valid|

---

🔸 **Key Trick**

```text
Character leaves window ONLY when freq becomes 0
```

---

🔸 **Why Phase 1 logic fails**

```text
Cannot “adjust mathematically”
Must track exact structure (freq map)
```

---

🔸 **Common Mistakes**

❌ Updating before shrinking  
❌ Wrong distinct update timing  
❌ Checking before decrement  
❌ Forgetting freq==0 condition

---

🔸 **Final Insight**

```text
Track structure, not just numbers
```

---

