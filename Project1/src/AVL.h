

#ifndef AVL_H
#define AVL_H



#include <string> // Include <string> for string data type
using namespace std;
#include <iostream>
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
    void InorderHelper(Node* node);
    void preorderHelper(Node* node);
    void postorderHelper(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* searchIDHelper(Node* node, string ID);
    void searchNameHelper(Node* node, string name, bool &found);
    void removeNodeHelper(Node* &node,string ID);
    void removeNthNodeHelper(Node* node, int n);

public:
    Node* root;
    void insert(string name, string ufid);
    void inOrder();
    void preOrder();
    void postOrder();
    string searchID(string ID);
    void searchName(string name);
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

void AVLTree::InorderHelper(Node* node) {
    if (node == nullptr) {
        return;
    } else {
        InorderHelper(node->left);
        cout << node->name << ", ";
        InorderHelper(node->right);
    }
}

void AVLTree::preorderHelper(Node *node) {
    if (node == nullptr) {
        return;
    } else {
        cout << node->name << ", ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
}
void AVLTree::postorderHelper(Node *node) {
    if (node == nullptr) {
        return;
    } else {
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->name << ", ";
    }
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

void AVLTree::searchNameHelper(Node *node, string name, bool &found) {

    if (node == nullptr) {
        return;
    }

    if (node->name == name) {
        cout << node->ufid << "\n";
        found = true;
    }

    searchNameHelper(node->left, name,found);
    searchNameHelper(node->right, name, found);
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
void AVLTree::removeNthNodeHelper(Node* node, int n) {
    if (n <= 0 || n > root->height) {
        cout << "Unsuccessful\n";
        return;
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
            nthNodeFound = true; // Set the flag to true to exit the loop
        } else {
            parent = current;
            current = current->right;
            n -= leftSubtreeSize + 1;
        }
    }

    if (!nthNodeFound) {
        cout << "Unsuccessful\n";
    }
}


// Public functions:
void AVLTree::insert(std::string name, std::string ufid) {
    this->root = InsertHelper(this->root, name, ufid);
}

void AVLTree::inOrder() {
    InorderHelper(this->root);
    cout << "\n";

}

void AVLTree::preOrder(){
    preorderHelper(this->root);
}

void AVLTree::postOrder() {
    postorderHelper(this->root);
}

string AVLTree::searchID(string ID) {
    if (searchIDHelper(this->root, ID) == nullptr){
        return "null";
    }
    else{
        return searchIDHelper(this->root, ID)->name;
    }
}

void AVLTree::searchName(string name) {
    bool found = false;
    searchNameHelper(this->root, name, found);
    if (!found) {
        cout << "unsuccesful" << "\n";
    }
}

void AVLTree::levelCount() {
    cout << this->root->height << "\n";
}

void AVLTree::removeNode(string ID) {
    removeNodeHelper(this->root, ID);
}

void AVLTree::removeNthNode(int n){
    removeNthNodeHelper(this->root, n);
}



#endif //AVL_H