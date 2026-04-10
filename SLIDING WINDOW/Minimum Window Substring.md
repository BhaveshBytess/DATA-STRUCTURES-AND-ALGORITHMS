
## 🔹 Problem

Given two strings `s` and `t`, return the **minimum window substring of `s`** such that:

```text
Every character in t (including duplicates) exists in the window
```

If no such window exists → return `""`

---

## 🔹 First Principles (Reset Your Brain)

When you see this after months, think:

```text
Contiguous? → YES → Sliding Window
```

But NOT normal sliding window.

---

### 🔥 Key Difference

This is NOT:

- max length
    
- count windows
    
- at most K
    

This is:

```text
Find the SMALLEST window that satisfies an EXACT requirement
```

---

# 🧠 Core Mental Model

We are not asking:

```text
"Is this window valid?"
```

We are maintaining:

```text
"How close is this window to being valid?"
```

---

## 🔹 Window Definition

```text
[L … R] = current substring in s
```

---

## 🔹 State (THIS IS EVERYTHING)

We maintain 4 things:

---

### 1️⃣ expected (need)

```text
What we REQUIRE from t
```

Example:

```text
t = "AABC"

expected:
A → 2
B → 1
C → 1
```

---

### 2️⃣ mp (window)

```text
What we currently HAVE in window
```

---

### 3️⃣ required

```text
Number of UNIQUE characters in t
```

Example:

```text
A, B, C → required = 3
```

---

### 4️⃣ formed (MOST IMPORTANT)

```text
Number of characters whose requirement is satisfied
```

---

## 🔥 CRITICAL DEFINITION

```text
formed increases ONLY when:
window[c] == expected[c]

formed decreases ONLY when:
window[c] < expected[c]
```

---

## 🔴 NOT THIS

```text
"number of matching characters"
```

---

## 🟢 THIS

```text
"number of satisfied constraints"
```

---

# 🔹 VALID WINDOW CONDITION

```text
formed == required
```

👉 This means:

```text
All requirements satisfied
```

---

# 🔥 THE BIG SHIFT (Phase 3)

|Phase 2|Phase 3|
|---|---|
|Shrink when invalid|Shrink when valid|
|Maximize|Minimize|

---

## 🔹 Decision Flow

---

### Step 1: Expand

Always move `R`

```cpp
mp[s[R]]++;
```

If:

```cpp
mp[s[R]] == expected[s[R]]
```

👉 `formed++`

---

### Step 2: When VALID

```text
formed == required
```

👉 Now shrink to minimize

---

### Step 3: Shrink

While valid:

- update answer
    
- remove `s[L]`
    
- if requirement breaks → stop
    

---

# 🔥 Why Shrink?

```text
We are not fixing the window,
we are optimizing it
```

---

# 🔹 Answer Update

```text
When window is VALID → try to minimize
```

---

# 🔹 C++ Code (Your Style, Fixed)

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size()) return "";

        unordered_map<char, int> mp;
        unordered_map<char, int> expected;

        for (auto x : t)
            expected[x]++;

        int required = expected.size();
        int formed = 0;

        int L = 0;
        int minlen = INT_MAX;
        int start = 0;

        for (int R = 0; R < s.size(); R++) {

            mp[s[R]]++;

            if (expected.count(s[R]) && mp[s[R]] == expected[s[R]])
                formed++;

            while (formed == required) {

                if (R - L + 1 < minlen) {
                    minlen = R - L + 1;
                    start = L;
                }

                mp[s[L]]--;

                if (expected.count(s[L]) && mp[s[L]] < expected[s[L]])
                    formed--;

                L++;
            }
        }

        if (minlen == INT_MAX) return "";

        return s.substr(start, minlen);
    }
};
```

---

# 🔹 Time Complexity

```text
O(n)
```

👉 Each pointer moves at most once

---

# 🔹 Space Complexity

```text
O(k)
```

👉 where k = unique chars in t

---

# 🔥 Common Mistakes (YOU MADE THESE)

---

❌ Checking validity by looping over map  
❌ Using `<` instead of `==` for formed  
❌ Not guarding with `expected.count()`  
❌ Shrinking on wrong condition  
❌ Trying Phase 2 logic

---

# 🧠 Reconstruction Trigger (MOST IMPORTANT PART)

When you revisit this problem after months:

---

### Think in this order:

```text
1. Exact requirement → NOT at most
2. Need vs Have maps
3. Track satisfaction → formed
4. Valid = formed == required
5. Expand always
6. Shrink when valid (NOT invalid)
7. Minimize window
```

---

# ⚔️ ONE LINE MEMORY

```text
Don’t check validity,
track when it becomes valid
```

---

# 🧠 FINAL FEELING YOU SHOULD HAVE

You are not sliding pointers.

```text
You are controlling a system of constraints
```

---

If this clicked, you’ve crossed:

```text
Phase 3 entry barrier
```

---

