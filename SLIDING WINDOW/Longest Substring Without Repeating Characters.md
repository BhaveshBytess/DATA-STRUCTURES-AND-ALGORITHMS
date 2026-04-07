## 🔹Problem

Given a string `s`, return the length of the **longest substring without repeating characters**.

---

## 🔹 First Principles Understanding

We are NOT asked to:

- check all substrings ❌
    
- restart from every index ❌
    

We are asked to:

> Maintain a **dynamic window** such that all characters inside it are unique.

---

## 🔹 Core Idea

```text
Expand → break → fix → use
```

We expand the window greedily and shrink only when it becomes invalid.

---

## 🔹 Window Definition

```text
Window [L … R] represents a substring with all UNIQUE characters
```

---

## 🔹 State

We maintain:

```text
freq[256] → frequency of characters in current window
maxLen → maximum valid window length
```

---

## 🔹 Invariant

```text
At any point AFTER shrinking, the window [L … R] contains NO duplicate characters
```

---

## 🔹 Validity Condition

```text
VALID → all characters have frequency ≤ 1  
INVALID → any character has frequency > 1
```

---

## 🔹 Key Observation

```text
Before adding s[R], window [L … R-1] is already valid
```

So:

```text
Only s[R] can violate the condition
```

👉 Hence we check:

```cpp
freq[s[R]] > 1
```

---

## 🔹 Decision / Movement

### Step 1: Expand (R++)

```cpp
freq[s[R]]++;
```

---

### Step 2: Fix Window (if invalid)

```cpp
while (freq[s[R]] > 1) {
    freq[s[L]]--;
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

## 🔹 Stop Condition

Loop ends when `R` reaches end of string.

---

## 🔹 Edge Cases

- Empty string → 0
    
- All same characters → 1
    
- All unique → n
    
- Mixed duplicates → handled dynamically
    

---

## 🔹 C++ Implementation

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> freq(256, 0);

        int L = 0;
        int maxLen = 0;

        for (int R = 0; R < s.size(); R++) {
            freq[s[R]]++;

            while (freq[s[R]] > 1) {
                freq[s[L]]--;
                L++;
            }

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
O(1)  
]  
(assuming ASCII)

---

## 🔹 Pattern Recognition

This is:

> **Variable Sliding Window + Frequency Tracking**

---

## 🔹 Common Mistakes

❌ Updating answer before fixing window  
❌ Comparing positions instead of maintaining frequency  
❌ Re-scanning window for duplicates  
❌ Not maintaining invariant  
❌ Wrong shrinking condition

---

## 🔹 Final Insight

```text
Sliding Window = Maintain validity, not positions
```

---

# 📝 MINI NOTES — Longest Substring Without Repeating Characters

---

🔹 **Problem**  
Find the length of the longest substring with **all unique characters**.

---

🔹 **Graph Type**  
String (Variable Window)

---

🔹 **Technique**  
Sliding Window + Frequency Array

---

🔹 **Core Template**

```cpp
vector<int> freq(256, 0);
int L = 0, maxLen = 0;

for (int R = 0; R < s.size(); R++) {

    freq[s[R]]++;

    while (freq[s[R]] > 1) {
        freq[s[L]]--;
        L++;
    }

    maxLen = max(maxLen, R - L + 1);
}
```

---

🔹 **Pattern Tag**  
Variable Window  
Frequency Control  
Expand–Fix–Use

---

🔸 **Logic Summary**

- Expand R → include char
    
- If duplicate → shrink L until valid
    
- Update max length when valid
    

---

🔸 **Invariant**

```text
Window [L … R] always has all unique characters (after shrinking)
```

---

🔸 **Decision Rule**

|Condition|Action|
|---|---|
|freq[s[R]] == 1|valid → update|
|freq[s[R]] > 1|shrink until fixed|

---

🔸 **Why Only Check s[R]**

```text
Only s[R] was added → only it can break validity
```

---

🔸 **Stop Condition**

```text
R reaches end of string
```

---

🔸 **Edge Cases**

- empty → 0
    
- all same → 1
    
- all unique → n
    

---

🔸 **Common Mistakes**

❌ Shrinking based on position (s[L] == s[R])  
❌ Updating before fixing  
❌ Scanning whole window for duplicates  
❌ Using set without proper removal

---

🔸 **Final Insight**

```text
Don’t search for duplicates — maintain a window where duplicates cannot exist
```

---

