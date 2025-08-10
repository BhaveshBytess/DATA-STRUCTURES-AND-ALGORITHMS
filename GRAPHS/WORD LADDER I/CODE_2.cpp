int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(endWord)) return 0; // if endWord not in list, impossible

    queue<string> q;
    q.push(beginWord);
    int level = 1; // starting from 1 because beginWord counts as a step

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            string word = q.front(); 
            q.pop();

            if (word == endWord) return level;

            for (int pos = 0; pos < word.size(); ++pos) {
                string newWord = word;
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == word[pos]) continue; // skip same char
                    newWord[pos] = c;

                    if (wordSet.count(newWord)) {
                        q.push(newWord);
                        wordSet.erase(newWord); // mark visited
                    }
                }
            }
        }
        level++;
    }
    return 0;
}
