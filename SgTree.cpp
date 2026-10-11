#include <bits/stdc++.h>
using namespace std;


class SgTree{
    
    private:
    
    vector<int>tree;
    int n;
    
    public:
    
    SgTree(int n,vector<int>&arr){
        this->n=n;
        tree.resize(4*n,0);
        buildTree(arr,0,n-1,0);
    }
    
    void buildTree(vector<int>&arr ,int l,int h,int index){
        if(h==l) {
            tree[index]=arr[h];
            return;
        } 
        
        int mid= l +(h-l)/2;
        
        buildTree(arr,l,mid,2*index+1);
        buildTree(arr,mid+1,h,2*index+2);
         
        tree[index]=min(tree[2*index+1],tree[2*index+2]);
        
    }
    
    void updateVal(int l,int h,int m,int v,int index){
        if(h==l) {
            tree[index]=v;
            return;
        }
        
       int mid= l +(h-l)/2;
       if(m<=mid){
           updateVal(l,mid,m,v,2*index+1);
       }
       else{
           updateVal(mid+1,h,m,v,2*index+2);
       }
       
       tree[index]=min(tree[2*index+1],tree[2*index+2]);
       
    }
    
  void update(int m , int v ){
        
        updateVal(0,n-1,m,v,0);
        
    }
    
    int queryVal(int lower,int higher,int l,int h,int index){
        
        if(lower<=l && h<=higher){
            return tree[index];
        }
        
        if(lower>h || higher<l){
            return 1e6;
        }
         int mid= l +(h-l)/2;
         
         int a =queryVal(lower,higher,l,mid,2*index+1);
         int b=queryVal(lower,higher,mid+1,h,2*index+2);
         
         return min(a,b);
        
    }
    
    
    int query(int lower,int higher){
        
        
        return queryVal(lower,higher,0,n-1,0);
        
    }
    
};

int main() {
    
    vector<int> arr = {1, 3, 2, 7, 9, 11};
    int n = arr.size();
    SgTree sg(n, arr);
    
    cout << "Min in range (1, 4): " << sg.query(1, 4) << "\n"; // Outputs 2
    
    sg.update(2, 0); // Update index 2 to 0
    cout << "Min in range (1, 4) after update: " << sg.query(1, 4) << "\n"; // Outputs 0

    return 0;

}
