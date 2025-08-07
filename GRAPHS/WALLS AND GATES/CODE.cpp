vector<vector<int>> solve(vector<vector<int>>& rooms) {
    int n = rooms.size(), m = rooms[0].size();
    queue<pair<int, int>> q;

    // Step 1: Push all gates into the queue (Multi-Source BFS)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (rooms[i][j] == 0) {
                q.push({i, j});
            }
        }
    }

    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};

    // Step 2: BFS from all gates
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // Check bounds and if it's an empty room (INF)
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && rooms[nx][ny] == INT_MAX) {
                rooms[nx][ny] = rooms[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return rooms;
}
