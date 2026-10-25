
// https://leetcode.com/problems/count-magical-substring-pairs-ii/description/


// You are given a string s of length n consisting of lowercase English letters.

// For every triplet of indices (i, j, k) satisfying 0 <= i <= j < k < n, define:

//     s1 = s[i..j]
//     s2 = s[j + 1..k]

// A pair of substrings (s1, s2) is called magical if the number of distinct characters in s1 is equal to the number of distinct characters in s2.

// Return the number of triplets (i, j, k) for which (s1, s2) is a magical pair.

// A substring is a contiguous non-empty sequence of characters within a string.


class Solution {
public:
    // Precomputes the number of subarrays STARTING at index 'i' 
    // that have EXACTLY 'size' distinct characters.
    vector<vector<int>> prepareRightCache(string &s, int &n) {
        // cache[size][i] will store the count of valid subarrays
        vector<vector<int>> cache(27, vector<int>(n, 0));
        
        for(int size = 1; size <= 26; size++) {
            int l = 0, r = 0;
            unordered_map<char, int> map;
            
            while(r < n) {
                // Add the current character to our window
                ++map[s[r]];
                
                // When we have EXACTLY 'size' distinct characters
                while((int)map.size() == size) {
                    // AT LEAST logic: If s[l..r] has 'size' distinct characters, 
                    // extending 'r' further to the right (up to n) will still yield 
                    // at least 'size' distinct characters. Total valid endpoints = n - r.
                    cache[size][l] = n - r;
                    
                    // Shrink the window from the left to evaluate the next starting position
                    --map[s[l]];
                    if(map[s[l]] == 0) map.erase(s[l]);
                    l++;
                }
                r++;
            }
        }
        
        // Convert the "At Least K" counts to "Exactly K" counts using:
        // Exact(K) = AtLeast(K) - AtLeast(K+1)
        for(int size = 1; size < 26; size++) {
            for(int i = 0; i < n; i++) {
                cache[size][i] -= cache[size+1][i];
            }
        }
        
        return cache;
    }

    // Precomputes the number of subarrays ENDING at index 'i' 
    // that have EXACTLY 'size' distinct characters.
    vector<vector<int>> prepareLeftCache(string &s, int &n) {
        vector<vector<int>> cache(27, vector<int>(n, 0));
        
        for(int size = 1; size <= 26; size++) {
            int l = 0, r = 0;
            unordered_map<char, int> map;
            
            while(r < n) {
                // Add the current character to our window
                ++map[s[r]];
                
                // If window has MORE than 'size' distinct characters, shrink from left
                while((int)map.size() > size) {
                    --map[s[l]];
                    if(map[s[l]] == 0) map.erase(s[l]);
                    l++;
                }
                
                // AT MOST logic: If s[l..r] has 'size' or fewer distinct characters,
                // any subarray ending at 'r' and starting between 'l' and 'r' is valid.
                // There are exactly (r - l + 1) such starting positions.
                if((int)map.size() <= size) {
                    cache[size][r] = r - l + 1;
                }
                r++;
            }
        }
        
        // Convert the "At Most K" counts to "Exactly K" counts using:
        // Exact(K) = AtMost(K) - AtMost(K-1)
        for(int size = 26; size > 1; size--) {
            for(int i = 0; i < n; i++) {
                cache[size][i] -= cache[size-1][i];
            }
        }
        
        return cache;
    }

    long long countMagicalPairs(string s) {
        int n = s.size();
        
        // lcache[size][i]: Number of valid left substrings ending exactly at index i
        vector<vector<int>> lcache = prepareLeftCache(s, n);
        
        // rcache[size][i]: Number of valid right substrings starting exactly at index i
        vector<vector<int>> rcache = prepareRightCache(s, n);
        
        long long ans = 0;
        
        // Iterate through all possible distinct character counts (1 to 26)
        for(int size = 1; size <= 26; size++) {
            // Iterate through every possible split point 'i'
            for(int i = 0; i < n - 1; i++) {
                // Number of magical pairs formed by splitting between i and i+1
                // is the product of valid left strings ending at 'i' 
                // and valid right strings starting at 'i+1'.
                ans += ((long long)lcache[size][i] * rcache[size][i+1]);
            }
        }
        
        return ans;
    }
};
