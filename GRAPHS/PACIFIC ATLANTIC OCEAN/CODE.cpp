#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();

        vector<vector<int>> pacific(n, vector<int>(m, 0));
        vector<vector<int>> atlantic(n, vector<int>(m, 0));

        queue<pair<int, int>> qPacific;
        queue<pair<int, int>> qAtlantic;

        // Step 1: Push Pacific border cells into qPacific
        for (int i = 0; i < n; i++) {
            pacific[i][0] = 1;
            qPacific.push({i, 0});
        }
        for (int j = 0; j < m; j++) {
            pacific[0][j] = 1;
            qPacific.push({0, j});
        }

        // Step 2: Push Atlantic border cells into qAtlantic
        for (int i = 0; i < n; i++) {
            atlantic[i][m - 1] = 1;
            qAtlantic.push({i, m - 1});
        }
        for (int j = 0; j < m; j++) {
            atlantic[n - 1][j] = 1;
            qAtlantic.push({n - 1, j});
        }

        // 4-directional movement
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        // BFS function
        auto bfs = [&](queue<pair<int, int>>& q, vector<vector<int>>& visited) {
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
                        !visited[nx][ny] &&
                        heights[nx][ny] >= heights[x][y]) {
                        visited[nx][ny] = 1;
                        q.push({nx, ny});
                    }
                }
            }
        };

        // Step 3: BFS for both oceans
        bfs(qPacific, pacific);
        bfs(qAtlantic, atlantic);

        // Step 4: Collect intersection cells
        vector<vector<int>> result;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }
};
