#include <bits/stdc++.h>
using namespace std;

int minimumEffortPath(vector<vector<int>>& heights) {
    int rows = heights.size();
    int cols = heights[0].size();

    // Directions: right, left, down, up
    vector<int> dx = {0, 0, 1, -1};
    vector<int> dy = {1, -1, 0, 0};

    // Effort matrix initialized to INF
    vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
    effort[0][0] = 0;

    // Min-heap priority queue: {effort_so_far, {x, y}}
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<>> pq;
    pq.push({0, {0,0}});

    while(!pq.empty()) {
        auto [curEffort, cell] = pq.top();
        pq.pop();
        int x = cell.first;
        int y = cell.second;

        // Destination reached
        if(x == rows - 1 && y == cols - 1) return curEffort;

        // Explore neighbors
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                int nextEffort = max(curEffort, abs(heights[x][y] - heights[nx][ny]));

                if(nextEffort < effort[nx][ny]) {
                    effort[nx][ny] = nextEffort;
                    pq.push({nextEffort, {nx, ny}});
                }
            }
        }
    }

    return 0; // unreachable (problem guarantees path exists)
}

int main() {
    vector<vector<int>> heights = {{1,2,2},{3,8,2},{5,3,5}};
    cout << minimumEffortPath(heights) << endl; // Output: 2
    return 0;
}
