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
    void update_height(Node* node);
    

private:
    Node* leftrotate(Node* node);
    Node* rightrotate(Node* node);
    Node * getmaxNode(Node* node);
};

//public implementations

int AVLTree::get_height(Node* node){
    if (node==nullptr){
        return 0;
    }
    return node->height;
}

void AVLTree::update_height(Node* node) {
    if (node !=nullptr){
        node ->height = max(get_height(node->left),get_height(node->right))+1;
    }
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
}

//private implementations 
//left rotate: 
Node* AVLTree::leftrotate(Node* head){
    Node* newhead = head->right;
    Node* temp = newhead->left;

    newhead->left = head;
    head->right = temp;

    update_height(head);
    update_height(newhead);

    return newhead;
}

//right rotate:
Node* AVLTree::rightrotate(Node* head){
    Node* newhead = head->left;
    Node* T = newhead->right;

    head->left = T;
    newhead->right = head;

   update_height(head);
    update_height(newhead);

    return newhead;
}


Node* AVLTree::getmaxNode(Node * node){
    if (node == nullptr){
        return nullptr;
    }
    Node * current = node;
    while (current -> right !=nullptr){
        current = current -> right;

    }
    return current;
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

   update_height(node);
    int balancefactor;
    if (node==nullptr){
        balancefactor = 0;
    }
    else balancefactor =  get_height(node->left) - get_height(node->right);

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
    if (root ==nullptr){
        return root;
    }
    //traverse

    if (k < root->k){
        root->left = Dint(root->left, k);
    }
    else if (k > root->k){
        root -> right = Dint(root->right,k);
    }
    else { 
        if ((root->left == nullptr) || (root->right == nullptr)){
            Node* temp;
            if (root->left != nullptr) {
                temp = root->left;
            } else {
                temp = root->right;
            }
            //no children
            if (temp == nullptr){
                temp = root;
                root = nullptr;
            }
            else { //one child
                *root = *temp;
            }
            delete temp;
        } else { //two children
            Node* temp = getmaxNode(root->left);
            root->k = temp->k;
            root->left = Dint(root->left, temp->k);
        }
    }
    if (root == nullptr){
        return root;
    }
    
 // Update the height of the current node
    update_height(root);
    int balancefactor = get_height(root->left) - get_height(root->right);

    // CASE 1: Left Left Case
    if (balancefactor > 1 && get_height(root->left->left) >= get_height(root->left->right)) {
        return rightrotate(root);
    }

    // CASE 2: Left Right Case
    if (balancefactor > 1 && get_height(root->left->left) < get_height(root->left->right)) {
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }

    // CASE 3: Right Right Case
    if (balancefactor < -1 && get_height(root->right->right) >= get_height(root->right->left)) {
        return leftrotate(root);
    }

    // CASE 4: Right Left Case
    if (balancefactor < -1 && get_height(root->right->right) < get_height(root->right->left)) {
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }

    return root;
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
            //error handling
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