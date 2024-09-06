#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

struct Node{
    int k;
    Node* left;
    Node* right;
    int height;
    Node(int val){
        k = val;
        left =nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree{
    public: 
    Node* Aint(Node* node, int k);
    Node* Dint(Node* root, int k);
    void PRE(Node* root);
    void IN(Node* root);
    void POST(Node* root);
    int get_height(Node* node);
    int balance_factor(Node* node);

private:
    Node* leftrotate(Node* node);
    Node* rightrotate(Node* node);
    Node* getminNode(Node* node);
};

//public implementations

int AVLTree::get_height(Node* node){
    if (node==nullptr){
        return 0;
    }
    return node->height;
}

int AVLTree::balance_factor(Node* node){
     if (node==nullptr){
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

//private implementations 
//left rotate: 
Node* AVLTree::leftrotate(Node* x){
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height= max(get_height(x->left), get_height(x->right)) + 1;
    y->height= max(get_height(y->left), get_height(y->right))+1;

    return y;
}

//right rotate:
Node* AVLTree::rightrotate(Node* y){
    Node* x = y->left;
    Node* T = x->right;

    y->left = T;
    x->right = y;

    y->height= max(get_height(y->left), get_height(y->right))+1;
    x->height= max(get_height(x->left), get_height(x->right)) + 1;

    return x;
}

//get minimum value in substree, most left node
Node* AVLTree::getminNode(Node* node){
    Node* current = node;
    while (current->left!=nullptr){
        current = current->left;
    }
    return current;
}

//INSERT AINT()
Node* AVLTree::Aint(Node* node, int k){
    if (node == nullptr){
        return new Node(k);
    }

    if (k< node->k){
        node->left = Aint(node->left,k);
    }
    else if (k > node->k){
        node->right = Aint(node->right,k);
    }
    else return node;


    node -> height = max(get_height(node->left), get_height(node->right))+1;


    int balancefactor = balance_factor(node);

    //rebalance tree
    //CASE 1: left left
    if (balancefactor >1 && k < node->left->k){
        return rightrotate(node);
    }
    //CASE 2: right right
    if (balancefactor < -1 && k > node->right->k){
        return leftrotate(node);
    }
    //CASE 3: left right 
    if (balancefactor > 1 && k > node->left->k){
        node->left = leftrotate(node->left);
        return rightrotate(node);
    }
    //CASE 4: right left
    if (balancefactor < -1 && k <node->right->k){
        node->right = rightrotate(node->right);
        return leftrotate(node);
    }

return node;

}

//DELETE
Node* AVLTree::Dint(Node* root, int k){
    if (root == nullptr){
        return root;
    }

    if (k <root->k){
        root->left = Dint(root->left,k);
    }
    else if(k> root->k){
        root->right = Dint(root->right,k);
    }
    else{
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp; 
            delete temp;
        } else {
            Node* temp = getminNode(root->right);
            root->k = temp->k;
            root->right = Dint(root->right, temp->k);
        }
    }

    if (root == nullptr) {
        return root;
    }
    root->height = max(get_height(root->left), get_height(root->right))+1;

    int balancefactor = balance_factor(root);
    
    //rebalance tree
    //CASE 1: left left
    if (balancefactor > 1 && balance_factor(root->left)>=0){
        return rightrotate(root);
    }
    //CASE 2: right right
     if (balancefactor < -1 && balance_factor(root->right) <= 0){
        return leftrotate(root);
        }
    //CASE 3: left right 
    if (balancefactor > 1 && balance_factor(root->left) < 0) {
            root->left = leftrotate(root->left);
            return rightrotate(root);
        }
    //CASE 4 right left 
    if (balancefactor < -1 && balance_factor(root->right) > 0){
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }
    return root;
}

// Pre-order traversal
void AVLTree::PRE(Node* root) {
    if (root != nullptr) {
        cout << root->k << " ";
        PRE(root->left);
        PRE(root->right);
    }
}

// In-order traversal
void AVLTree::IN(Node* root) {
    if (root != nullptr) {
        IN(root->left);
        cout << root->k << " ";
        IN(root->right);
    }
}

// Post-order traversal
void AVLTree::POST(Node* root) {
    if (root != nullptr) {
        POST(root->left);
        POST(root->right);
        cout << root->k << " ";
    }
}

vector <string> parse_input(const string& input){
    vector<string> result;
    string temp = "";
    for (char c : input) {
        if (c == ' ') {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
    }
    return result;
}

int main() {
    AVLTree AVLTree;
    Node* root = nullptr;

    string input;
    getline(cin, input);


    vector<string> cmds = parse_input(input);
    for (size_t i = 0; i < cmds.size() - 1; i++) {
        string cmd = cmds[i];
        if (cmd[0] == 'A') {
            int val = stoi(cmd.substr(1));
            if (val < 1 || val > 100){
                cout<<"Please insert values from 1 - 100"<<endl;
                return -1;
                
            }
            root = AVLTree.Aint(root, val);
        } else if (cmd[0] == 'D') {
            int val = stoi(cmd.substr(1));
            root = AVLTree.Dint(root, val);
        }
       
    }
    //check last command for order conditions. 
    string final_command = cmds.back();

    if (final_command == "PRE") {
        if (root == nullptr)
            cout << "EMPTY" << endl;
        else
            AVLTree.PRE(root);
    } else if (final_command == "IN") {
        if (root == nullptr)
            cout << "EMPTY" << endl;
        else
            AVLTree.IN(root);
    } else if (final_command == "POST") {
        if (root == nullptr)
            cout << "EMPTY" << endl;
        else
            AVLTree.POST(root);
    }

    if (root != nullptr)
        cout << endl;

    return 0;
}