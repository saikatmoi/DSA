#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long max_weight;
    cin >> n >> max_weight;

    vector<long long> weight(n);
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    // dp[mask] = {min_rides, min_weight_on_last_ride}
    // Size is 2^n. Initialize with a state worse than any possible answer.
    vector<pair<int, long long>> dp(1 << n, {n + 1, 0});
    
    // Base case: 0 people transported means 1 empty ride started, carrying 0 weight.
    dp[0] = {1, 0};

    // Iterate through all possible subsets of people
    for (int mask = 1; mask < (1 << n); mask++) {
        
        // Try making every person 'i' in the current subset the LAST person to enter
        for (int i = 0; i < n; i++) {
            
            // Check if person 'i' is actually in the current mask
            if ((mask & (1 << i)) != 0) {
                
                // Get the DP state of the subset exactly before person 'i' was added
                int prev_mask = mask ^ (1 << i); // Removes 'i' from the mask
                int rides = dp[prev_mask].first;
                long long current_weight = dp[prev_mask].second;

                // Scenario A: Person 'i' fits in the current elevator
                if (current_weight + weight[i] <= max_weight) {
                    current_weight += weight[i];
                } 
                // Scenario B: Person 'i' is too heavy, must start a new elevator ride
                else {
                    rides++;
                    current_weight = weight[i];
                }

                // Update the current mask with the best outcome found so far.
                // pair < operation automatically checks 'rides' first, then 'current_weight'
                dp[mask] = min(dp[mask], {rides, current_weight});
            }
        }
    }

    // The answer is the number of rides required for the full bitmask (all 1s)
    cout << dp[(1 << n) - 1].first << "\n";

    return 0;
}
