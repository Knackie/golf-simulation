#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Position {
    int x, y;
};

bool isValidMove(int x, int y, int width, int height, const vector<string>& grid) {
    return x >= 0 && x < width && y >= 0 && y < height && grid[y][x] != 'X';
}

void findPath(Position ball, Position hole, int steps, vector<string>& result, const vector<string>& grid) {
    int dx = hole.x - ball.x;
    int dy = hole.y - ball.y;

    // Ensure the path is clear and valid
    if (dx == steps && dy == 0) {
        for (int i = 1; i < steps; ++i) {
            if (!isValidMove(ball.x + i, ball.y, result[0].size(), result.size(), grid) || result[ball.y][ball.x + i] != '.') {
                return;
            }
        }
        for (int i = 1; i <= steps; ++i) {
            result[ball.y][ball.x + i] = '>';
        }
    } else if (dx == -steps && dy == 0) {
        for (int i = 1; i < steps; ++i) {
            if (!isValidMove(ball.x - i, ball.y, result[0].size(), result.size(), grid) || result[ball.y][ball.x - i] != '.') {
                return;
            }
        }
        for (int i = 1; i <= steps; ++i) {
            result[ball.y][ball.x - i] = '<';
        }
    } else if (dy == steps && dx == 0) {
        for (int i = 1; i < steps; ++i) {
            if (!isValidMove(ball.x, ball.y + i, result[0].size(), result.size(), grid) || result[ball.y + i][ball.x] != '.') {
                return;
            }
        }
        for (int i = 1; i <= steps; ++i) {
            result[ball.y + i][ball.x] = 'v';
        }
    } else if (dy == -steps && dx == 0) {
        for (int i = 1; i < steps; ++i) {
            if (!isValidMove(ball.x, ball.y - i, result[0].size(), result.size(), grid) || result[ball.y - i][ball.x] != '.') {
                return;
            }
        }
        for (int i = 1; i <= steps; ++i) {
            result[ball.y - i][ball.x] = '^';
        }
    }
}

int main() {
    int width, height;
    cin >> width >> height; cin.ignore();
    
    vector<string> grid(height);
    vector<string> result(height, string(width, '.'));
    vector<Position> balls;
    vector<Position> holes;

    for (int i = 0; i < height; i++) {
        cin >> grid[i]; cin.ignore();
        for (int j = 0; j < width; j++) {
            if (isdigit(grid[i][j])) {
                balls.push_back({j, i});
            } else if (grid[i][j] == 'H') {
                holes.push_back({j, i});
            }
        }
    }

    for (const auto& ball : balls) {
        for (const auto& hole : holes) {
            int steps = grid[ball.y][ball.x] - '0';
            if (abs(ball.x - hole.x) + abs(ball.y - hole.y) == steps) {
                findPath(ball, hole, steps, result, grid);
                break;
            }
        }
    }

    for (const auto& line : result) {
        cout << line << endl;
    }

    return 0;
}
