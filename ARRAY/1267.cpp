class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int numRows = grid.size(), numCols = grid[0].size();
        int communicableServersCount = 0;

        // Traverse through the grid
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                if (grid[row][col] == 1) {
                    bool canCommunicate = false;

                    // Check for communication in the same row
                    for …        canCommunicate = true;
                                break;
                            }
                        }

                        // If a server was found in the same column, increment
                        // communicableServersCount
                        if (canCommunicate) {
                            communicableServersCount++;
                        }
                    }
                }
            }
        }

        return communicableServersCount;
    }
};
