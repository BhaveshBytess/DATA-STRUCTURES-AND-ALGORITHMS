class Solution {

public:

int swimInWater(vector<vector<int>>& grid) {

    int n = grid.size();

  

    vector<vector<int>> best(n, vector<int>(n, INT_MAX));

    best[0][0] = grid[0][0];

  

    // Min-heap: {time, {x,y}}

    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<>> pq;

    pq.push({grid[0][0], {0,0}});

  

    vector<int> dx = {0,0,1,-1};

    vector<int> dy = {1,-1,0,0};

  

    while(!pq.empty()){

        auto [time, cell] = pq.top(); pq.pop();

        int x = cell.first, y = cell.second;

  

        // reached destination

        if(x == n-1 && y == n-1) return time;

  

        for(int i=0; i<4; i++){

            int nx = x + dx[i], ny = y + dy[i];

            if(nx>=0 && nx<n && ny>=0 && ny<n){

                int nextTime = max(time, grid[nx][ny]);

                if(nextTime < best[nx][ny]){

                    best[nx][ny] = nextTime;

                    pq.push({nextTime, {nx,ny}});

                }

            }

        }

    }

    return -1; // never happens

}

};
