class Solution {
public:
    void dfs(int row, int col, vector<vector<int>>& image, int originalColor, int newColor) {
        int m = image.size(), n = image[0].size();

        // Boundary + visited + color check
        if (row < 0 || row >= m || col < 0 || col >= n || image[row][col] != originalColor)
            return;

        image[row][col] = newColor;

        // 4-directional movement
        dfs(row + 1, col, image, originalColor, newColor);
        dfs(row - 1, col, image, originalColor, newColor);
        dfs(row, col + 1, image, originalColor, newColor);
        dfs(row, col - 1, image, originalColor, newColor);
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int originalColor = image[sr][sc];
        if (originalColor != newColor) {
            dfs(sr, sc, image, originalColor, newColor);
        }
        return image;
    }
};
