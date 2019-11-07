#include <cmath>

using namespace std;

int max(int a, int b){
    return(abs(a)>abs(b))?a:b;
}


#include <iostream>

template<typename T>
struct Node {
    T key;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    int height;

    Node(T val){
        key = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
        Node(T val, Node<T>* _parent){
        key = val;
        left = nullptr;
        right = nullptr;
        parent = _parent;
        height = 1;
    }
};

template<typename T>
class Avl{
    private:
    Node<T>* root;

    public:

    int getHeight(Node<T>* node){
        if(!node) return 0;
        return node->height;
    }

    int getBalance(Node<T>* node){
        return getHeight(node->right) - getHeight(node->left);
    }

    void rotateRight(Node<T>* node){
        Node<T>* top = node;
        Node<T>* pivot = node->left;
        
        top->left = pivot->right;
        
        if(pivot->right){
            pivot->right->parent = top;
        }
        
        pivot->right = top;

        if(top->parent){
            if(top->parent->right == top){
                top->parent->right = pivot;
            }
            else{
                top->parent->left = pivot;
            }
            top->parent = pivot;
        }

        pivot->parent = top->parent;

        if(node == root){
            root = pivot;
        }

        top->height = max(getHeight(top->left),getHeight(top->right))+1;
        pivot->height = max(getHeight(pivot->left),getHeight(pivot->right))+1;
        
    }

    void rotateLeft(Node<T>* node){
        Node<T>* top = node;
        Node<T>* pivot = node->right;
        
        top->right = pivot->left;
        
        if(pivot->left){
            pivot->left->parent = top;
        }
        
        pivot->left = top;

        if(top->parent){
            if(top->parent->right == top){
                top->parent->right = pivot;
            }
            else{
                top->parent->left = pivot;
            }
            top->parent = pivot;
        }

        pivot->parent = top->parent;

        if(node == root){
            root = pivot;
        }

        top->height = max(getHeight(top->left),getHeight(top->right))+1;
        pivot->height = max(getHeight(pivot->left),getHeight(pivot->right))+1;
        
    }

    void insert(T val){
        cout<<"Inserting "<<val<<"...\n";
        if(!root){
            root = new Node<T>(val);
        }
        else{
            insert(root,val);
        }
    }

    void insert(Node<T>* node, T val){

        if(node->key < val){
            if(node->right){
                insert(node->right,val);
            }
            else{
                node->right = new Node<T>(val,node);
            }
        }
        else if(node->key > val){
            if(node->left){
                insert(node->left,val);
            }
            else{
                node->left = new Node<T>(val,node);
            }
        }
        else{
            return;
        }

        node->height = 1 + max(getHeight(node->left),getHeight(node->right));
        //cout<<"node: "<<node->key<<" with height "<<node->height<<"\n";

        int balance = getBalance(node);
        //cout<<"node: "<<node->key<<" with balance "<<balance<<"\n";

        //left left
        if(balance < -1 && val < node->left->key){
            cout<<"FOUND LEFT LEFT\n";
            rotateRight(node);
        }
        //right right
        else if(balance > 1 && val > node->right->key){
            cout<<"FOUND RIGHT RIGHT\n";
            rotateLeft(node);
        }
        //right left
        else if(balance > 1 && val < node->right->key){
            cout<<"FOUND RIGHT LEFT\n";
            rotateRight(node->right);
            rotateLeft(node);
        }
        //left right
        else if(balance < -1 && val > node->left->key){
            cout<<"FOUND LEFT RIGHT\n";
            rotateLeft(node->left);
            rotateRight(node);
        }
    }

    void print(){
        if(root){
            //cout<<"Printing...\n";
            print(root);
        }
        else{
            cout<<"Empty tree.\n";
        }
    }

    void print(Node<T>* node){
        if(node){
            cout<<node->key<<":"<<node->height<<" ";
            print(node->left);
            print(node->right);
        }
    }



};