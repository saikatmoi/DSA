#include <bits/stdc++.h>
using namespace std;

class FenwikTree{
    vector<int>tree;
    int n;
    
   public:
   
   FenwikTree(int size){
       this->n=size;
       tree.resize(n+1,0);
   }
   
   int query(int index){
       int sum=0;
       int i=index;
       while(i>0){
           sum+=tree[i];
           i-=(i&(-i));
       }
       return sum;
   }
       
       
       
    void add(int index,int value){
        int i=index;
        while(i<=n){
            tree[i]+=value;
            i+=(i&(-i));
        }
    }   
   
    
};





int main() {
	// your code goes here



int n = 5;
    FenwikTree bit(n);

    // Initial array conceptually: [0, 0, 0, 0, 0]
    
    bit.add(1, 4); // Array becomes: [4, 0, 0, 0, 0]
    bit.add(3, 5); // Array becomes: [4, 0, 5, 0, 0]
    bit.add(5, 2); // Array becomes: [4, 0, 5, 0, 2]

    cout << "Sum from index 1 to 3: " << bit.query(3) << endl; // Output: 9
    cout << "Sum from index 2 to 5: " << bit.query(1)<< " "<<bit.query(5) << endl; // Output: 7

    return 0;
}
