#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9; // Represents an impossibly large distance

class TSP {
    int n;
    vector<vector<int>> dist;
    vector<vector<int>> memo;

public:
    TSP(int cities, vector<vector<int>> distance_matrix) {
        n = cities;
        dist = distance_matrix;
        
        // Initialize memoization table with -1
        // Size is 2^n (for the mask) by n (for the current city)
        memo.assign(1 << n, vector<int>(n, -1));
    }

    // mask: binary representation of visited cities
    // current_city: the city we are currently standing in
    int solve(int mask, int current_city) {
        // 1. BASE CASE: All cities visited
        // (1 << n) - 1 creates a number where the first 'n' bits are all 1s.
        if (mask == (1 << n) - 1) {
            // Return cost to travel from current city back to the start (city 0)
            return dist[current_city][0]; 
        }

        // 2. MEMOIZATION CHECK
        if (memo[mask][current_city] != -1) {
            return memo[mask][current_city];
        }

        int min_cost = INF;

        // 3. TRANSITION: Try visiting every other city
        for (int next_city = 0; next_city < n; next_city++) {
            
            // Check if 'next_city' is NOT visited yet (the bit is 0)
            if ((mask & (1 << next_city)) == 0) {
                
                // Add 'next_city' to our mask by flipping its bit to 1
                int new_mask = mask | (1 << next_city);
                
                // Calculate cost to go there + cost to finish the rest of the tour
                int cost = dist[current_city][next_city] + solve(new_mask, next_city);
                
                // Track the absolute minimum path found
                min_cost = min(min_cost, cost);
            }
        }

        // 4. CACHE AND RETURN
        return memo[mask][current_city] = min_cost;
    }
};

int main() {
    // 4 cities
    int n = 4; 
    
    // Distance matrix: dist[i][j] is distance from city i to city j
    vector<vector<int>> dist = {
        {0, 20, 42, 25},
        {20, 0, 30, 34},
        {42, 30, 0, 10},
        {25, 34, 10, 0}
    };

    TSP tspSolver(n, dist);
    
    // Start at city 0. 
    // Mask is 1 (binary 0001), because city 0 is marked as visited.
    int min_tour_cost = tspSolver.solve(1, 0);
    
    cout << "Minimum Cost for TSP Tour: " << min_tour_cost << endl;
    
    return 0;
}
