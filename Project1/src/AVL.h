

#ifndef AVL_H
#define AVL_H



#include <string>
using namespace std;
#include <iostream>
#include <vector>

struct Node{
    string name;
    string ufid;
    int height;
    Node* left;
    Node* right;
    Node(string name, string ufid);
};

class AVLTree{
private:
    Node* InsertHelper(Node* node, string name, string ufid);
    vector<string> InorderHelper(Node* node);
    vector<string> preorderHelper(Node* node);
    vector<string> postorderHelper(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* searchIDHelper(Node* node, string ID);
    void searchNameHelper(Node* node, string name, bool &found);
    bool removeNodeHelper(Node* &node,string ID);
    void removeNthNodeHelper(Node* node, int n);

public:
    Node* root;
    void insert(string name, string ufid);
    vector<string> inOrder();
    vector<string> preOrder();
    vector<string> postOrder();
    string searchID(string ID);
    vector<string> searchName(string name);
    void levelCount();
    void removeNode(string ID);
    void removeNthNode(int n);
    AVLTree() : root() {}
};
// Node Functions:
Node::Node(string name, string ufid) : name(name), ufid(ufid), height(0), left(nullptr), right(nullptr){}


//========================================================AVL Tree Functions======================================================//

// Private functions:
Node* AVLTree::InsertHelper(Node *node, std::string name, std::string ufid) {
    if (node == nullptr){
        return new Node(name, ufid);
    }
    else if (ufid < node->ufid){
        node->left = InsertHelper(node->left, name, ufid);
    }
    else if(ufid > node->ufid){
        node->right = InsertHelper(node->right, name, ufid);
    }
    node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);

    int balance = (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);

    if (balance > 1) {
        if (ufid < node->left->ufid) {
            return rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    } else if (balance < -1) {
        if (ufid > node->right->ufid) {
            return rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}

vector<string> AVLTree::InorderHelper(Node* node) {
    vector<string> result;
    if (node == nullptr) {
        return result;
    } else {
        vector<string> left = InorderHelper(node->left);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(node->name);
        vector<string> right = InorderHelper(node->right);
        result.insert(result.end(), right.begin(), right.end());
    }
    return result;
}

vector<string> AVLTree::preorderHelper(Node* node) {
    vector<string> result;
    if (node == nullptr) {
        return result;
    } else {
        result.push_back(node->name);
        vector<string> left = preorderHelper(node->left);
        result.insert(result.end(), left.begin(), left.end());
        vector<string> right = preorderHelper(node->right);
        result.insert(result.end(), right.begin(), right.end());
    }
    return result;
}

vector<string> AVLTree::postorderHelper(Node* node) {
    vector<string> result;
    if (node == nullptr) {
        return result;
    } else {
        vector<string> left = postorderHelper(node->left);
        result.insert(result.end(), left.begin(), left.end());
        vector<string> right = postorderHelper(node->right);
        result.insert(result.end(), right.begin(), right.end());
        result.push_back(node->name);
    }
    return result;
}



Node* AVLTree::rotateLeft(Node *node) {
    Node* tempNode = node->right;
    node->right = tempNode->left;
    tempNode->left = node;
    node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
    tempNode->height = 1 + max(tempNode->left ? tempNode->left->height : 0, tempNode->right ? tempNode->right->height : 0);
    return tempNode;
}

Node* AVLTree::rotateRight(Node *node) {
    Node* tempNode = node->left;
    node->left = tempNode->right;
    tempNode->right = node;
    node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
    tempNode->height = 1 + max(tempNode->left ? tempNode->left->height : 0, tempNode->right ? tempNode->right->height : 0);
    return tempNode;
}

Node* AVLTree::searchIDHelper(Node *node, string ID) {
    if (node == nullptr){
        return nullptr;
    }
    else if (node->ufid == ID){
        return node;
    }
    else if (node->ufid > ID){
        searchIDHelper(node->left, ID);
    }
    else if (node->ufid < ID){
        searchIDHelper(node->right, ID);
    }
}

void AVLTree::searchNameHelper(Node* node, string name, vector<string>& result) {
    if (node == nullptr) {
        return;
    }

    searchNameHelper(node->left, name, result);

    if (node->name == name) {
        result.push_back(node->ufid);
    }

    searchNameHelper(node->right, name, result);
}

void AVLTree::removeNodeHelper(Node* &node, string ID) {
    if (node == nullptr) {
        return;
    }

    if (ID < node->ufid) {
        removeNodeHelper(node->left, ID);
    } else if (ID > node->ufid) {
        removeNodeHelper(node->right, ID);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            Node *temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
                delete temp;
            }
        } else {
            Node *temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            node->name = temp->name;
            node->ufid = temp->ufid;

            removeNodeHelper(node->right, temp->ufid);
        }

        if (node != nullptr) {
            node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
        }
    }
}
bool AVLTree::removeNthNodeHelper(Node* node, int n) {
    if (n <= 0 || n > root->height) {
        return false; // Return false if the removal is unsuccessful
    }

    Node* current = node;
    Node* parent = nullptr;
    int leftSubtreeSize;
    bool nthNodeFound = false; // Flag variable to track if nth node is found

    while (current != nullptr && !nthNodeFound) {
        leftSubtreeSize = (current->left != nullptr) ? current->left->height : 0;

        if (n <= leftSubtreeSize) {
            parent = current;
            current = current->left;
        } else if (n == leftSubtreeSize + 1) {
            removeNodeHelper(this->root, current->ufid);
            nthNodeFound = true; // Set the flag to true to indicate successful removal
        } else {
            parent = current;
            current = current->right;
            n -= leftSubtreeSize + 1;
        }
    }

    return nthNodeFound; // Return true if the nth node was successfully removed, false otherwise
}


// Public functions:
void AVLTree::insert(std::string name, std::string ufid) {
    this->root = InsertHelper(this->root, name, ufid);
}

vector<string> AVLTree::inOrder() {
    return InorderHelper(root);
}

vector<string> AVLTree::preOrder() {
    return preorderHelper(root);
}

vector<string> AVLTree::postOrder() {
    return postorderHelper(root);
}

string AVLTree::searchID(string ID) {
    if (searchIDHelper(this->root, ID) == nullptr){
        return "nullptr";
    }
    else{
        return searchIDHelper(this->root, ID)->name;
    }
}

vector<string> AVLTree::searchName(string name) {
    vector<string> result;
    searchNameHelper(this->root, name, result);
    return result;
}

int AVLTree::levelCount() {
    return this->root->height;
}

void AVLTree::removeNode(string ID) {
    removeNodeHelper(this->root, ID);
}

void AVLTree::removeNthNode(int n){
    return removeNthNodeHelper(this->root, n);
}



#endif //AVL_H