#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        // Step 1: Initialize graph
        unordered_map<char, unordered_set<char>> adj; // adjacency list
        unordered_map<char, int> indegree;            // in-degree count

        // Add all unique chars to indegree map
        for (auto& word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }

        // Step 2: Build graph from adjacent word comparisons
        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i];
            string w2 = words[i + 1];
            int len = min(w1.size(), w2.size());
            bool found = false;

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    if (!adj[w1[j]].count(w2[j])) { 
                        adj[w1[j]].insert(w2[j]);
                        indegree[w2[j]]++;
                    }
                    found = true;
                    break; // Only first difference matters
                }
            }

            // Invalid case: prefix problem
            if (!found && w1.size() > w2.size()) {
                return "";
            }
        }

        // Step 3: BFS (Kahn's algorithm)
        queue<char> q;
        for (auto& [c, deg] : indegree) {
            if (deg == 0) q.push(c);
        }

        string result;
        while (!q.empty()) {
            char u = q.front();
            q.pop();
            result.push_back(u);

            for (char v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Step 4: Check if valid topo order exists
        if (result.size() < indegree.size()) {
            return ""; // cycle detected
        }

        return result;
    }
};
