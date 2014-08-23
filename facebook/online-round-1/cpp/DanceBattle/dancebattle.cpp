#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

char grid[101][101];
int cost[101][101];

vector<pair<int, int> > colour[10]; // lists of same coloured cells

//used to compute adjacent cells
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int rows, cols; // total rows and coloumns

int bfs(pair<int, int> start) {
    memset(cost, -1, sizeof (cost)); // all unvisited nodes have negative cost to mark them
    cost[start.first][start.second] = 0; // start node has cost 0

    queue< pair<int, int> > Q;
    Q.push(start);

    while (!Q.empty()) {

        pair<int, int> node = Q.front();
        Q.pop();
        int r = node.first;
        int c = node.second;
        int cst = cost[r][c];
        if (grid[r][c] == 'E') {
            return cst;
        }

        // search adjacent cells
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && cost[nr][nc] < 0 && grid[nr][nc] != 'W') {
                cost[nr][nc] = cst + 1;
                Q.push(make_pair(nr, nc));
            }
        }

        // search cells of the same colour
        if (grid[r][c] >= '1' && grid[r][c] <= '9') {
            vector<pair<int, int> > &trans = colour[grid[r][c] - '0'];
            for (int i = 0; i < trans.size(); i++) {
                pair<int, int> next = trans[i];
                if (cost[next.first][next.second] < 0) {
                    cost[next.first][next.second] = cst + 1;
                    Q.push(next);
                }
            }
        }
    }
    return -1;
}

int main() {
    int N;
    cin >> N;
    while (N--) {
        cerr << "Left: " << N << endl;
        cin >> rows >> cols;
        pair<int, int> start;
        for (int i = 0; i < 10; i++) colour[i].clear();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> grid[i][j];

                if (grid[i][j] == 'S') {
                    start = make_pair(i, j);
                } else if (grid[i][j] >= '1' && grid[i][j] <= '9') {
                    colour[grid[i][j] - '0'].push_back(make_pair(i, j));
                }
            }
        }
        cout << bfs(start) << "\n";
    }

    return 0;
}