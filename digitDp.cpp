#include <bits/stdc++.h>
using namespace std;

long long dp[20][11][2][2];

long long solve(string s ,int index, int last, int flag,int tight){
    
    // flag=1 means non zero started
    
    if (index == s.length()) {
        return 1;
    }
    
    if (dp[index][last][flag][tight] != -1) {
        return dp[index][last][flag][tight];
    }
    
    
    
    int limit=tight?(s[index] - '0'):9;
    
    
    long long cnt=0;
    
    
    for(int i=0;i<=limit;i++){
        if(i==0){
           if(flag==0) cnt+=solve(s,index+1,0,0,tight&(i==limit));
           else{
               if(last!=0) cnt+=solve(s,index+1,0,flag,tight&(i==limit));
           }
        }
        else{
            if(i!=last) cnt+=solve(s,index+1,i,1,tight&(i==limit));
        }
        
    }
    
    return dp[index][last][flag][tight]=cnt;
}



long long calc(long long x) {
    if (x < 0) return 0;
    if (x == 0) return 1;
    
    string s = to_string(x);
    memset(dp, -1, sizeof(dp)); // Reset DP state for each new number
    
    return solve(s, 0, 0, 0, 1);
}



int main() {
	// your code goes here
 
 
 ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b;
    if (cin >> a >> b) {
        // Calculate valid numbers in range [a, b] using prefix subtraction
        cout << calc(b) - calc(a - 1) << "\n";
    }

    return 0;

}
