#include <vector>
#include <queue>
using namespace std;

int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0;

    // Step 1: Push all initially rotten oranges & count fresh ones
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            } else if (grid[i][j] == 1) {
                fresh++;
            }
        }
    }

    // If no fresh oranges at all
    if (fresh == 0) return 0;

    // Directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int minutes = 0;

    // Step 2: BFS traversal
    while (!q.empty()) {
        int size = q.size();
        bool rottedThisMinute = false;

        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                // If valid and fresh orange
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;        // Rot it
                    fresh--;                 // One less fresh orange
                    q.push({nx, ny});        // Add to queue for next minute
                    rottedThisMinute = true; // At least one orange rotted
                }
            }
        }

        if (rottedThisMinute) minutes++;  // Increase time only if something rotted
    }

    return (fresh == 0) ? minutes : -1;   // If fresh oranges still left, return -1
}
