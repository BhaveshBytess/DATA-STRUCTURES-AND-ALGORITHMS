class Solution {
public:
    void dfs(int i, int j, vector<vector<int>>& grid, int& count) {
        int n = grid.size();
        int m = grid[0].size();
        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != 1) return;
        
        grid[i][j] = -1; // mark visited
        count++;
        
        dfs(i + 1, j, grid, count);
        dfs(i - 1, j, grid, count);
        dfs(i, j + 1, grid, count);
        dfs(i, j - 1, grid, count);
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int max_area = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    int count = 0;
                    dfs(i, j, grid, count);
                    max_area = max(max_area, count);
                }
            }
        }
        return max_area; 
    }
};
