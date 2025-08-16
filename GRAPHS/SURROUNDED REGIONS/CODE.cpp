class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        
        // Step 1: Mark all 'O's connected to border as safe (change to 'S')
        // Check all border cells
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // If it's on the border and is 'O', mark it and all connected 'O's as safe
                if((i == 0 || i == n-1 || j == 0 || j == m-1) && board[i][j] == 'O') {
                    dfs(board, i, j, n, m);
                }
            }
        }
        
        // Step 2: Convert all remaining 'O's to 'X' (these are surrounded)
        // Convert all 'S' back to 'O' (these are safe)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(board[i][j] == 'O') {
                    board[i][j] = 'X';  // Surrounded, capture it
                } else if(board[i][j] == 'S') {
                    board[i][j] = 'O';  // Safe, restore it
                }
            }
        }
    }
    
private:
    void dfs(vector<vector<char>>& board, int x, int y, int n, int m) {
        // Mark current cell as safe
        board[x][y] = 'S';
        
        // Directions: up, down, left, right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        // Check all 4 directions
        for(int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            // If valid cell and is 'O', recursively mark it as safe
            if(nx >= 0 && ny >= 0 && nx < n && ny < m && board[nx][ny] == 'O') {
                dfs(board, nx, ny, n, m);
            }
        }
    }
};

// Alternative BFS approach
class SolutionBFS {
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        
        queue<pair<int,int>> q;
        
        // Add all border 'O' cells to queue and mark them as safe
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if((i == 0 || i == n-1 || j == 0 || j == m-1) && board[i][j] == 'O') {
                    board[i][j] = 'S';
                    q.push({i, j});
                }
            }
        }
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        // BFS to mark all connected 'O's as safe
        while(!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for(int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                
                if(nx >= 0 && ny >= 0 && nx < n && ny < m && board[nx][ny] == 'O') {
                    board[nx][ny] = 'S';
                    q.push({nx, ny});
                }
            }
        }
        
        // Final conversion
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(board[i][j] == 'O') {
                    board[i][j] = 'X';  // Capture surrounded
                } else if(board[i][j] == 'S') {
                    board[i][j] = 'O';  // Restore safe
                }
            }
        }
    }
};
