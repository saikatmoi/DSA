#include <string>
using namespace std;

struct Node{
    Node * childs[26]={nullptr};
    bool isEnd=false;
    
    bool exists(char c){
        return childs[c-'a']!=nullptr;
    }
    
    void setEnd(){
        isEnd=true;
    }
    
    bool doesEnd(){
        return isEnd;
    }
    
    void putCh(char c){
        childs[c-'a']=new Node();
    }
    
    Node * getchild(char c){
        return childs[c-'a'];
    }
};

class Trie{
    Node* root;
    
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string s){
        Node * node=root;
        for(int i=0; i<s.size(); i++){
            // Fixed: call exists on node, not s
            if(node->exists(s[i])){
                // Fixed: pass s[i] to getchild
                node = node->getchild(s[i]);
            }
            else{
                // Fixed: call putCh on node, not s
                node->putCh(s[i]);
                node = node->getchild(s[i]);
            }
        }
        // Fixed: added ()
        node->setEnd();
    }
    
    // Fixed: return type changed from void to bool
    bool find(string s){
        Node * node=root;
        for(int i=0; i<s.size(); i++){
            // Fixed: call exists on node
            if(node->exists(s[i])){
                // Fixed: pass s[i] to getchild
                node = node->getchild(s[i]);
            }
            else{
               return false;
            }
        }
        // Fixed: added ()
        return node->doesEnd();
    }
};
