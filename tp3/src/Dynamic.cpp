#include "Grafo.hpp"

std::pair<int, std::vector<int>> Grafo::tspDynamic() {
    int n = int(matriz.size());
    std::vector<std::vector<int>> dp(n, std::vector<int>(1 << n, -1));
    std::vector<std::vector<int>> parent(n, std::vector<int>(1 << n, -1));
    
    // Recursive function without std::function
    struct Solver {
        std::vector<std::vector<int>>& matriz;
        std::vector<std::vector<int>>& dp;
        std::vector<std::vector<int>>& parent;
        int n;
        
        Solver(std::vector<std::vector<int>>& d, std::vector<std::vector<int>>& dp_, std::vector<std::vector<int>>& p, int size)
            : matriz(d), dp(dp_), parent(p), n(size) {}
        
        int solve(int pos, int mask) {
            if (mask == (1 << n) - 1) return matriz[pos][0]; // Return to starting city
            if (dp[pos][mask] != -1) return dp[pos][mask];

            int ans = std::numeric_limits<int>::max(), next_city = -1;
            for (int city = 0; city < n; city++) {
                if ((mask & (1 << city)) == 0) { // If city is not visited
                    int new_cost = matriz[pos][city] + solve(city, mask | (1 << city));
                    if (new_cost < ans) {
                        ans = new_cost;
                        next_city = city;
                    }
                }
            }
            dp[pos][mask] = ans;
            parent[pos][mask] = next_city;
            return ans;
        }
    };
    
    Solver solver(matriz, dp, parent, n);
    int min_cost = solver.solve(0, 1);
    
    // Reconstruct path
    std::vector<int> path;
    int mask = 1, pos = 0;
    while (true) {
        path.push_back(pos);
        int next_pos = parent[pos][mask];
        if (next_pos == -1) break;
        mask |= (1 << next_pos);
        pos = next_pos;
    }
    path.push_back(0); // Return to start
    
    return {min_cost, path};
}

