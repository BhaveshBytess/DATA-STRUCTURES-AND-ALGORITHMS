#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        // Step 1: Build graph
        unordered_map<char, unordered_set<char>> adj;
        unordered_map<char, int> visited; 
        // visited states: 0 = unvisited, 1 = visiting, 2 = visited

        for (auto& w : words) {
            for (char c : w) visited[c] = 0; // register all chars
        }

        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i], w2 = words[i + 1];
            int len = min(w1.size(), w2.size());
            bool found = false;

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    adj[w1[j]].insert(w2[j]);
                    found = true;
                    break;
                }
            }

            // invalid case: prefix
            if (!found && w1.size() > w2.size()) return "";
        }

        // Step 2: DFS topo sort
        string result;
        for (auto& [c, _] : visited) {
            if (visited[c] == 0) {
                if (!dfs(c, adj, visited, result)) return ""; // cycle detected
            }
        }

        reverse(result.begin(), result.end());
        return result;
    }

private:
    bool dfs(char c, unordered_map<char, unordered_set<char>>& adj,
             unordered_map<char, int>& visited, string& result) {
        if (visited[c] == 1) return false; // cycle
        if (visited[c] == 2) return true;  // already done

        visited[c] = 1; // visiting
        for (char nei : adj[c]) {
            if (!dfs(nei, adj, visited, result)) return false;
        }

        visited[c] = 2; // done
        result.push_back(c);
        return true;
    }
};
