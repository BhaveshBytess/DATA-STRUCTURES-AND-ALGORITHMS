class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        vector<vector<string>> res;

        if (!dict.count(endWord)) return res;

        unordered_map<string, vector<string>> parents;
        unordered_set<string> visited, currLevel;

        queue<string> q;
        q.push(beginWord);
        visited.insert(beginWord);

        bool found = false;

        while (!q.empty() && !found) {
            int size = q.size();
            currLevel.clear();

            for (int i = 0; i < size; ++i) {
                string word = q.front(); q.pop();

                string original = word;
                for (int j = 0; j < word.size(); ++j) {
                    char c = word[j];
                    for (char ch = 'a'; ch <= 'z'; ++ch) {
                        if (ch == c) continue;
                        word[j] = ch;

                        if (dict.count(word)) {
                            if (!visited.count(word)) {
                                if (!currLevel.count(word)) {
                                    q.push(word);
                                    currLevel.insert(word);
                                }
                                parents[word].push_back(original);
                                if (word == endWord) found = true;
                            }
                        }
                    }
                    word[j] = c;
                }
            }

            for (const string& w : currLevel) visited.insert(w);
        }

        if (found) {
            vector<string> path = {endWord};
            backtrack(endWord, beginWord, parents, path, res);
        }

        return res;
    }

    void backtrack(string& word, string& beginWord,
                   unordered_map<string, vector<string>>& parents,
                   vector<string>& path,
                   vector<vector<string>>& res) {
        if (word == beginWord) {
            vector<string> temp = path;
            reverse(temp.begin(), temp.end());
            res.push_back(temp);
            return;
        }

        for (string& p : parents[word]) {
            path.push_back(p);
            backtrack(p, beginWord, parents, path, res);
            path.pop_back();
        }
    }
};
