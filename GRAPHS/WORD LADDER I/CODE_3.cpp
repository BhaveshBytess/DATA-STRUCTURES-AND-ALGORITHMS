class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord)) return 0;

        unordered_map<string, vector<string>> patternMap;
        int L = beginWord.length();

        // Preprocess: build pattern map
        for (string& word : wordSet) {
            for (int i = 0; i < L; ++i) {
                string pattern = word.substr(0, i) + "*" + word.substr(i + 1);
                patternMap[pattern].push_back(word);
            }
        }

        // BFS
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        unordered_set<string> visited;
        visited.insert(beginWord);

        while (!q.empty()) {
            auto [word, level] = q.front(); q.pop();

            for (int i = 0; i < L; ++i) {
                string pattern = word.substr(0, i) + "*" + word.substr(i + 1);

                for (string& neighbor : patternMap[pattern]) {
                    if (neighbor == endWord) return level + 1;
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        q.push({neighbor, level + 1});
                    }
                }
            }
        }

        return 0;
    }
};
