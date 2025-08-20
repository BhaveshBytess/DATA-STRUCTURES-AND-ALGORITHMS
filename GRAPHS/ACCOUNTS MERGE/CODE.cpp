#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unionSet(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DSU dsu(n);

        unordered_map<string, int> emailToIndex; // maps email -> account index

        // Step 1: Union accounts that share emails
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                if (emailToIndex.count(email)) {
                    dsu.unionSet(i, emailToIndex[email]);
                } else {
                    emailToIndex[email] = i;
                }
            }
        }

        // Step 2: Gather emails under their parent (representative account)
        unordered_map<int, set<string>> merged;
        for (auto &p : emailToIndex) {
            string email = p.first;
            int owner = dsu.find(p.second);
            merged[owner].insert(email);
        }

        // Step 3: Build final result
        vector<vector<string>> result;
        for (auto &entry : merged) {
            vector<string> account;
            account.push_back(accounts[entry.first][0]); // account name
            account.insert(account.end(), entry.second.begin(), entry.second.end());
            result.push_back(account);
        }

        return result;
    }
};
