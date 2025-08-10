class Solution {
public:
    bool isOneCharDiff(const string& a, const string& b) {
        int diff = 0;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) ++diff;
            if (diff > 1) return false;
        }
        return diff == 1;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (find(wordList.begin(), wordList.end(), endWord) == wordList.end())
            return 0;

        wordList.push_back(beginWord);
        unordered_map<string, vector<string>> adj;

        for (int i = 0; i < wordList.size(); ++i) {
            for (int j = i + 1; j < wordList.size(); ++j) {
                if (isOneCharDiff(wordList[i], wordList[j])) {
                    adj[wordList[i]].push_back(wordList[j]);
                    adj[wordList[j]].push_back(wordList[i]);
                }
            }
        }

        queue<pair<string, int>> q;
        unordered_set<string> visited;
        q.push({beginWord, 1});
        visited.insert(beginWord);

        while (!q.empty()) {
            auto [word, steps] = q.front(); q.pop();
            if (word == endWord) return steps;

            for (const string& neighbor : adj[word]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push({neighbor, steps + 1});
                }
            }
        }

        return 0;
    }
};
