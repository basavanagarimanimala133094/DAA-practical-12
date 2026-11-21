#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9; // Represents infinity (no direct path)

int tsp(int mask, int pos, int n, const vector<vector<int>>& dist, vector<vector<int>>& dp) {
    // Base case: All cities have been visited (all bits in mask are 1)
    if (mask == (1 << n) - 1) {
        // Return cost to go back to the starting city (city 0)
        return dist[pos][0];
    }

    // Return already computed subproblem result
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;

    // Try visiting every unvisited city
    for (int city = 0; city < n; city++) {
        // Check if the 'city'-th bit is 0 (meaning unvisited)
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city, n, dist, dp);
            ans = min(ans, newAns);
        }
    }

    // Store and return the minimum cost for this state
    return dp[mask][pos] = ans;
}

int main() {
    // Number of cities
    int n = 4;

    // Adjacency matrix representing distances between cities
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    // Memoization table initialized with -1
    // Size: (2^n) x n
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));

    // Start from city 0, so mask is 1 (binary: 0001)
    int minCost = tsp(1, 0, n, dist, dp);

    cout << "Minimum travelling cost: " << minCost << endl;

    return 0;
}
